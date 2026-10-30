# 0x008460D0 Rva008460D0 (114 B)

Facts from BFME 1 retail:
- 0x008460D0..0x00846141 is a random-access `__copy` loop writing chars into
  an `ostreambuf_iterator<char>` (sputc through the streambuf, failed flag
  on EOF), returning the iterator by value; byte-identical to the
  `??$__copy@PBDV?$ostreambuf_iterator...` COMDAT that
  NumFacetsInstantiations.cpp emits.
- 0x00846B40 (matched `Rva00846B40` in Rva00846E80CopyWrappers.cpp) calls this
  address, not the canonical copy at 0x00835590; that unit spells the callee
  `Rva008460D0` (identity_evidence/0x00846b40.md), which nothing defined
  (link queue #285, census 1d5131d3f1).

The previous row `?dup_008460d0@@YAXXZ` was a gen-alias to the COMDAT copy;
the resolver binds that template name elsewhere. The address-derived name
keeps the address; the original instantiation's spelling is unproven.
