/**
 * @file utility.h
 * @author codezijei (skd1102@outlook.com)
 * @brief
 * @version 0.0.1
 * @date 2023-06-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

typedef struct Tcl_Interp Tcl_Interp;
#include "singleton.h"
namespace util {

class GlobalObject {
  DECLARE_SINGLETON(GlobalObject);
 public:
  Tcl_Interp* GetInterp() const { return m_interp; }
  void SetInterp(Tcl_Interp* interp) { m_interp = interp; }

 private:
  Tcl_Interp* m_interp;
};

}  // namespace util