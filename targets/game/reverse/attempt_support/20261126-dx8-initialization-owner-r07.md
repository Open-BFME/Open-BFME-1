# DX8 initialization state: existing owner and original accesses

Round baseline: `8f06fd4114796d2175b8d741984687f805391597`.
This is one initialization-state owner/reference reconciliation, not a new
function or newly emitted storage. The two real definitions already exist in
`game/Libraries/Source/WWVegas/WW3D2/dxwrapper.cpp`: protected
`bool DX8Wrapper::IsInitted=false` and
`unsigned DX8Wrapper::_MainThreadID=0`. No replacement global, header change,
access change, alias, pin, or compiler-profile change is proposed.

The real COFF definitions are `?IsInitted@DX8Wrapper@@1_NA` and
`?_MainThreadID@DX8Wrapper@@1IA`, EXTERNAL strong in the existing writable BSS.
Original BFME1 `.data` VA0134050C contains one zero byte, and VA01340570 contains
four zero bytes. The existing typed definitions and ordinary protected-member
size compiler must prove the actual sizes; zero bytes alone do not prove roles.

Six original complete bodies independently bind the bool cell: DX8Wrapper Init
0090AB60/594, Shutdown, Reset_Device, Load_Texture, MeshMatDescClass's mapper
query, and the address-labelled six-byte getter. Init's bool store is at +1EA:
`c6050c05340101`, a one-byte store of 1 to VA0134050C. Shutdown stores zero and
the remaining bodies read the same byte. All six original body hashes and
actual operand/width records are frozen in the private scope evidence.

The same complete 594-byte Init writes EAX to VA01340570 at +9C:
`a370053401`. Its preceding call at0090ABF1 reaches original RVA009DB580,
`ff257c8d3501`, which reads actual IAT VA01358D7C. The original PE import is
KERNEL32.dll!GetCurrentThreadId. The original full Init hash is
`493301e158e24529d8d584647f865ee16b24d47d3b0f2950e74c5381666c624e`.
The existing named unsigned definition/header/getter independently agree with
this producer and four-byte store. Other DX8 globals and private last-frame
counters are outside this repair.

Source plan: use the real protected lvalues inside their own class; use the
already included canonical public Is_Initted API in meshmatdesc; use exact
typed COFF references in the two header-free consumers. The latter is the
already verified IsWindowed __identifier pattern in UnclaimedGlobalGetters,
not a duplicate class, friend, access-mangling change, or another definition.
Natural compiler copies must be recorded and checked, never assumed owned.

BFME2 donor pass: read-only e2e99959950e6eebfe1ced5663aa05de320afc52,
Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp172/235 and
meshmatdesc.cpp747. Its real statics/public API support the source shape;
BFME1 original accesses and actual existing provider establish BFME1 identity.
No donor address, layout, profile, or header modification is imported.

Scope: four existing proper TUs,177 matched rows/173 unique code RVAs,
16 retained data rows, and the two newly admitted data owners (1+4 bytes).
The normal unchanged control passed177/177,16 data,556 DIR32,237 literals plus
two empty references and106 float constants, with no baselined body findings.
Six stale internal meshmatdesc funclet-label diagnostics predate this change
and are separate from byte matching. Normal before-link was0/4 clean and
LINKED0->0; older missing providers and selection debts remain visible.

Both normal add_data_match calls passed: actual protected-access sizeof and
allocation extents are1 and4 bytes, with original zero bytes at their own VAs.
The only added data coverage is5 bytes; emitted storage and new C++ coverage
are0. Both old DIR32 spellings were removed by the normal retire frontdoor.

The first candidate build refused two old cleanup labels. The unchanged
eh_state_pins tool independently proved the original parent/state/action
bindings, then its normal sole writer repinned10 rows, skipped0. The separate
postcheck proves all10, including state-index distinctions between byte twins.
The same frozen source then passed177/177,18 data and556 DIR32. No alternate
source form, manual label/parent/state edit, marker or verifier change was used.

The physical graph is1244 retained nodes plus a natural6-byte public
Is_Initted COMDAT and its16-byte associated FPO. Every retained payload and
edge is checked, with exactly5 real data-target rebindings and454 unique
compiler-local correspondences proven by actual named section owner, exact
offset, storage and type. No numeric-label arithmetic is used. Three real
runtime diagnostic arguments change: existing Non_Fatal_Log_DX8_ErrorCode
calls carry source lines2682->2680,2980->2978,2887->2885 after removal of two
extern lines. Each exact push is bound to the unchanged __FILE__, actual new
statement, same three-argument cdecl callee and12-byte stack cleanup. All
other retained instruction bytes/targets, data, EH, FPO, weak, CRT, SafeSEH and
COMDAT relationships are preserved. These unrowed methods earn no body credit.

The new getter copy is NOT an invented matched owner. A fresh complete native
proof over22997 current objects and1904 verified data rows includes all
Weak/alternatename edges and335489 referenced names. Seven current retry
receipts were revalidated by the unchanged native current/check methods;
missing/stale counts are0 before and after, all source/tool/input/object
snapshots are stable, and the index is unchanged. Both actual getter copies
have no retail-address verdict and no ledger owner; neither is globally
referenced. Native keep_rule returns unreferenced with no losing copy.
This is the sole admission basis for the additional6+16 bytes, not byte
similarity, a local no-reference observation or an old receipt.

Before/after scoped legacy42237 previews remain0/4 clean, LINKED0->0
(238.1s/370.6s); old g names disappear in all four scopes. The after preview
also reports selection-currency UNKNOWNs for9 dxwrapper and10 meshmatdesc
sibling names against its old index; it is not a current selection census.
Other old unresolved/provider debts remain. The separate fresh reference
proof above does not establish a /MAP selection census or full-image link.
Normal staged FDU passes without new definitions or allowances.

Private source/object/complete inventories and closed hashes are under
diagnostics/ten-rounds-20261125-2054/bfme1/r07; the small companion receipt
manifest binds the full artifacts. No runtime, memory, crash, performance
improvement, new C++ body, or LINKED gain is claimed.
