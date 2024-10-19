#pragma once

namespace util {

/**
 * @brief delete pointer
 *
 * @tparam T
 * @param pointer
 */
template <typename T> inline void DeletePointer(T *&pointer) {
  if (pointer == nullptr) {
    return;
  }
  delete pointer;
  pointer = nullptr;
}

} // namespace util
