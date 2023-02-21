#pragma once

#include "instream.h"
#include "outstream.h"
#include "util/types.h"

template <typename T>
struct Serializer {
  virtual void serialize(const T &t, Outstream &out) const {}
  virtual T deserialize(T &t, Instream &in) const {}
};

#define S_WRITE(_t, _o) \
Serializer<decltype(_t)>().serialize(_t, _o)
#define S_READ(_t, _i) \
Serializer<decltype(_t)>().deserialize(_t, _i)

// defines a serializer for primitive type _t
#define _PRIMITIVE_SERIALIZER(_t)                        \
template <>                                              \
struct Serializer<_t> {                                  \
  auto serialize(const _t &data, Outstream &out) const { \
    return out.write(data);                              \
  }                                                      \
  auto deserialize(_t &data, Instream &in) const {       \
    return in.read<_t>(data);                            \
  }                                                      \
};

_PRIMITIVE_SERIALIZER(u8)
_PRIMITIVE_SERIALIZER(u16)
_PRIMITIVE_SERIALIZER(u32)
_PRIMITIVE_SERIALIZER(u64)

_PRIMITIVE_SERIALIZER(s8)
_PRIMITIVE_SERIALIZER(s16)
_PRIMITIVE_SERIALIZER(s32)
_PRIMITIVE_SERIALIZER(s64)

_PRIMITIVE_SERIALIZER(f32)
_PRIMITIVE_SERIALIZER(f64)

_PRIMITIVE_SERIALIZER(bool)
