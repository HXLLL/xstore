#pragma once

#include "./lib.hh"

namespace xstore {

namespace xkv {

using namespace r2;

// an iterator to find all keys
template <class Derived> class KeyIterTrait {
public:
  void begin() { return reinterpret_cast<Derived *>(this)->begin_impl(); }

  void next() { return reinterpret_cast<Derived *>(this)->next_impl(); }

  auto has_next() -> bool {
    return reinterpret_cast<Derived *>(this)->has_next_impl();
  }

  auto cur_key() -> KeyType {
    return reinterpret_cast<Derived *>(this)->cur_key_impl();
  }

  /*!
    \ret: return an opaque u64 to the user
    For example, if it is the B+Tree, then the val maybe the key's leaf node's
    addr. Another example: if it is a sorted array, then the val maybe the key's
    index.
   */
  auto opaque_val() -> u64 {
    return reinterpret_cast<Derived *>(this)->opaque_val_impl();
  }
};

} // namespace xkv
} // namespace xstore
