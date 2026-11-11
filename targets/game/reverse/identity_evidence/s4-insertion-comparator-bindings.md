# S4 unguarded insertion: existing comparator bindings

Consumer: game/GameEngine/Source/Common/S4UnguardedInsertionSort.cpp. Four
existing93B sort rows keep their names, signatures, four-byte range storage
and complete bodies. Only four artificial range operator references are
replaced by existing predicate names, across EIGHT actual call sites.

## Per-family native contracts

| Existing caller | Existing predicate | Original ILT -> body | Full provider |
| --- | --- | --- | --- |
|00342CE0|Q4Sort0034BFC0::operator()(int,int)const|00024B81 ->0033D5E0|122B/RET8|
|00453090|Q4Sort004566F0::operator()(int,int)const|00024055 ->00451F60|122B/RET8|
|00453180|S4Cmp00452A50::operator()(int,int)const|00039CB1 ->00451E90|164B/twoRET8|
|007537C0|Q4Sort00755050::operator()(int,int)const|0002952D ->00752B80|465B/twelveRET8|

Providers remain in GameLogic/ScriptEngine/Q4Sort0034BFC0Comparator.cpp and
Common/{Q4Sort004566F0Comparator,S4Cmp00452A50Comparator,
Rva007527C0Comparator}.cpp. Existing named median/partition/heap callers and
row notes establish these address/context-derived predicate identities. No
new EA name, class layout, original sort identity or alias is claimed.

The four current operators compare their TWO integer arguments. They do not
read their incoming receiver. Their source is not uniformly empty-layout:
S4Cmp00452A50 and Q4Sort00755050 also declare an UNUSED one-word m_state field.
That field is not copied, read or imported into this consumer. The new
method-only declarations expose the existing public const operators and no
native sizeof, field, constructor, destructor, inheritance or virtual shape.
No suitable shared header declares these predicate types.

## Preserve the unusual bound/receiver storage

The second caller argument is still S4Range<address> with its ONE pointer
m_last, not a substituted empty/native comparator. Its first word remains the
loop bound. Its ADDRESS remains predicate ECX. The existing entry signatures,
cdecl cleanup, uncertain total second-argument width and unused trailing caller
words are NOT reinterpreted or normalized.

Both actual call sites in every93B body have operands+22hex and+43hex. Four
saved registers and two pushed dword arguments place ESP at entryESP-24;
LEA ECX,[ESP+20hex] therefore points at entryESP+8, the original second slot.
The first site schedules MOV EDI,EBP after the LEA; the second calls directly.
The check asserts those EXACT measured instruction prefixes rather than an
incorrect assumption that LEA is always the last instruction before CALL.
Each callee pops8; caller control then tests AL. The pointer view changes no
receiver value, argument bits/order, cleanup or lifetime operation.

The implementation extends only the existing local macro with a predicate
parameter and declaration, removes the obsolete range member declaration,
and calls the native operator through the original range-slot address. No
forwarding body, overload adapter, raw member-pointer bridge, assembly,
extra definition or optimizer/exception flag change is introduced.

## Exact checks and footprint

Verified original source/object were saved before editing. External definition
sets are IDENTICAL; only four intended undefined-name substitutions occur.
All four93B callers pass strict/unmasked equality with no unresolved patch
references. All eight physical ILTs are unchanged and their complete five-byte
E9 destinations are asserted. All four full providers are strict/unmasked and
completely decoded, including all sixteen normal RET8 paths across them.

Normal before AND after:15/15functions across the consumer plus four provider
TUs,4float constants,6DIR32references, no literals, zero body-guard findings.
Reproduce with the normal five-source build and
`python3 build/sol12h-bindings/check_s4_sort_routes.py`.
The source list, original source/object, callee output, gates, native root
instruction dump, route assertions and previews use the private
build/sol12h-bindings/s4-sort-* prefix. The first diagnostic's immediate-LEA
assumption failed; corrected exact native-prefix assertions pass. No source
gate was weakened or diagnostic object substituted for a verified receipt.

## Reference and current linking limits

Read-only BFME2 pin76f0baefa6f285d54bc1ca922397674312a5913f was checked for the
corresponding consumer and recipes; no exact S4UnguardedInsertionSort unit is
present. Its Code/GameEngine/Source/Common/System/Rva0021C811InsertionSort.cpp
instead uses8B nontrivial values and four arguments, including unused third
argument and a separate comparator. That is NOT evidence for replacing this
BFME1 bound/receiver slot or its4B elements. No donor body, signature, layout,
name, flags or dependency is imported. Existing source -GX- context remains
unchanged, with MSVC7.1/lane-private Wine11.16 WoW64, WINEARCH=win64, BUILD_POOL=2.

Actual before-preview:0of5clean,235.9seconds. After:0of5clean,240.7seconds;
all five units UNKNOWN with22764unavailable/currentness-changed ledger objects.
Historical2008->2008bytes are UNCHANGED, not new or currently confirmed linked
coverage. No matched or census-confirmed unique linked-byte gain is claimed.

Explicit diagnostic comparison removes exactly the four obsolete range-operator
undefined names and adds zero blockers. The failed initial private assertion
is preserved as a transcribed tool-output excerpt in
s4-sort-initial-diagnostic-failure.txt; final exact-prefix and native-byte checks
pass. Independent parent review decoded all eight routes, measured bound-slot
addressing and complete providers, and approved this caller-edge repair only.
