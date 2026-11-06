# Team position and S4 AssetList link trials

The inputs are BFME 1 retail 1.03, master `cf7d438f4e`, and pinned BFME 2
reference `dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce`.

- Team position helper `0x000EDCD0`, 186 B. The standalone retail
  provider was kept. Removing the additional definition separately from
  `AIGuardIdleStateDestructor.cpp` and `GiantBirdGuardIdleState.cpp`
  changes the verified `update` body in each unit. The paired native
  gates fail 1/3 and 1/2, respectively. Both edits were restored. A
  retry must preserve the compiler's emitted caller bodies while
  avoiding the duplicate definition.
- S4 array cleanup in `S4Base0077C1F0Destructor.cpp`, 325 B at
  `0x0077C1F0`. The original array at receiver +0x134 uses a
  0x14-byte element stride. Its cleanup names a destructor through
  ILT `0x0000E746`, which reaches the native 124-byte pointer-tree body
  at `0x00140950`. The pinned BFME 2 AssetPointerSetFind.cpp and
  the existing BFME 1 declaration-only AssetList calls corroborate the
  key type. A direct tree substitution first failed with the old
  non-STLport header selection. With the existing STLport settings,
  its size guard fails. The compiler diagnostic instantiates
  `S4ShowSize<12>`. A plain tree substitution would therefore change
  the stride from 20 to 12. Preserve the original array layout and
  the exact indirect destructor target together before retrying.

The production sources and the existing function rows were restored.
