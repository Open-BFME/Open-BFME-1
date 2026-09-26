// cl: /DNDEBUG /MD /EHsc /Od /Oi

// Retail 0x0082B700 is STLport's
//   _STL::__debug_alloc<_Alloc>::allocate(size_t)
// (?allocate@?$__debug_alloc@V__new_alloc@_STL@@@_STL@@SAPAXI@Z).
// The body below follows inputs/vendor/stlport/stl/_alloc.c; it is emitted under
// the object symbol the ledger pins for this row.
//
// Retail built the STLport alloc helpers unoptimised, hence /Od above:
// __real_n and __result live on the stack ([ebp-8], [ebp-4]). extra_before
// and extra_after collapse to the +24 / +16 constants the inlined
// __extra_*_chunk helpers produce for value_type=char.

#pragma intrinsic(memset)
extern "C" void* __cdecl memset(void *, int, unsigned int);
extern "C" void* __cdecl bfme_debugAllocInnerAllocate_82AD80(unsigned int);

struct __alloc_header {
  unsigned int __magic: 16;
  unsigned int __type_size: 16;
  unsigned int _M_size;
};

enum {
  __magic = 0xdeba,
  __shred_byte = 0xA3
};

extern "C" void* __cdecl
bfme_DebugAllocAllocate_82B700(unsigned int __n)
{
  unsigned int __real_n = __n + 24;
  __alloc_header *__result =
      (__alloc_header *)bfme_debugAllocInnerAllocate_82AD80(__real_n);
  memset((char *)__result, __shred_byte, __real_n);
  __result->__magic = __magic;
  __result->__type_size = 1;
  __result->_M_size = (__n);
  return ((char *)__result) + 16;
}
