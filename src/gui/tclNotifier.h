/**
 * @file tclNotifier.h
 * @author codezijie (skd1102@outlook.com)
 * @brief 
 * @version 0.0.1
 * @date 2023-06-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <tcl.h>
#include <QtCore/QSocketNotifier>
#include <QtCore/QObject>
namespace gui {

class TclTimeNotifier : public QObject {
  Q_OBJECT
public:
  TclTimeNotifier();
  ~TclTimeNotifier() = default;

public slots:
  void run();
};

class TclFileHandler : public QObject {
  Q_OBJECT
public:
  TclFileHandler(int f);
  ~TclFileHandler();
  int fd = 0;
  int mask = 0; /* Mask of desired events: TCL_READABLE, etc. */
  int readyMask = 0;
  /* Events that have been seen since the
   * last time FileHandlerEventProc was called
   * for this file. */
  QSocketNotifier *read = nullptr;
  QSocketNotifier *write = nullptr;
  QSocketNotifier *except = nullptr;
  Tcl_FileProc *proc = nullptr;
  /* Procedure to call, in the style of
   * CreateFileHandler. */
  ClientData clientData; /* Argument to pass to proc. */
  TclFileHandler *nextPtr; /* Next in list of all files we care about. */
public slots:
  void fileactive(int);

};


} //namespace gui