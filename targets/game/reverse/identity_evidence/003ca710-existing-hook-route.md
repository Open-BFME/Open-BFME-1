# Existing hook route used by RVA 003CA710

The complete 140-byte flag-refresh body makes one shared machine call at
003CA76A after pushing the same entry + B4 pointer twice. It calls ILT
00041164, then caller-pops eight bytes and compares the full EAX result
with one. The original ILT bytes are E9 37 81 38 00, independently resolving
to the existing 100-byte body at 003C92A0.

That body reads two 32-bit stack arguments and uses a plain return. Its
fallback pushes both words, calls ILT 0002A7C5 and caller-pops eight bytes;
its hook path passes the argument addresses to the existing constructor.
It consumes no incoming ECX receiver. Independent matched callers at
003CAE00 (45 bytes) and 003CAE40 (89 bytes) repeat the same two pushes,
original ILT call, caller cleanup and full-width result comparison.

BigObfHookWrappers.cpp already defines Rva003C92A0 as int __cdecl(int, int).
It is the unique retail-true selected provider in the accepted census;
the old bfmeCallFHA spelling has only unresolved references and a diagnostic
stub. This repair uses the existing signature. Explicit pointer-to-int
casts preserve the argument words on the original 32-bit compiler target;
this is not a portable 64-bit API redesign or a new semantic name claim.
No alias, pin, provider, shared header or link ordering is changed.

The entire caller TU passes its 140-byte row after the change. At the sealed
82dc61ee38 census, the supported source-scoped preview changes from
LINKED 0 -> 0 before to LINKED 0 -> 140 after, with the old unresolved name
removed and no other caller blocker. Caller/provider/witness source and
relevant ledger hashes remain identical to the sealed accepted evidence
before the repair. This is a scoped preview, not a current full census.

The provider TU remains separately blocked by other unresolved names,
duplicate and address debts. In particular this wrapper still references
g_Slot012BE394 and Gen003C78B0. Its transitive dependencies and the other
four consumers of the old spelling are outside this narrow caller repair.
