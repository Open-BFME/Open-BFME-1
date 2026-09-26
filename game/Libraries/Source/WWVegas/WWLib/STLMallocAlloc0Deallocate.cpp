// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082B100 is STLport's
//   _STL::__malloc_alloc<0>::deallocate(void*, size_t)
// (?deallocate@?$__malloc_alloc@$0A@@_STL@@SAXPAXI@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_alloc.h; it is emitted
// under the object symbol the ledger pins for this row.
//
// Retail built the STLport alloc helpers unoptimised, hence /Od above: the
// pointer is reloaded from [ebp+8] before the dllimport free call.

extern "C" __declspec(dllimport) void __cdecl free(void *);

extern "C" void __cdecl
bfme_MallocAlloc0Deallocate_82B100(void* __p, unsigned int)
{
  free((char*)__p);
}
