# 0x002F8980 is the SolutionVec copy constructor

The 82-byte body was claimed as `Gen_002F8980::bfmeAssign(BfmeVectorRange *)`,
a synthetic name for "copy an 8-byte-element range into this and return
this".

- ScriptActions::doLoadAllTransports (0x003014C0, executeAction arm 52 =
  TEAM_LOAD_TRANSPORTS) calls it through ILT 0x00027B2E with ECX = the address
  of its uninitialised local and the argument = the result of
  PartitionSolver::getSolution() (0x00094BF0, returns &m_bestSolution). The
  local then enters its own EH state and is destroyed at the end as an
  8-byte-element vector. That is Zero Hour's
  `SolutionVec solution = partition.getSolution();`, a copy construction of
  `vector<pair<ObjectID, ObjectID>>`.
- The body is STLport's copy constructor: it calls the source's
  get_allocator() (ILT 0x0002EBC2 -> 0x002F19E0, which returns its hidden
  return pointer), passes that allocator and the element count
  ((finish - start) >> 3) to `_Vector_base(size_t, const allocator &)` (ILT
  0x00015ABE -> 0x002F19F0, already a tgrid _Vector_base constructor for an
  8-byte element), copies each element with placement new, stores _M_finish,
  and returns this (`ret 4`).

The two callee pins move from the synthetic BfmeSourceC::bfmeGrab /
Gen_002F8980::bfmeReserve names to the real get_allocator and _Vector_base
constructor names; both routed bodies are generated rows. The body is
re-homed to SolutionVecCopyConstructor.cpp and byte-verifies (82/82). The three
other bfmeAssign bodies in S3VectorAssign.cpp are untouched.
