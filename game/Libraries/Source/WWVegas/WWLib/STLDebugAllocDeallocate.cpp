// cl: /DNDEBUG /MD /EHsc /Od /Oi

// Retail 0x0082B780 is STLport's
//   _STL::__debug_alloc<_Alloc>::deallocate(void*, size_t)
// (?deallocate@?$__debug_alloc@V__new_alloc@_STL@@@_STL@@SAXPAXI@Z).
// The body below follows inputs/vendor/stlport/stl/_alloc.c with NDEBUG so the
// _STLP_VERBOSE_ASSERT checks vanish but the pad-scan for-loops remain.
// Emitted under the object symbol the ledger pins for this row.
//
// /Od keeps __real_p / __real_n / __tmp on the stack; /Oi inlines memset
// as the retail stosd/stosb shred.

#pragma intrinsic(memset)
extern "C" void* __cdecl memset(void *, int, unsigned int);
extern "C" void __cdecl bfme_debugAllocInnerDeallocate_82AD90(void *, unsigned int);

struct __alloc_header {
  unsigned int __magic: 16;
  unsigned int __type_size: 16;
  unsigned int _M_size;
};

enum {
  __deleted_magic = 0xdebd,
  __shred_byte = 0xA3
};

extern "C" void __cdecl
bfme_DebugAllocDeallocate_82B780(void *__p, unsigned int __n)
{
  __alloc_header * __real_p = (__alloc_header *)((char *)__p - 16);
  unsigned char* __tmp;
  for (__tmp = (unsigned char*)(__real_p + 1); __tmp < (unsigned char*)__p; __tmp++) {
  }

  unsigned int __real_n = __n + 24;

  for (__tmp = ((unsigned char*)__p) + __n;
       __tmp < ((unsigned char*)__real_p) + __real_n; __tmp++) {
  }

  __real_p->__magic = __deleted_magic;
  memset((char*)__p, __shred_byte, __n);
  bfme_debugAllocInnerDeallocate_82AD90(__real_p, __real_n);
}
