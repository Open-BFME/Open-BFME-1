# Ability abort: one existing public squared-gap provider

Only `game/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate_isWithinAbilityAbortRange.cpp`
changes. The existing full 372 B `SpecialAbilityUpdate::isWithinAbilityAbortRange`
at `002A65C0` retains its identity, signature, module/object fields, offsets,
range arithmetic, target/position branches, BFME power-type `0x27` adjustment,
return handling and all geometry code. This is one caller-edge repair, not a
new body recovery or original class/method naming claim.

## Exact bounded interface

The old unused declaration `Object::getDistanceSquared(const Object*) const`
is removed. Its one call instead uses the existing public
`Gen_000ED3B0::bfmeGapSq(const Gen_000ED3B0*) const` at `000ED3B0` (75 B,
`game/GameEngine/Source/Common/Bfme5NinetyEight.cpp`). The supervisor approved
this single signature-only, pointer-only view before editing. Both existing
Object addresses are passed unchanged through const pointer casts; no object,
state, field, constructor, helper, storage, nominal class ownership, adjusted
subobject, header, provider, raw bridge, member-pointer union or pin is created.
No actual Gen class layout is imported into this caller.

The provider's witnessed finite-value behavior is
`square(max(0, sqrt((self.x-other.x)^2+(self.y-other.y)^2)-self.radius-other.radius))`:
x/y are actual `+38/+3C` float reads and radii are actual `+BC` reads on both
objects. It is a clamped **2D radius gap squared**, NOT generic 3D center
Euclidean distance. The opaque existing provider name/class is not promoted
to an original EA identity or asserted canonical Object declaration.

## Full native ABI/control-flow proof

`callees.py 0x002A65C0 372` and prior attempt records were read before editing.
At root `002A65D3`, `mov ebx,[ecx+8]` loads the original self Object. The target
lookup result remains in EAX then ESI, checked for null before the call:
`push esi; mov ecx,ebx; call ILT00043CED` at `002A662F` (REL32 operand `+70`).
That original five-byte E9 thunk reaches the full 75 B `000ED3B0` provider.
The old and new receiver/pointer argument addresses are therefore identical;
no hidden parameter, adjustment, constness loss or stack conversion occurs.

The full strict/unmasked provider loads its sole argument from `[esp+4]` and
has two `RET4` exits. The negative-gap path discards the gap then FLDs pooled
zero into ST0; the other duplicates and multiplies the gap, returning the
square in ST0. Both restore the same x87 stack depth. Root's next instruction
remains the original jump to `002A66B9`; it loads/squares the module's
`+1F0` abort range and compares/pops the original ST0 distance. No store/reload,
integer/EAX conversion, precision/lifetime change or control-flow rewrite is
introduced. Both complete root/provider are verified unmasked, not inferred
from the old pin or a coincidentally matching caller alone.

## Geometry is entirely UNCHANGED and remains independent debt

The existing `BfmeSubYR::bfmeDoYR(void*,void*,void*,void*,int)` char-return
geometry call is untouched. So are the original force-inline geometry helper,
orientation float/int union, all five argument words, `GeometryInfo` placeholder,
Object fields/offsets, zero-angle macro and direct route to `0087F2F0`. The native
`test al,al; setne al` result normalization remains at `002A6715/002A6718`.
No bool prototype, float signature, geometry-header adoption, raw/member-pointer
bridge or access experiment is performed or authorized. Its old unresolved
provider reference/independent linking debt remains OPEN. The other existing
point-gap helper is likewise unchanged. Existing inline convenience definitions
are not counted as new recovered native identities or current-link winners.

## Whole object, native gates and limitations

All **13 actual sections** (eight non-debug/five debug), raw instruction/data/
directive/debug bytes, section flags and every relocation match by exact public
owner/associated identity after ONLY the one intended undefined-name
substitution. All 13 complete section auxiliary records—including COMDAT
selection/checksum/association graph/reserved fields—match. All **seven public
definitions** remain with identical type/storage/offsets, including the three
pre-existing inline helpers and three float data definitions. No code/data/
helper/alias/weak definition is added or removed. This preserves selection
metadata, NOT an observed current-link winner or whole-image layout.

All-section inventory SHA256:
`4d4c7b9a285fab71f9d639b62641e3059f3b28d998fa71cb9a07abb173ada791`.

Before/after normal unified consumer + actual provider gates: **3/3 functions
across two TUs**, 12 float constants, 11 DIR32 references, zero literals/skipped
refs/body findings. The unrelated existing Bezier sibling in the provider TU
is also strict/unmasked and unchanged. Original source compiler contexts stay
unchanged; all builds use the approved private WoW64 prefix, WINEARCH=win64,
BUILD_POOL=2, WINEDEBUG=-all and empty DISPLAY/WAYLAND_DISPLAY. No compiler
variant or shared input is added.

Corrected, strictly sequential preview: before **0/2 clean**, 207.6 s;
after **0/2 clean**, 188.5 s. Both retain 1 UNKNOWN / 1 independent-debt
verdict, with all selected names stale and **22,732** cold/changed ledger
objects unavailable. Historical LINKED **150 -> 150** remains unchanged,
not current coverage. Exactly the old `getDistanceSquared` unresolved
diagnostic disappears; the old geometry unresolved reference and all other
selected diagnostics remain unchanged, none added.

The first purported
before-preview raced the changed caller rebuild while its census initialized:
its own stale-symbol list already contained the NEW gap provider. The zero-delta
negative-control assertion caught this error before review/publication. Both
invalid logs and the failed-delta output are retained with `abort-gap-invalid-*`
names; they establish NO before measurement or gain. The original source is
restored and normally rebuilt; the corrected before preview was awaited
in full before reapplying this one edge and rebuilding/measuring after. The
original copied before object versus changed object inventory remains a valid
independent one-substitution footprint comparison. No new matched bytes,
current confirmed linked-byte gain, actual provider selection or closure is
claimed, especially for the explicitly untouched geometry edge.

## References and prior evidence

Read-only BFME 2 revision `76f0baefa6f285d54bc1ca922397674312a5913f`,
`Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdateIsWithinStartAbilityRange.cpp`
provides its related abort predicate and public opaque distance call
`self->rva00263763(target)`. It is semantic context, not proof of BFME 1
addresses, naming, method constness or object layouts. The existing BFME 1
372 B root is nonconst; it is not changed to match that reference.
Zero Hour `GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate.cpp`
at the abort predicate explicitly uses `FROM_BOUNDINGSPHERE_2D`; its partition
manager call is not transplanted. BFME 1's own complete 75 B provider, both
physical Object addresses, x/y/radius reads and full native caller establish
this one edge. No donor tree, pointer, layout, address or API is modified or
imported. Older root attempts' x87/register-shape failures are not reopened.

Private artifacts in `build/sol12h-bindings/`: `abort-gap-{before-build,after-build,link-before,link-after,routes,footprint}.log`,
`abort-gap-{before.cpp,before.obj,callees.txt,native.txt,sources.txt,prior-attempts.txt}`,
`abort-gap-footprint.json`, exact claim log and
`check_abort_gap_{routes,footprint}.py`.
