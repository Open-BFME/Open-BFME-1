# PartitionSolver::getSolution at 0x00094BF0

The 4-byte body `lea eax,[ecx+0x2c]; ret` was claimed under the opaque
`Rva00094BF0AddressPlus2C::get` because nothing tied it to a class.

Evidence that it is `PartitionSolver::getSolution() const`:

- It sits inside the PartitionSolver cluster (constructor 0x00095FB0, the
  STLport pair<ObjectID,UnsignedInt> sort helpers 0x00094D70-0x00096510, solve
  0x00096570), all built from `partition_solver.cpp`.
- The matched constructor at 0x00095FB0 lays PartitionSolver out as Zero Hour
  does: m_howToSolve +0x00, m_data +0x04, m_spacesForData +0x10,
  m_currentSolution +0x1C, m_currentSolutionLeftovers +0x28, m_bestSolution
  +0x2C. Zero Hour's getSolution returns `m_bestSolution`, i.e. this+0x2C.
- ScriptActions::doLoadAllTransports (0x003014C0, executeAction arm 52 =
  TEAM_LOAD_TRANSPORTS) calls it through ILT 0x00013A7A with ECX = its stack
  PartitionSolver immediately after `solve()` (ILT 0x0000117C) and passes the
  result straight to the SolutionVec copy constructor, exactly Zero Hour's
  `SolutionVec solution = partition.getSolution();`.
- Retail was linked without identical-COMDAT folding, so the body has one
  identity; the opaque name asserted none.

The Zero Hour source in `partition_solver.cpp` compiles to the retail bytes
(probe: 4/4, exact). The opaque definition is removed from
Rva0008TinyBodies.cpp in the same change.
