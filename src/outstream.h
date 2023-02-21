#pragma once

#include "util/types.h"
#include <bits/types/FILE.h>
#include <cstdio>
#include <cstring>
#include "span.h"

// abstract output stream class
struct Outstream {
  virtual ~Outstream() = default;

  // write data to output stream
  virtual int write(span<u8> data) {
    return 0;
  }

  template <typename T>
  auto write(T data) {
    return this->write({ reinterpret_cast<u8*>(&data), sizeof(data) });
  }
};

// output stream wrapping a block of memory
struct MemoryOutstream : public Outstream {
  MemoryOutstream(span<u8> out) : out(out) {}

  span<u8> out;
  size_t index = 0;

  int write(span<u8> data) override {
    if (this->index + data.size_bytes() > this->out.size_bytes()) {
      return 1;
    }

    std::memcpy(
        &this->out[this->index],
        &data[0],
        data.size_bytes());
    this->index += data.size_bytes();

    return 0;
  }
};

struct FileOutstream : public Outstream {
  FileOutstream(FILE* file) : file(file) {}

  FILE* file;

  int write(span<u8> data) override {
    size_t result = std::fwrite(&data[0], data.size_bytes(), 1, this->file);
    if (result != 1) return 1;
    return 0;
  }
};
