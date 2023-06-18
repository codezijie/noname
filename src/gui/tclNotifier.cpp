/**
 * @file tclNotifier.cpp
 * @author codezijie (skd1102@outlook.com)
 * @brief
 * @version 0.0.1
 * @date 2023-06-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "tclNotifier.h"

#include <QtCore/QSocketNotifier>
#include <QtCore/QTimer>
#include <QtWidgets/QApplication>
#include <QtCore/QEventLoop>

#include "utility.h"

namespace gui {

static int FileHandlerEventProc(Tcl_Event *evPtr, int flags);
static void NotifierExitHandler(ClientData clientData);
static void CreateFileHandler(int fd, int mask, Tcl_FileProc *proc,
                              ClientData clientData);
static void DeleteFileHandler(int fd);
static void DefineTimer(const Tcl_Time *timePtr);
static int WaitForEvent(const Tcl_Time *timePtr);

struct FileHandlerEvent : public Tcl_Event {
  int fd;
};

class NotifierState {
 public:
  NotifierState(QApplication *app)
      : m_app(app), m_currentTimeout(0), m_firstFileHandlerPtr(nullptr) {
    m_timer = new QTimer();
    m_loop = new QEventLoop(m_app);
    m_timeNotifier = new TclTimeNotifier();
    m_timeNotifier->connect(m_timer, SIGNAL(timeout()), SLOT(run()));
  }
  ~NotifierState();
  QApplication *m_app = nullptr;  // The Qt application
  QTimer *m_timer = nullptr;      // A QTimer
  TclTimeNotifier *m_timeNotifier = nullptr;
  int m_currentTimeout;  // Non 0, if timer active
  TclFileHandler *m_firstFileHandlerPtr = nullptr;
  QEventLoop *m_loop = nullptr;  
};
static NotifierState *notifier = nullptr;

NotifierState::~NotifierState() {
  if (notifier->m_currentTimeout) {
    notifier->m_timer->stop();
  }
  util::DeletePointer(m_timer);
  util::DeletePointer(m_timeNotifier);
  util::DeletePointer(m_loop);
  if (notifier->m_firstFileHandlerPtr != nullptr) {
    DeleteFileHandler(notifier->m_firstFileHandlerPtr->fd);
  }
}
//  class TclTimeNotifier

TclTimeNotifier::TclTimeNotifier() : QObject(nullptr) {
  setObjectName("TclTimeNotifier");
}
void TclTimeNotifier::run() {
  notifier->m_currentTimeout = 0;
  Tcl_ServiceAll();
}

// class TclFileHeadler

TclFileHandler::TclFileHandler(int f) : fd(f) {
  nextPtr = notifier->m_firstFileHandlerPtr;
  notifier->m_firstFileHandlerPtr = this;
}

TclFileHandler::~TclFileHandler() {
  util::DeletePointer(read);
  util::DeletePointer(write);
  util::DeletePointer(except);
}

void TclFileHandler::fileactive(int f) {
  auto s = sender();
  int current_mask = 0;
  if (s == read) {
    current_mask = TCL_READABLE;
  } else if (s == write) {
    current_mask = TCL_WRITABLE;
  } else if (s == except) {
    current_mask = TCL_EXCEPTION;
  } else {
  }

  if (!(mask & current_mask) || (readyMask & current_mask)) {
    return;
  }

  FileHandlerEvent *fileEvPtr;
  readyMask |= mask;
  fileEvPtr = new FileHandlerEvent();
  fileEvPtr->proc = FileHandlerEventProc;
  fileEvPtr->fd = f;
  Tcl_QueueEvent(static_cast<Tcl_Event *>(fileEvPtr), TCL_QUEUE_TAIL);
  Tcl_ServiceAll();
}

static int FileHandlerEventProc(Tcl_Event *evPtr, int flags) {
  TclFileHandler *filePtr;
  FileHandlerEvent *fileEvPtr = static_cast<FileHandlerEvent *>(evPtr);
  int mask;
  if (!(flags & TCL_FILE_EVENTS)) {
    return 0;
  }
  for (filePtr = notifier->m_firstFileHandlerPtr; filePtr != nullptr;
       filePtr = filePtr->nextPtr) {
    if (filePtr->fd != fileEvPtr->fd) {
      continue;
    }
    mask = filePtr->readyMask & filePtr->mask;
    if (0 != mask) {
      filePtr->proc(filePtr->clientData, mask);
    }
    break;
  }
  return 1;
}

static void FinalizeNotifier(ClientData) {}

static void *InitNotifier() { return nullptr; }

static void AlerNotifier(ClientData) {}

static void ServiceModeHook(int) {}

void Qt_InitNotifier(QApplication *app) {
  Q_ASSERT(app);
  Tcl_NotifierProcs notifier_info;
  notifier_info.createFileHandlerProc = CreateFileHandler;
  notifier_info.deleteFileHandlerProc = DeleteFileHandler;
  notifier_info.setTimerProc = DefineTimer;
  notifier_info.waitForEventProc = WaitForEvent;
  notifier_info.initNotifierProc = InitNotifier;
  notifier_info.finalizeNotifierProc = FinalizeNotifier;
  notifier_info.alertNotifierProc = AlerNotifier;
  notifier_info.serviceModeHookProc = ServiceModeHook;
  Tcl_SetNotifier(&notifier_info);

  Tcl_CreateExitHandler(NotifierExitHandler, nullptr);
  if (!notifier) {
    static NotifierState m_ns(app);
    notifier = &m_ns;
  }
}

static void NotifierExitHandler(ClientData) {}
static void DefineTimer(Tcl_Time *timerPtr) {
  Q_ASSERT(notifier);
  if (notifier->m_currentTimeout) {
    notifier->m_timer->stop();
  }
}

static void CreateFileHandler(int fd, int mask, Tcl_FileProc *proc,
                              ClientData clientData) {
  Q_ASSERT(notifier);
  TclFileHandler *filePtr;
  for (filePtr = notifier->m_firstFileHandlerPtr; filePtr != nullptr;
       filePtr = filePtr->nextPtr) {
    if (filePtr->fd == fd) {
      break;
    }
  }
  filePtr->proc = proc;
  filePtr->clientData = clientData;

  if (mask & TCL_READABLE) {
    if (!(filePtr->mask & TCL_READABLE)) {
      filePtr->read = new QSocketNotifier(fd, QSocketNotifier::Read);
      filePtr->connect(filePtr->read, SIGNAL(activated(int)),
                       SLOT(fileactive(int)));
    }
  } else {
    if (filePtr->mask & TCL_READABLE) {
      delete filePtr->read;
    }
  }
  if (mask & TCL_WRITABLE) {
    if (!(filePtr->mask & TCL_WRITABLE)) {
      filePtr->write = new QSocketNotifier(fd, QSocketNotifier::Write);
      filePtr->connect(filePtr->write, SIGNAL(activated(int)),
                       SLOT(fileactive(int)));
    }
  } else {
    if (filePtr->mask & TCL_WRITABLE) {
      delete filePtr->write;
    }
  }
  filePtr->mask = mask;
}
static void DeleteFileHandler(int fd) {
  Q_ASSERT(notifier);
  TclFileHandler *filePtr, *prevPtr;
  for (prevPtr = NULL, filePtr = notifier->m_firstFileHandlerPtr;;
       prevPtr = filePtr, filePtr = filePtr->nextPtr) {
    if (filePtr == NULL) {
      return;
    }
    if (filePtr->fd == fd) {
      break;
    }
  }
  if (prevPtr == NULL) {
    notifier->m_firstFileHandlerPtr = filePtr->nextPtr;
  } else {
    prevPtr->nextPtr = filePtr->nextPtr;
  }
  delete filePtr;
}
static void DefineTimer(const Tcl_Time *timePtr) {
  Q_ASSERT(notifier);
  if (notifier->m_currentTimeout != 0) {
    notifier->m_timer->stop();
  }
  if (timePtr) {
    int timeout = timePtr->sec * 1000 + timePtr->usec / 1000;
    notifier->m_timer->start(timeout);
    notifier->m_currentTimeout = 1;
  } else {
    notifier->m_currentTimeout = 0;
  }
}
static int WaitForEvent(const Tcl_Time *timePtr) {
  Q_ASSERT(notifier);
  int timeout;
  if (timePtr) {
    timeout = timePtr->sec * 1000 + timePtr->usec / 1000;
    if (timeout == 0) {
      if (!notifier->m_loop->processEvents()) {
        return 0;
      }
    } else {
      DefineTimer(timePtr);
    }
  }
  notifier->m_loop->processEvents(QEventLoop::WaitForMoreEvents);
  return 1;
}
}  // namespace gui