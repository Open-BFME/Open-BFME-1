# 0x0036A570 `AttributeModifierPoolUpdate::applyAttributeModifier` — SOLVED

**Landed 2026-09-29** at 1037/1037 bytes, 0 non-reloc differences, as clean
C++ in
`game/GameEngine/Source/GameLogic/Object/Update/AttributeModifierPoolUpdate_applyAttributeModifier.cpp`
(`?applyAttributeModifier@AttributeModifierPoolUpdate@@QAE_NABVAsciiString@@H@Z`).

## The answer: the residue is a block merge, not a spelling

Everything below was measured against the 0.997 stash
(`targets/game/reverse/attempts/0x0036a570.cpp`, since removed by `add_match`)
and is kept because the lever is reusable — the same one almost certainly
reaches `0x0024ECA0` slot `+0x78`, whose residue is the adjacent
`mov ecx,esi` / `push edi` order.

The `push 0` of the second argument must be emitted **in a predecessor block**
and the call itself must be the merge point. Write the guarded FX call once per
arm of the `isModifierActive` test:

```cpp
if(isModifierActive(frame,it)) {                       // retail +0x220 arm
    FXList *fx=(FXList*)store->primaryValueAt(it->m_index,getObject());
    if(fx) { Object *object=m_object;
             if(!fx->bfmeIsBlocked())fx->doFXObj(object,0); }
} else {                                               // retail +0x230 arm
    FXList *fx=(FXList*)store->secondaryValueAt(it->m_index,getObject());
    if(fx) { Object *object=m_object;
             if(!fx->bfmeIsBlocked())fx->doFXObj(object,0); }
}
```

Each arm keeps its own `push 0`; the two arms merge on the shared tail, which
is retail's `mov ecx,esi; push ebx; call` at `+0x25c`. Written once after the
test — the spelling the previous five sessions searched — there is no merge, so
the front end emits the whole argument sequence and sinks the receiver copy
under it: `push 0; push ebx; mov ecx,esi; call`, three bytes off.

The witness is `?doThisConnectionRound@NAT@@IAEXXZ` (`0x006726B0`, matched clean
C++ in `game/GameEngine/Source/GameNetwork/NAT_doThisConnectionRound_BFME.cpp`),
whose two `setConnectionState` arms push their state constants and merge on
`mov ecx,esi; push edi; call` at `+0xBD` while its single call at `+0x10`
sinks. So the discriminator is **whether the call is a merge point**, not the
argument's spelling, type, constness, register or constantness. That is why
1170 rotation toggles and ~60 argument spellings could not reach it.

Measured this round, all on the real body:

| variant | result |
| --- | --- |
| guarded FX block duplicated into both `isModifierActive` arms | **EXACT** |
| same, with `Object *object` hoisted above the `if` and shared | 414 diffs |
| same, with one `FXList *fx` local and the guard shared | 3 diffs |
| `Bool blocked = fx->bfmeIsBlocked();` then `if(!blocked)` | 3 diffs |

## History (the search this beat)

Measured 2026-09-28 against the 0.997 stash: 1037/1037 bytes, 3 non-reloc
differences, all at the receiver copy for the existing-modifier FX call at
`+0x25c`.

## The residue

The only divergence is the placement of the receiver copy for the
existing-modifier FX call at `+0x25c`:

```
retail                                ours
  025a 6a 00        push 0            025a 6a 00        push 0
  025c 8b ce        mov ecx, esi      025c 53           push ebx
  025e 53           push ebx          025d 8b ce        mov ecx, esi
  025f e8 ...       call doFXObj      025f e8 ...       call doFXObj
```

Everything else, including the *structurally identical* FX call in the
new-entry path at `+0x36a` (`push 0; push edi; mov ecx, esi; call`), matches.

## This is not a spelling of the call (superseded: it is not a spelling, but it is a *block*)

`MSVC 7.1` sinks `mov ecx, <receiver>` below the whole argument-push sequence
for a two-stack-argument `__thiscall` in every source shape tried. Measured
in a scratch TU (`build/lab_callshape.cpp`, `build/lab_call2.cpp`,
`build/lab_call3.cpp`, `build/lab_nat.cpp`, `build/lab_fw*.cpp`): direct,
virtual, `__fastcall`-free, guarded, ternary, alias, early-return, in-loop,
3-argument, receiver from a member, receiver from a nested member, argument in
EAX/ECX/EDX/EBX — every one ends `push a; push b; mov ecx, R; call`.

Every one of those scratch shapes is a call that is **not** a merge point.
Duplicating the call into two arms that merge is a different shape and it
reaches retail — see the answer at the top. The negative result stands only
for a single call in a single block, which is what the whole search above
tested.

## Retail reaches it, and the matched bodies say how often

`6a XX | 8b c? | 5? | e8` (immediate argument, receiver copy, register
argument, call) occurs **three** times in the whole image. Two of the three
are byte-verified matched C++ bodies, so the shape is reachable in real source:

* `?detectionTest3WaitForResponsesUpdate@FirewallHelperClass@@QAE_NXZ`
  (`0x0066F6A0` +0x23, matched,
  `game/GameEngine/Source/GameNetwork/FirewallHelper.cpp`) — source
  `m_mangledPorts[i] = getManglerResponse(m_packetID + i);` inside a
  `for` loop. Reproduced exactly by a 20-line scratch TU.
