# vector<pair<ObjectID,ObjectID>> (SolutionVec) lives at 0x000960A0 / 0x00096350, not 0x00771870 / 0x007740E0

PartitionSolver::solve (0x00096570) is byte-exact from the Zero Hour source in
partition_solver.cpp. Its `m_bestSolution.push_back(std::make_pair(
m_data[i].first, spacesStillAvailable[j].first))` inlines the SolutionVec
push_back and calls `vector<pair<ObjectID, ObjectID>>::_M_insert_overflow`
through ILT 0x0002AB44 -> 0x000960A0. So:

- 0x000960A0 (306 B) is `vector<pair<ObjectID, ObjectID>>::_M_insert_overflow`
  (it carried an address-derived element after
  000960a0-002fed10-objectid-pair-overflow.md), and 0x0002AB44 is its thunk.
- 0x00096350 (62 B, gen-tgrid) is the out-of-line SolutionVec push_back: it
  calls _Construct through ILT 0x000267F6 (0x000952A0) and the overflow through
  ILT 0x0002AB44, and partition_solver.cpp's push_back compiles to it exactly.
- The pair<ObjectID, ObjectID> names sat on W3D-side twins: 0x00771870 (268 B
  insert, a different code shape with an out-of-line _M_clear), its thunk
  0x00022AF7, and the push_back 0x007740E0 (a byte-alias of
  partition_solver.cpp's COMDAT). They are reached only from W3DModelDraw INI
  parsing (0x007740E0 and Rva007752E0ParseProbability), and 0x007740E0 calls
  _Construct through ILT 0x0001FA1E, not 0x000267F6. Retail was linked without
  identical-COMDAT folding, so these are a different instantiation. 0x00771870
  and 0x00022AF7 take the address-derived element Rva00771870Element; the
  0x007740E0 claim is retired (its bytes still need an address-derived
  push_back stand-in: retail puts the __false_type tag temporary in the dead
  parameter slot, which a hand-written stand-in did not reproduce).

Helper pins follow the callers: the pair<ObjectID, ObjectID> element-construct
names move to ILT 0x000267F6, the 0x0001FA1E / 0x0002F4D2 pins take
Rva00771870Element names, and the pair<ObjectID, ObjectID> overflow pin on
0x00022AF7 is retired.
