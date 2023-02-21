#pragma once

#include <stdlib.h>

template<typename T>
struct span {
  T* v;
  size_t size;

  size_t size_bytes() {
    return sizeof(v);
  }

  T& operator[](int i) {
    if (i > this->size) {
      // FIXME: proper error handling
      return v[0];
    }

    return v[i];
  }
};
