# SaveLoad constructor bank: loop and outgoing callback lifetime

This is an improved bank, not a conversion or an identity claim. The inherited
BfmeAptScreenSaveLoad label and callback spellings remain experimental here.
The factory/table and sibling destructor locate the screen, but do not meet the
current rule for newly asserting all those C++ identities. No production source,
ledger, or symbol pins change.

## Independent retail evidence

Raw unpacked retail bytes and Ghidra FUN_0096e980 agree on the 1719-byte extent:
RVA 0056F034 is `C2 04 00`, followed by INT3 at 0056F037. The exception handler
C35536 points to FuncInfo E24A9C, with sixteen states. States 2 through 13 and
15 clean an AsciiString at EBP+4. State 14 cleans an outgoing holder pointer
at EBP-50 through ILT 803A -> 464AA0; state 0 instead uses saved-this at EBP-54.

The loop beginning at 56EE2A is not an assignment of the hook result back to
the loop value. EDI keeps the value from ILT 3C65A -> 56DEC0. The hook/fallback
result in EAX is compared to 993BA311, while subsequent calls use EDI. ILT
43CBB -> 56DFC0 is called twice, first for the table index and again for the
registration argument, with each result narrowed by MOVSX from AX. ILT 3F7CE
-> 56DF40 supplies the *next* value in EAX, carried back to EDI. The original
bank instead overwrote the value with the comparison result, cached the index,
and discarded the step result. The final background call pushes EBX=1, not 0.

The existing Obf0056D5E0 constructor reads its two pointer arguments without
writing through them, writes receiver offsets 0..1C, and ends with RET8 at
56D688, then INT3. Its native 171-byte emission independently probes exact
(two relocation sites). The bank now uses this real constructor and the native
Rva0056DE40 wrapper definition from BigObfHookWrappers.cpp, with its original
one-instruction ESP selector. Exposing the real constructor hoists the constant
argument initialization out of the loop as in retail. No dummy purity body was
used. Other wrappers retain their existing names and are explicitly noinline.

## Measurements and remaining work

All measurements use the requested Proton environment, original retail image,
and probe.py with size1719. The served stash emitted1682B/398 differing bytes,
measured quality0.7254; its old0.912 was normalized instruction similarity.
Restoring the loop alone emitted1695B/406dif. Correct nontrivial by-value callback
construction restored1719B/296dif. The canonical string header, signed reference
count, virtual-destruction view, real helper names and definitions, and corrected
background argument yield the final1714B/293dif, measured quality0.8237.

The frame remains44h versus retail50h; saved-this and callback temporaries occupy
different homes. The state14 transition is still absent around the second index
call despite a generated cleanup action; control-flow/code scheduling also differs.
A const-reference binding constructor and /EHsc- left the native result unchanged;
removing forceinline from the callback constructors regressed the extent to1680B.
The original48-byte hook-state facade was wrong: the real constructor/wrapper uses
32 bytes. Restoring that extent was necessary, not a padding lever.

The bank is shortened to this body and its dependencies and includes ascii_string.h.
It retains the older synthetic base/manual vptr model and experimental callback,
registry and list-payload views. Their identities, canonical outgoing holder types,
base lifetime, and all DIR32/REL32 bindings must be reconciled before promotion.
The helper's masked equality is not a strict proof of those caller bindings.

The first normal commit attempt rejected dropping two inherited descriptive helper
spellings. The final bank retains them as inline forwarders to canonical wrappers,
without adding aliases to symbols.csv or changing the actual called bodies. The
recorder remeasures that final source; the earlier receipt remains part of the audit.