* `?doThisConnectionRound@NAT@@IAEXXZ` (`0x006726B0` +0xbb, matched,
  `game/GameEngine/Source/GameNetwork/NAT_doThisConnectionRound_BFME.cpp`) —
  source `setConnectionState( i, NATCONNECTIONSTATE_DONE );`. The *same
  function* also contains the sunk form at +0x10
  (`setConnectionState( i, NATCONNECTIONSTATE_NOSTATE )`), where the constant
  `0` is materialised in a callee-saved register and pushed with `push ebx`.

So the placement is a per-call-site decision by the list scheduler, not a
property of the call expression. In the scratch labs, the only two-argument
shape that reproduced the unsunk order had a **16-bit** first argument computed
by a 16-bit op (`add ax, si`); the 32-bit equivalents sank. The 0x0036A570
argument is a 32-bit pointer preloaded into EBX before the guard call, which is
the sunk case.

## The best counter-witness: the same callee, the same spelling, sunk

`?performUpgradeFX@UpgradeMuxData@@QBEXPAVObject@@@Z` (`0x002D9B30`, matched,
`game/GameEngine/Source/Common/Thing/UpgradeMuxData.cpp`) calls the *same*
`FXList::doFXObj` through the *same* ILT `0x00022BBA` with the *same* source
spelling this body needs:

```cpp
const FXList *fx = m_fxListUpgrade;
if (fx && !fx->isEmpty())
    fx->doFXObj(object, 0);
```

which retail compiles to the sunk order at +0x17 (`mov eax,[esp+8]; push 0;
push eax; mov ecx,esi; call`). The other `doFXObj` site in this body — the
new-entry call at +0x31d, which carries the identical source text — is sunk
too. One matched body elsewhere and the twin site inside this function all sink
the receiver copy for `doFXObj(object, 0)`; only `+0x25c` does not.

Note also that the NAT pair shows a register-argument push (`push edi`) landing
*after* the receiver copy in one call and *before* it in another of the same
function, so "the argument is a register" and "the argument is a constant" are
both irrelevant to the placement.

The same family is still open elsewhere in the repo: `docs/shape_levers.md`
line 1312 records `0x0024ECA0` slot `+0x78` as "the residual is the adjacent
`mov ecx,esi` / `push edi` order", with local-alias orders, a `__fastcall`
table trial, `/Oi`, `/Ot` and pragma trials all failing. **Next lever for that
row:** the one this body used — make the call a merge point by writing the
identical guarded call in both arms of the branch that selects it, so each arm
keeps its own argument push and the shared tail is `mov ecx,esi; push edi; call`.

## Levers already measured on this body (all leave exactly 3 diffs)

`tools/rotation_sweep.py --pairs` (1170 toggles, singles and pairs); default
argument on `doFXObj`'s second parameter, with and without omitting it at the
call site; `getObject()` / `this->m_object` / `getObject()` twice as the
argument; `const Object *` and top-level-`const` parameter declarations; a
`const FXList *` receiver; a nested `{ }` block; a `switch` guard; `== false`,
`!= true`, a named `Bool blocked` local, a `(void)` cast; the `&&`-merged
guard; `fx` assigned by ternary; unused `int` / `Object *` locals in the block
and at function scope; a barrier; `false`, `NULL`, `0L`, `(const Object *)0`,
`enum = 0` as the second argument; swapping the argument order;
`AttributeModifierEntry &e = *it`.

Second session (2026-09-29) added, all leaving exactly 3 diffs unless noted:
declaring `bfmeIsBlocked` `const` as its proven mangled name `QBE_NXZ` says
(3), that plus a narrow `static inline doFX36A570(fx, object)` helper (3),
that plus `const Object *object` (3), `Object *const object` (3), the
`performUpgradeFX` `const FXList *` + merged-`&&` spelling (15 diffs, breaks
the block), the same without the object local (15), a single `object` local
shared with the new-entry path (compile error: the inner `Object *object`
shadowing removal leaves the new path's local undeclared), `Object *object`
declared *after* the blocked check (24 diffs), a `const Object *none = 0`
second argument (3), `if (blocked) {} else call` (3), `if (blocked == true)
{} else call` (6), an `FXList &f = *fx` reference (3), `(*fx).doFXObj` (3),
`do { ... } while (0)` (3), a `static inline` wrapper holding the whole
`if (fx) { if (!blocked) ... }` (15), `doFXObj` declared non-`const` (3) and
with an `int` second parameter (3), `#pragma optimize("t", on)` (3),
`#pragma optimize("i", on)` (3), and `#pragma optimize("t", off)` (841
diffs, i.e. `-Od`, confirming the pragma is honoured at all).

Superseded verdict (kept for the record): register/schedule-private residue at
this site, in the same family as the `0x0024ECA0` row in
`docs/shape_levers.md` ("the residual is the adjacent `mov ecx,esi` /
`push edi` order") and the `bfmeKey0052CDA0` receiver-sink row. The scratch
harness to re-run any of this in ~1.5 s per variant is `build/lab36a570.py`
(compile + masked byte diff) driven by `build/lab_var.py`
`run(name, old, new, extra=[(old, new), ...])`; the batches written across the
sessions are `build/lab_batch1.py` .. `build/lab_batch11.py`.

## Re-banking note (2026-09-29) — moot, the body landed

`tools/re_log.py record ... partial --stash` currently **cannot** re-bank this
body unchanged: it first re-archives the *previous* stash with
`score_kind="author-estimate"`, while
`attempt_history/0x0036a570/163a44c7….json` was written with
`score_kind="measured"`, and the immutable-archive check refuses the mismatch
(`ValueError: immutable attempt archive differs`). A session with no
improvement should therefore record `blocked` (no `--stash`) and leave the
preferred 0.9971 body alone. The stash is unchanged on disk
(`md5 0295e1aa49162288b8c3f39ebdd83fe4`).
