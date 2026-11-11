# S3SeedPairsForms: bind eighteen missing names to existing providers

Base `a40562fc69a2b17474024ff8f6b4e28e67da9bd4`. Consumer-only change in
`game/GameEngine/Source/Common/S3SeedPairsForms.cpp`; no shared header,
provider source, ledger identity, pin, alias, or exception-baseline changes.
All46caller row identities/extents and all field offsets remain unchanged.

## Contracts established from BFME1

The fetched9ac0d06c54 census lists18unresolved symbols for this unit. Each is
an invented per-caller accept declaration or an obsolete free-function view
of an already implemented body. Fresh checked-callee output for every caller was read before editing;
existing provider declarations, relevant source contracts and the normal
provider byte gates corroborate the replacement interfaces. The old and new
calls have these exact routes:

| Existing provider | Encoded ILT | Body | Repaired sites |
| --- | --- | --- | --- |
| `Gen0016B140::handle(FlagPairTarget *)` | 00002379 | 0016B140 | 7 |
| `Gen0020F330::handle(FlagPairTarget *)` | 00031557 | 0020F330 | 2 |
| `Gen_002077D0::bfmeSeed(BfmeSeedTarget *)` | 0003689A | 002077D0 | 1 |
| `Rva001EF3D0Caller::invoke(FlagPairTarget *)` | 000160B3 | 001EF3D0 | 1 |
| `Rva00776AC0Owner::rva00776AC0(Xfer *)` | 00011CBB | 00776AC0 | 1 |
| `Gen_002D9B90::bfmeSeed(BfmeSeedTarget *)` | 00029DAC | 002D9B90 | 3 |
| `Gen_005FF940::bfmeSeed(BfmeSeedTarget *)` | 00031A07 | 005FF940 | 1 |
| `FXParticleSystem::RenderObjectDrawModuleInfo::DoXfer(Xfer &)` | 000328EE | 005F6670 | 1 |
| `FXParticleSystem::LightningDrawModuleInfo::DoXfer(Xfer &)` | 0003EA86 | 005F4260 | 1 |
| `bfmeHandOver_0000FFE2(BfmeSeedTarget *, void *)` | 0000FFE2 | 000E66F0 | 1 |
| `Rva0010C1A0(MidVirtualSlot90Receiver *, void *)` | 00020586 | 0010C1A0 | 1 |

Member providers receive the unchanged original receiver/subobject address
in ECX and one pointer/reference stack word (RET4). Free helpers preserve
argument order and cdecl cleanup; the existing pointer return from
bfmeHandOver_0000FFE2 is unused by this caller. No second overload or body is
introduced. The receiver casts do not claim the opaque caller classes are
original EA classes, nor do they import provider field layouts.

The FX classes already have a native header: include it rather than inventing
private class copies. Calls are explicitly class-qualified because retail
calls these bodies directly even though the declarations are virtual. The
Xfer reference expression passes the existing target address without a load
or receiver adjustment. The four old member-address marker types remain
empty, so their enclosing storage and offsets do not grow with the real
provider types. Only their nonexistent method declarations are removed.

The compiler context adds exactly the four existing native provider include
roots needed by that header; optimization, EH and runtime flags are unchanged.
A private before-state object and current verified object have **identical
external definition sets**. Exactly18undefined names disappear and exactly
the11provider names above appear: no header-induced helper, template or data
definition, or unrelated external dependency is added.

## Donor review and limits

Consulted read-only BFME2 pin76f0baefa6f285d54bc1ca922397674312a5913f.
Narrow searches for the S3SeedPairs/FlagPairTarget spellings in Common, AI and
FX sources found no equivalent caller-unit repair to transfer. Reviewed
`Code/GameEngine/Include/GameClient/RenderObjectDrawModuleInfo.h` and
`LightningDrawModuleInfo.h`, plus `Source/GameClient/FXParticleSystemModules.cpp`.
The donor separates these declarations into headers, with configurable
pointer/reference transfer signatures and target-specific layouts/addresses.
Those donor layouts, addresses and header switches are not imported.
BFME1's native header, full provider bodies and witnessed call sites establish
this repair; donor spelling is not identity or ABI proof. Gitlink unchanged.

## Validation

Lane-private Wine11.16 WoW64/MSVC7.1 runner, supervisor-approved WINEARCH=win64,
BUILD_POOL=2. Before and after consumer gates46/46exact. Full normal source
gate over consumer plus all9provider TUs: **797/797** functions,
**47/47** data rows,46literals+4empty strings,93float constants,
1089DIR32 references, zero body-guard findings. Eight existing FX-bulk unwind
labels are reported as renumbered; their bodies still pass the normal gate.
No EH pin is edited by this lane.

A strict diagnostic uses build.compile_function (not masked disassembly):
all46caller rows exactly equal retail, and all20repaired call sites name the
correct provider and encode the exact ILT/E9 destination pairs in the table.
Private reproducible artifacts: `build/sol12h-bindings/check_seed_routes.py`,
`seed-routes.log`, `seed-symbol-delta.txt`, `seed-callees.txt`,
`seed-providers-build.log`, and `seed-provider-census.txt`.

Historical providers:5of9units linked (Guarded, Sweep, Gen0016B140Handle,
BodySnapshot0020F330 and Rva00776AC0ModelTransfer). Other providers retain
broader call/data/COMDAT debt: FlagPairThenDirectCallers19unresolved,
MidVirtualSlot90Forwarders58unresolved, Hoisted4unresolved+1wrong-selected,
FXbulk270unresolved+50duplicates+78losers+81wrong-selected. These existing
provider-family problems are not altered or excused here. Historical
consumer3571non-CC bytes are not new matched or census-confirmed linked bytes.
Current286.1-second preview reports0of10units link cleanly: consumer and the
five historical linked providers are UNKNOWN because22795current ledger
objects cannot be read here; four remaining providers still report concrete
unresolved/duplicate/selection blockers. Consumer has no remaining explicit
unresolved-name diagnostic. LINKED9,990->9,990aggregate, consumer0->0;
no census-confirmed gain is claimed. After a formatting/redundant-cast cleanup,
the final normal consumer gate again passes46/46and the route assertions pass.
