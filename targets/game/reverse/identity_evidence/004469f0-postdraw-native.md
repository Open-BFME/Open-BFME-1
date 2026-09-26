# InGameUI::postDraw native reconstruction

2026-09-26, GPT-6. This is a bank, not a conversion. The existing game source
and ledger owner remain unchanged.

## Extent and identity

The 3333-byte body starts at RVA `004469F0`, returns at `004476F4`, and is
followed by INT3 padding. Its last 15 bytes are
`5f 5e 5d 64 89 0d 00 00 00 00 5b 83 c4 48 c3`.
`probe.py` reports no extent warning. InGameUI vtable VA `010F5B38`, slot 75
(`+12C`, VA `010F5C64`), contains ILT `00446DAD`, which jumps to this body;
the derived table at VA `011206BC` has the same slot. The EA postDraw source
independently supplies the six-message ring, superweapon timers, named timers,
and four-rectangle RMB anchor grammar.

The oracle's `m_superweaponHiddenByScript`, `m_superweaponPosition`,
`m_namedTimerPosition`, and `m_messagePosition` names are retained. The unknown
receiver at `this+81C` stays address-derived. ScriptEngine::getCounter returns
the already witnessed ScriptCounter pointer, with `m_value` at offset zero;
the old bank's Int-pointer return declaration was not a valid symbol contract.

## Measured improvement

The old bank emitted 3292 bytes for the 3333-byte body, with normalized
instruction similarity 0.943. The preferred source now emits exactly 3333
bytes; all 121 relocation operands align. It differs at 35 of 2849 concrete
bytes, giving `(2849-35)/2849 = 0.987715`, the recorded score. Normalized
instruction similarity is 0.999. All 55 REL32 operands independently select
an existing callee address from the current resolver; no pin was added.

The improvement came from real STLport map/list iterators, the actual visible
hash lookup and recursive override bodies, explicit display-string reloads
after virtual color setters, and a ternary flash-color argument before the
shared draw tail. This preserves the relevant aliasing behavior rather than
asserting that virtual calls are pure.

Two visible helpers were checked with the strict verifier using temporary
selected rows against their already established retail owners:

* GameLogic::findObjectByID: RVA `0009A510`, 82/82 bytes, the native hash_map
  lookup already landed in GameLogicFindObjectByID.cpp.
* Overridable::friend_getFinalOverride: RVA `00097880`, 26/26 bytes, the actual
  recursive helper already owned by INIWater.cpp.

The strict helper gate passed 2/2. These definitions explain the caller's
memory reloads; they carry no new ownership or byte credit.

## Residue and preserved alternatives

The preferred source has an EBX/EBP mirror in the message loop, different
timer/string/iterator stack slots, and the adjacent `push ebp` / `mov ecx,esi`
order at `+4EF`. Every other instruction shape and every call offset agrees.
The shared timer-coordinate lifetime reduces the concrete residue from 57
to 35 bytes, but is not proof that the original source shared those locals.

The immutable source archives are:

* `0f7dcb6664200617d18f43cac2a822ccb33ab5dcf297d3e4021696ab3bf455d9.json`:
  preferred 35-byte residue, corrected witnessed names and ScriptCounter ABI.
* `7cffadc58310e4a19ef97427909f5f1f5538c5333dde7c1dc9acf0b2894e4653.json`:
  57-byte residue with independent coordinates in each timer scope.
* The earlier 0.26 bank remains archived in this address's attempt history.

Natural coordinate aggregates, iterator scopes, const/postincrement variants,
ordinary declaration order, and complete drawName/drawTime/setText helper
visibility did not improve the result. The actual GameGetColorComponents body
changed the frame adversely. Volatile-coordinate probes also worsened the
result and are not retained. A further pass needs evidence affecting variable
lifetime or register allocation; repeating these shapes has no measured value.
