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

namespace util {

/**
 * @brief delete pointer
 *
 * @tparam T
 * @param pointer
 */
template <typename T>
inline void DeletePointer(T*& pointer) {
  if (pointer == nullptr) {
    return;
  }
  delete pointer;
  pointer = nullptr;
}

}  // namespace util