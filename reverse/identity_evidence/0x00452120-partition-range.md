# 0x00452120: STLport partition range wrapper

The 30-byte retail body takes a four-byte predicate value followed by a
pointer to two adjacent iterator values. It loads the second iterator from
`[range+4]`, then the first from `[range]`, forms the address of the caller's
range-pointer argument slot as a temporary `bidirectional_iterator_tag`, and
pushes tag, predicate, last, first. The call at `0x00452135` reaches the ILT
at `0x00043004`, which routes to the matched STLport `__partition` body at
`0x00450B90` (`Rva00450B90PointerPartition.cpp`). The four pushes and
`add esp, 0x10` establish the cdecl call shape independently of the C++ probe.

The matched `0x00450B90` source instantiates STLport's bidirectional
partition with `Rva00450B90Item **` iterators and a four-byte
`Rva00450B90Predicate`; STLport's `_algo.c` supplies the four-argument
`__partition` template. This establishes the callee contract. It does not
identify a semantic owner for the 30-byte wrapper, so the exported name
retains its RVA. The older `bfmeDoBQG` alias at the ILT is a synthetic guess,
not evidence for this wrapper's identity.

`Rva00452120PartitionRange.cpp` compiles to 30/30 retail bytes modulo the
single call relocation. Its `_ReadWriteBarrier` only preserves the observed
load order of the two iterator fields before argument setup; a first-before-last
variant changed six instruction bytes. `tools/add_match.py` strictly verified
the replacement of the generator dump with live C++ (1/1 scoped function).
