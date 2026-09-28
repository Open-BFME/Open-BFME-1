# vector<pair<ObjectID,UnsignedInt>>::_M_insert_overflow is 0x002FED10, not 0x000960A0

Two 306-byte STLport `_M_insert_overflow` bodies for an 8-byte element have
identical code apart from their per-element `_Construct` callee (0x000960A0
calls ILT 0x000267F6 -> 0x000952A0; 0x002FED10 calls ILT 0x000060CD ->
0x000953E0). Retail was linked without identical-COMDAT folding, so they are
two template instantiations with two different element types. The ledger had
the `pair<ObjectID, unsigned int>` name on 0x000960A0 and an address-derived
element on 0x002FED10. The call graph says the reverse.

- 0x002FED10 (through ILT 0x00026198) is called by
  ScriptActions::doLoadAllTransports (0x003014C0, executeAction arm 52 =
  TEAM_LOAD_TRANSPORTS) from the one call site that both its `units` and
  `transports` push_backs share (the transports arm jumps to it at +0x117).
  Both vectors are then passed by reference to the matched PartitionSolver
  constructor at 0x00095FB0, whose signature takes `const EntriesVec &` and
  `const SpacesVec &`, i.e. `vector<pair<ObjectID, UnsignedInt>>`. No
  temporary conversion is made, so the element type is `pair<ObjectID,
  UnsignedInt>`. The other caller, the push_back at 0x003001D0, sits in the
  same ScriptActions cluster.
- 0x000960A0 (directly and through ILT 0x0002AB44) is called only by
  PartitionSolver::solve (0x00096570) and the push_back beside it at
  0x00096350. Zero Hour's solve pushes only into `m_bestSolution`, a
  `SolutionVec` = `vector<pair<ObjectID, ObjectID>>`, and it copies the
  EntriesVec/SpacesVec members by assignment, never by push_back. So
  0x000960A0 is not the `pair<ObjectID, UnsignedInt>` instantiation.

0x000960A0 is most likely SolutionVec's instantiation, but the
`pair<ObjectID, ObjectID>` name is already claimed by 0x00771870, a 268-byte
body reached only from W3DModelDraw INI parsing (push_back 0x007740E0 and
Rva007752E0ParseProbability). That claim looks wrong too, but correcting it is
outside this change. 0x000960A0 therefore takes an address-derived element
name until 0x00771870 is resolved.

The per-element `_Construct` pins follow their callers:
`BfmeElementConstruct(pair<ObjectID, unsigned int>)` moves from ILT 0x000267F6 to
0x000060CD, and 0x000267F6 takes the address-derived `BfmeRva000952A0Construct`.
The synthetic `BfmeRva002FED10Construct` pin retires with its element type.
Both TUs re-verify byte-exact (306/306).
