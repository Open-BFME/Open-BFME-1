# Canonical string return at675A80 and cleanupC45460

The complete201B parent at675A80 ends with RET4 at675B46 then INT3 at675B49;
Ghidra bytes agree. The prologue push675A82 names handlerC45479, whose
FuncInfoE34D24/mapE34D0C state0 predecessor-1 names cleanupC45460.
That action tests EBP-14 mask1, clears it, loads hidden resultEBP+4 and
tail-jumps via ILTD828 to canonical AsciiString destructor5EE90. The
conditional RET atC45478 proves the complete25B action.

The body belongs to a NetCommandMsg-derived owner: Ghidra xrefs to stubVA418E99
identify tableVA111A7D0 slot0C (pointerVA111A7DC), and the stub reaches675A80.
Constructor6759B0 and destructor675B80 store that table. Their existing ledger
name is BFMENetRequestGameSpyStatsAuthKeyCommandMsg, but no original full-name
witness is asserted here: the new local owner conservatively keeps675A80.
The constructor and formatting load establish the one string at this+1C.
Its old member identifier is retained rather than adding a new semantic name.

Call675AC8 -> ILT2D204 -> matched NetCommandMsg::getContentsAsAsciiString6747C0
refutes the synthetic BfmeOrderZR::bfmeNameZR alias. The only source use was
this parent; the recovered source calls the canonical base directly. Calls675AEF to
888BC0,675AF9 to888FF0,675B1A to887B60,675B0A/675B30 to887940 establish
canonical AsciiString construction/format/copy/release, rather than the legacy
StringBaseNarrowZR/AsciiStringZR stand-ins. The new source includes its canonical
header. No standalone destructor alias is added.

The legacy bfmeDescribeZR/BfmeOrderZR names are synthetic placeholders, not
proven method/owner identities. Rva00675A80::method retains the real address.
The scratch canonical candidate matched201 instruction bytes; the production
parent and cleanup are subject to strict byte/relocation verification.
