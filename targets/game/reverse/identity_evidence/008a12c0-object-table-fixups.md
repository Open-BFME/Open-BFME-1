# RVA 008A12C0: object-table fixups

The owner and method retain the bank's address-qualified names. The source does
not promote this body to a semantic Apt identity. Its incoming ECX accesses
counts at +0C/+20, the object-pointer array at +10, and 16-byte named records at
+24. The sole direct call is the independently matched thiscall
Rva008A1050Owner::findNamedSlot at 008A1050; its table and entry declaration
matches Rva008A1050FindNamedSlot.cpp.

## Boundary and dispatch

Independent PE/Capstone decoding reads a complete RET 8 at +17A..+17C:
381 executable bytes. Three alignment bytes (8D 49 00) occupy +17D..+17F.
The six DWORDs at VA00CA1440 (+180) are 00CA13F5, 00CA136E, 00CA1422,
00CA1422, 00CA1333, 00CA134B, corresponding to kinds 3 through 8.
They end at +198; the following bytes are padding. The compiled COFF span is
408 bytes including that alignment and table. Probe compared the entire span
and reported zero non-relocation differences. An independent read of the
production COFF relocations resolves its same-section labels +135/+AE/+162/
+162/+73/+8B to precisely those six retail VAs (all addends zero). Its
code operand at +6F names local label +180, agreeing with VA00CA1440.
The ledger retains the 381-byte executable extent; no padding is claimed.

Live Ghidra creation/decompilation corroborates both loops and all switch arms,
but creation initially reported an incomplete 142-byte flow range before the
switch was recovered. The PE bytes, not that initial range, establish the extent.
The historical log phrase saying the 381-byte size includes the table is false.

The indirect callback is cdecl with three stack arguments (argument 2 of this
method, record index, record +8). The existing global spelling
?g_bfmeSlot23VB@@3P6AXXZA is pinned to VA01337894, the operand at +7F;
its existing install site is BfmeOneHundredTwentyThree.cpp. The typed call view
preserves that global's existing declaration. No new global or callee pin is used.

## Reconstruction

The supplied bank had an incorrect break after a nonempty kind-4 entry loop.
Retail's back edge at +E5 reaches +E7, restores the outer index, and continues
into the +3C link fixups at +EB. The corrected source preserves this path.

The first call needs a local receiver loaded directly from m_namedEntries[i],
while its name argument remains an indexed expression. Combining this with
an in-class reference-taking slot helper (inlining enabled) reproduces the
retail load order, explicit slot-address LEAs, and the later SIB operand order.
The helper only performs the real index-to-pointer fixup; it asserts no
extra memory-effect contract. No assembly, volatile fields, or barriers are used.

Validation: add_match scoped build verified 1/1 functions and the sole external
DIR32 against the recorded global. All six switch-target relocations and the
switch-base relocation were independently checked as described above.
