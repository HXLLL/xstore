#pragma once

#include "../alloc_trait.hh"
#include "../kv_trait.hh"

#include "./inner_node.hh"
#include "./xnode.hh"

namespace xstore {

namespace xkv {

namespace xtree {

/*!
  N : fanout
  V : the value type
 */
template <usize N, typename V> struct XTree : public KVTrait<XTree<N, V>, V> {

  using Inner = TreeInner<N>;
  using Leaf = XNode<N, V>;

  // data structure
  int depth = 0;
  raw_ptr_t root = nullptr;
  static __thread Leaf *pre_alloc_leaf_node;

  // impl the public trait
  auto get_impl(const u64 &k) -> Option<V> {
    auto leaf = this->find_leaf(k);
    ASSERT(leaf != nullptr);
    auto idx = leaf->search(k);
    if (idx) {
      return leaf->values[idx.value()].get_payload();
    }
    return {};
  }

  auto find_leaf(const u64 &k) -> Leaf * {
    auto cur_node = root;
    auto cur_depth = depth;

    while (this->depth != 0) {
      // traversing the inner nodes
      Inner *inner = reinterpret_cast<Inner *>(cur_node);
      cur_node = inner->find_children(k);
      // down to the next
      this->depth -= 1;
    }
    return reinterpret_cast<Leaf *>(cur_node);
  }

  auto insert_impl(const u64 &k, const V &v) {
    ::xstore::xkv::TrivalAlloc<sizeof(Leaf)> alloc;

    // 1. initialize the pre_alloc_leaf_node
    if (unlikely(this->pre_alloc_leaf_node == nullptr)) {
      init_pre_alloced_leaf(alloc);
    }

    // 2. then do the insert
    auto ret = this->insert_core(k, v, this->pre_alloc_leaf_node);

    // leaf split
    if (ret) {
      // take out the current leaf node
      this->take_pre_alloced_leaf(alloc);
    }
  }

  /*!
    alloc: allocator that implements AllocTrait<sizeof(Leaf)>
    \ret: whether the underlying leaf has split
   */
  auto insert_core(const u64 &k, const V &v, Leaf *new_leaf) -> bool {
    bool ret = false;
    if (unlikely(this->root == nullptr)) {
      this->root = reinterpret_cast<raw_ptr_t>(new_leaf);
      ASSERT(new_leaf != nullptr);
      ret = true;
    }

    if (unlikely(this->depth == 0)) {
      // root is the now
      auto old_leaf = reinterpret_cast<Leaf *>(this->root);
      ASSERT(new_leaf != nullptr);

      // a split happens
      if (old_leaf->insert(k, v, new_leaf)) {
        //       <-  r  ->
        //  old_leaf   new_leaf
        this->root = reinterpret_cast<raw_ptr_t>(new Inner(
            new_leaf->get_key(0), reinterpret_cast<raw_ptr_t>(old_leaf),
            reinterpret_cast<raw_ptr_t>(new_leaf)));
        this->depth += 1;
        ret = true;
      }

    } else {
      // not implemented yet
      ASSERT(false) << " not implemennted";
    }
    return ret;
  }

  /*!
    alloc: allocator that implements AllocTrait<sizeof(Leaf)>
    \ret: the leaf
   */

  template <class Alloc> auto init_pre_alloced_leaf(Alloc &alloc) {
    pre_alloc_leaf_node =
        new (reinterpret_cast<Leaf *>(alloc.alloc().value())) Leaf();
  }

  template <class Alloc>
  auto take_pre_alloced_leaf(Alloc &alloc)
      -> Leaf * { // first fill the cached_copy of nodes
    if (unlikely(pre_alloc_leaf_node == nullptr)) {
      init_pre_alloced_leaf(alloc);
      ASSERT(pre_alloc_leaf_node != nullptr);
    }
    auto ret = pre_alloc_leaf_node;
    init_pre_alloced_leaf(alloc); // re-set
    return ret;
  }
};

// static member init
template <usize N, typename V>
__thread XNode<N, V> *XTree<N, V>::pre_alloc_leaf_node = nullptr;
} // namespace xtree
} // namespace xkv

} // namespace xstore
