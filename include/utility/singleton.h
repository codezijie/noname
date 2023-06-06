#ifndef UTILS_SINGLETON_H_
#define UTILS_SINGLETON_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DECLARE_SINGLETON(CSingleton) \
private:                              \
  static CSingleton *m_pInstance;     \
  static bool m_bInstantialized;      \
                                      \
public:                               \
  static CSingleton *Instance()       \
  {                                   \
    if (!m_bInstantialized)           \
    {                                 \
      m_bInstantialized = true;       \
      m_pInstance = new CSingleton;   \
    }                                 \
    return m_pInstance;               \
  }                                   \
  static void DeleteInstance()        \
  {                                   \
    delete m_pInstance;               \
    m_pInstance = nullptr;            \
    m_bInstantialized = false;        \
  }

#define IMPLEMENT_SINGLETON(CSingleton)       \
  bool CSingleton::m_bInstantialized = false; \
  CSingleton *CSingleton::m_pInstance = nullptr;

#endif
