#pragma once

#include "util/types.h"

#define BIT_SIZE(_s) (sizeof(_s)*8)

static inline bool bit_get(u8 *self, u8 i) { return (*self >> i) % 2 == 1; }
static inline void bit_set(u8 *self, u8 i) { *self |= (1 << i); }
static inline void bit_unset(u8 *self, u8 i) { *self &= ~(1 << i); }
static inline void bit_assign(u8 *self, u8 i, u8 n) { return n == 0x00 ? bit_unset(self, i) : bit_set(self, i); }

static inline u8 _bit_isolate(u8 *self, u8 from, u8 to) { return (*self << to) >> to >> from; }
static inline u8 bit_isolate(u8 *self, u8 from, u8 to) { return _bit_isolate(self, BIT_SIZE(u8)-1 - to, BIT_SIZE(u8)-1 - from); }
