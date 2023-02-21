#pragma once

#include "util/types.h"
#include <cstdio>
#include <cstring>
#include "span.h"

// abstract input stream class
struct Instream {
  virtual ~Instream() = default;

  // read data from input stream
  virtual int read(size_t n, span<u8> buf) {
    return 0;
  }

  // `stream.read<int>(t) -> result, t -> T`
  template <typename T>
  auto read(T &t) {
    u8 data[sizeof(T)];
    auto result = this->read(
        sizeof(T),
        { reinterpret_cast<u8*>(&data[0]), sizeof(data) });
    if (result == 0) {
      t = *reinterpret_cast<T*>(&data[0]);
    }
    return result;
  }
};

struct MemoryInstream : public Instream {
  MemoryInstream(span<u8> in) : in(in) {}

  span<u8> in;
  size_t index = 0;

  int read(size_t n, span<u8> data) override {
    if (this->index + n > this->in.size_bytes()) {
      return 1;
    }

    std::memcpy(
        &data[0],
        &this->in[this->index],
        n);
    this->index += n;

    return 0;
  }
};

struct FileInstream : public Instream {
  FileInstream(FILE* file) : file(file) {}

  FILE* file;

  int read(size_t n, span<u8> data) override {
    size_t result = std::fread(&data[0], n, 1, this->file);
    if (result != 1) return 1;
    return 0;
  }
};
