# TransportContain::onContaining: native list-provider context, no byte conversion

BFME I input `72cdedeab4bda93ec099f6454b92cc568a8e7b96`;
runtime `openai/gpt-6.1-sol:high`. First current-family input follows local
bank-only commit `aed0d29908404c361d4180c9235ae160e68cb22b`.
No production source/header/type contract/pin/datum/function ledger changed.

## Identity and baseline

The existing 865-byte bank reproduces **865B, 41 relocations, two masked
byte differences** at +0x260 and +0x263. Native instruction starts +0x25F:
allocator-temp address goes to EDX then PUSH EDX; ours uses EAX.
`ilt_oracle.py` confirms the established TransportContain::onContaining name.
Matched SiegeEngineContain::onContaining RVA 0x0022B3E0 in
`RiderChangeContain.cpp` calls this base. The ContainModuleInterface secondary
view, module data at this-0x1C and owner at this-0x18, is preserved. Native
RET8 at +0x35E and following INT3 bound 865 bytes. Class admission check passes.
No broad rotation/header sweeps were repeated: prior 273-toggle/pair and
allocator-temp/noise trials were read first and excluded.

## Actual new prerequisite: the old bank has a fake destructor and wrong allocator

Current baseline includes the native Object-pointer list ownership repair in
`identity_evidence/20261111-object-list-base-contract.md` and commit
`c79eeaa70`. It is newer than the September bank. The native pointer population
and dereference chains prove `list<Object*>`, not donor `list<int>` or mere
four-byte payload equivalence. Its existing physical providers are:

* `game/GameEngine/Source/GameClient/Rva00443F60Selection.cpp`: 32B
  `list<Object*>::list(const allocator<Object*>&)`, RVA 0x000CFFB0.
* `game/GameEngine/Source/GameLogic/Object/Contain/OpenContain.cpp`: 66B
  `_List_base<Object*>::~_List_base`, RVA 0x000CEBD0, routed by ILT E68D.

The bank's inline union-call destructor emits a five-byte trampoline under the
canonical destructor name, not the real 66B provider. Replacing it with the
existing declaration-only canonical binding removes that bad definition and
uses the real OpenContain provider. Main body stays 865B/two differences.
No wrapper, alias or pin is added.

The old `_STLP_USE_NEWALLOC` constructor is deceptively **32B probe-exact**,
but its relocation at +0x0C targets `operator new` (`??2@YAPAXI@Z`). Native
RVA 0x000CFFB0 instead calls `_STL::__node_alloc<false,0>::_M_allocate` at
RVA 0x0082E540. Removing `_STLP_USE_NEWALLOC` emits the existing native
node-allocator call, retaining 32 bytes and leaving the main two-byte residue
unchanged. This is a concrete relocation/provider repair lead, not acceptance
from masked bytes. No source is promoted while the primary is nonmatching.

The corrected-context alternative is archived by normal `re_log.py --stash`;
its preferred-pointer policy may retain the equal-score older bank, so use the
`alternative=` path on this session's verdict. Do not silently use the old
preferred file's fake dtor/raw-new constructor for a landing.

## Bounded source/context trials

Reference lead: pinned donor `76f0baefa6f285d54bc1ca922397674312a5913f`,
`Code/GameEngine/Source/GameLogic/Object/Contain/TransportContainOnContaining.cpp`.
Its Bool flags, fade tail and real accessor structure are useful, but BFME 2
has other model-condition bits/virtual slots and a 665B body. Neither its
addresses nor its list<int> identity are transferred. The declaration-only
pattern is corroborated by pinned `Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp`;
BFME I native providers determine the type and allocator.

| New contextual trial | Main result |
|---|---|
| Canonical dtor declaration; old allocator | 865B / 2 masked differences |
| Canonical dtor + native node allocator | 865B / 2, retained stronger dependency context |
| Declaration-only ctor as well | 865B / 7, rejected |
| Reference rider condition accessor | 844B / 481, rejected |
| Reference owner condition accessor | 860B / 548, rejected |
| Both condition accessor chains | 844B / 513, rejected |
| Reference getPosition call directly in weapon arguments | 865B / 7, but the list allocator mismatch disappears |

The direct-position form trades the original two bytes for seven weapon-call
setup bytes (+0x1CD..+0x1DD), including one moved relocation. Source/position
locals, position reference, out-of-class accessor and actual Thing-owner
accessor forms either restore the original two differences or retain the seven.
No form resolves both. These are semantic position expressions, not dummy
register anchors. All generated variants remain private scratch.

Raw full object inventories (sections, public/data symbols, auxiliaries,
association/relocation records) for old, canonical-dtor-only and corrected
allocator contexts are `build/spike3/transport-coff-{0,1,2}.log`.
`transport-provider-context.json` retains every public undefined name and the
constructor relocation target. This is inventory, not a native linkwinner or
full coexistence proof. No actual link was attempted with an unverified primary.
Current census is absent; current family/whole closure is UNKNOWN.

## Validation and resume

All project imports/compiler/environment construction entered external
`/home/pispike/qa/bfme-spike3-20261113/game.sh` first, with private win32 prefix,
nice10/headless/pool1 and on-disk TMPDIR. Sources/objects are private outputs;
no old object or receipt was copied. Scratch include-directory stability
refused caching; compilation itself passed.

Logs: `build/spike3/transport-{repro,identity,class,full-probe,canonical-dtor,variants,position-full,position-variants,provider-context}.log`,
`transport-constructor-{old,native}.log` and `transport-provider-context.json`.
Accepted source gain is **zero**, not 865 bytes; no source category or closure
credit is inferred from this bank.

Resume on a genuinely new native/source explanation tying weapon-call
scheduling and the allocator temporary together. Do not repeat these position
forms or prior exhaustive rotation sweeps. Preserve the corrected physical
provider context in any future attempt; do not reintroduce the trampoline.
