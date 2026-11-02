# Material-vector ID slots: corrected overload and declaring-class evidence

Link queue #31, `??_7?$DynamicVectorClass@PAVVertexMaterialClass@@@@6B@`,
claim FBD5D165. This is partial identity progress, not a repaired provider.

- [Reproducible compiler witness](witness.cpp.txt)
- [Arguments, input hashes, vtable relocations and exact body bytes](proof.json)
- [Earlier table investigation](../0113c614-material-vector-slots-20261101.md)

## New BFME 1 findings

The earlier investigation leaves the ID overload order uncertain and proposes
a base-class pointer ID at slot 4. The target bytes disprove that mapping:

| Native table slot | Target RVA | Complete size | Operation | Compiler-emitted owner/signature |
| --- | --- | --- | --- | --- |
| 4 (+0x10) | 0x00930210 | 38 | Search active elements for the referenced value | DynamicVectorClass<VertexMaterialClass*>::ID(VertexMaterialClass* const&) |
| 5 (+0x14) | 0x00930270 | 25 | Convert an element address to its array index | DynamicVectorClass<VertexMaterialClass*>::ID(VertexMaterialClass* const*) |

At 0x00930210, `[ecx+0x10]` supplies ActiveCount, the argument is
dereferenced, and the loop compares it with each four-byte entry from
`[ecx+4]`. Missing values return -1. RET 4 is at 0x00930233; INT3 starts
at 0x00930236. VectorClass's value search instead uses VectorMax at +8
and checks IsValid: this is the derived value-search override.

At 0x00930270, IsValid at +0x0C is checked, then the argument address
minus Vector at +4 is divided by four. RET 4 at 0x00930286 is followed
by INT3 at 0x00930289. This is the pointer-address overload.

The existing WWLib/vector.h declares pointer ID first, value ID second,
and DynamicVectorClass overrides **both**. Its pointer override forwards
to VectorClass::ID; inline forwarding does not imply a base-class vtable
owner. MSVC 7.1's emitted table names the derived pointer override and
inlines the base operation into its own 25-byte body. The overload slots
appear in reverse declaration order.

## Compiler evidence

A new-expression for DynamicVectorClass<VertexMaterialClass*> compiled
with normal /O2 /GR- plus /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS and the
existing WWLib/WWDebug include directories emits a 24-byte vtable. Its
relocations +0x10/+0x14 name the two derived overrides above. Their
complete bodies match every retail byte (38/38 and 25/25) with **zero
relocations**. This establishes more than instruction-shape similarity.

The include trace confirms the actual header is
`game/Libraries/Source/WWVegas/WWLib/vector.h`; no donor header was used.
All compiler output was private under build/task-queue-20261102/material-vector.
To reproduce, copy witness.cpp.txt into a private build/ .cpp, compile
through build.try_compile_source with an explicit private .obj, and inspect
the two named symbols with build.read_object_symbol_bytes.

The witness's deleting-destructor slot names ??_E, while retail's 30-byte
slot-0 body is scalar-shaped. This witness does not settle that slot's
identity, nor justify copying the complete emitted vtable.

## Scope and remaining work

Both unchanged consumer units pass the normal scoped build (3/3 rows).
The bounded link_check previews remain UNKNOWN because the original dirty
submodule differs from staged inputs; the available census index is also
older than the queue. No linking gain is claimed.

The current slot-4 row is a PrototypeLoaderClass value-search instantiation;
slot 5 is a Render2DClass base-pointer alias. Their target identities need
normal evidence-backed ledger corrections, followed by the other slots and
the emitting providers. No ledger, pin, alias or shared header was changed.
This note supersedes the slot-4/5 owner proposals and note 2/3 in the earlier
investigation; its table-address and constructor evidence still applies.

BFME 2 revision 92f12c3 was reviewed via git show: corresponding
Code/Libraries/Source/WWVegas/WW3D2/MaterialInfoClassCtor.cpp and vector
repair records confirm the table spelling but do not prove BFME 1 slot
identities. All new overload/order/body findings here come from BFME 1's
header, target and compiler witness. No donor adaptation was applied.
