# 0x00694570 audio-worker run body: MASM dump to C++

Retail 0x00694570, 315 bytes, RET at +0x13A followed by INT3 padding (see
`00694570-masm-codegen-blocker.md` for the boundary and caller chain). The row
moves from the MASM dump `?Rva00694570@@YAXXZ`
(`game/masm_dumps/Rva00694570AudioWorkerRun.asm`) to clean C++
`?run@Rva00694570@@QAEKXZ` in
`game/GameEngineDevice/Source/MilesAudioDevice/Rva00694570AudioWorkerRun.cpp`.

## BFME 1 target facts

- Only caller: the stdcall wrapper at 0x00694700
  (`?rva00694700@@YGXPAVRva00694570@@@Z`), which passes its argument in ECX
  and calls ILT 0x000279A8, whose only target is this body. The member-function
  ABI (`__thiscall`, no stack arguments, plain `ret`) is read from the retail
  bytes: ECX is saved as `this` and the body ends in `ret` with no immediate.
- The body ends `xor eax, eax` before the epilogue at +0x12D, so it returns a
  32-bit zero; the C++ return type is `unsigned long` (the thread-procedure
  return value the wrapper passes through). The symbols.csv placeholder at the
  ILT (`?run@Rva00694570@@QAEXXZ`) spelled a void return; the row name keeps
  the same address-derived class and method token and corrects only the
  return type that the bytes witness.
- Callees (tools/callees.py): handle default ctor 0x006910E0 and value ctor
  0x006910F0, handle dtor 0x00691130, handle assignment 0x00691140,
  Gen0002857EOwner::Rva00693B00 0x00693B00, Gen0002857EOwner::Rva00694230
  0x00694230, STLport node deallocation 0x0082E5F0, IAT
  WaitForSingleObject/ReleaseMutex/Sleep.
- The identity stays address-derived. Neither the owning class nor the
  method's original name is proven.

## Donor facts (Open-BFME-2, not BFME 1 proof)

Open-BFME-2 `Code/GameEngineDevice/Source/MilesAudioDevice/AudioFileCacheLoader.cpp`
(`AudioFileCache::rva000A8437`, also address-derived there) is the same loop.
It reads the entry's use count into a named int local before the zero test
and compares `it != pending.end()` with `it = pending.begin()`.

## Byte result

With those two spellings (and no other change to the 0.9905 bank) VC7.1
`/O2 /Ob2 /EHsc` emits all 315 bytes, 15 relocations, and the retail
sentinel-in-ECX / begin-in-EAX allocation at +0x75 that every earlier
spelling missed. The `volatile` qualifier, the `register` keyword and the
donor's free `operator!=` overload are not needed: each was removed in turn
with the probe still exact. The named count local is the lever. Without it,
the begin-first compare gives 4 differing bytes and the end-first compare 3.
