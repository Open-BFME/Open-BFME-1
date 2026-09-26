// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082C580 is STLport's
//   _STL::__malloc_alloc<0>::allocate(size_t)
// (?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z).
// The body below is verbatim from inputs/vendor/stlport/stl/_alloc.h; it is emitted
// under the object symbol the ledger pins for this row.
//
// Retail built the STLport alloc helpers unoptimised, hence /Od above:
// __result lives on the stack ([ebp-4]) rather than in a register.

extern "C" __declspec(dllimport) void* __cdecl malloc(unsigned int);
extern "C" void* __cdecl bfme_MallocAlloc0OomMalloc_82B820(unsigned int);

extern "C" void* __cdecl
bfme_MallocAlloc0Allocate_82C580(unsigned int __n)
{
  void* __result = malloc(__n);
  if (0 == __result)
    __result = bfme_MallocAlloc0OomMalloc_82B820(__n);
  return __result;
}
