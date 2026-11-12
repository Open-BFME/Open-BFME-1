# Skirmish apply: three public native bindings, existing helper debt retained

Only `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/SkirmishScreenStateApply.cpp`
changes. Existing `SkirmishScreenState::apply(void*,int)` at `0052AAD0` retains
its full 443 B extent (442 non-padding census bytes), signature, class/storage,
owner calls, slot loop, control pointers, flags, strings and lifetime/EH logic.
No original-EA method identity or newly matched bytes are recovered.

| Old undefined call | Existing provider | Original ILT | Full body |
| --- | --- | --- | --- |
| `j_0003029c(SkirmishScreenState*)`, fastcall | `SkirmishScreenState::rva00529BE0()` | `0003029C` | `00529BE0`, 186 B |
| `refreshPlayerTeamControl(int)` | `SkirmishScreenState::rva005294F0(int)` | `0002D38A` | `005294F0`, 1214 B |
| `refreshPlayerFactionControl(int,bool)` | `SkirmishScreenState::rebuildTeamCombo005268F0(int,bool)` | `0002EA91` | `005268F0`, 544 B |

These are existing compiled provider names, not newly invented opaque names or
promotion of guessed public labels. `005268f0-team-combo.md` independently
explains the false legacy faction spelling, same slot receiver and actual team
combo role; the existing 1214 B sibling and native guard source preserve their
own address-bearing identities.

## Existing unrowed helper is NOT an identity/ownership repair

The baseline source had inline `bool shouldRefresh(){return j_0003029c(this);}`.
It emits an external **5 B** single-JMP COMDAT named
`?shouldRefresh@SkirmishScreenState@@QAE_NXZ`, with one REL32 operand. It is an
unrowed artificial/source-convenience helper, NOT the complete retail 186 B
method at `00529BE0`. The former shouldRefresh ILT naming inference was
contradicted by the existing ilt_oracle evidence; equal dispatch destination
does not make the helper a retail identity or an alias for the full body.

Before any source edit, the supervisor authorized a strictly preserved-footprint
experiment: retain this pre-existing helper's exact name, signature, visibility,
inline context and 5 B bytes, but retarget its call expression to the existing
public `rva00529BE0()` provider. The consumer's inline guard uses the same native
route. No helper is removed/renamed/added; no new alias, wrapper, body, pin,
access bridge, hierarchy, provider/header rewrite or original name is introduced.
This leaves the artificial helper/ownership debt explicitly OPEN. It is not
endorsed as an EA method, recovered provider or current-link winner. No current
root-selection claim is made from its presence or the passing inventory.

## Physical ABI and full-code evidence

`callees.py 0x0052AAD0 443` was read before editing. The strict full consumer is
unmasked with no unresolved relocations. Its three original E8 ILTs remain:

- Guard: REL32 operand `+1C`, before which `mov esi,ecx` saves (but does not
  change) the incoming receiver; no argument is pushed. Old fastcall's one
  pointer parameter was already in ECX, and the new thiscall has zero stack
  parameters. Native receiver is therefore unchanged, no EDX/stack adjustment
  or result conversion is introduced, and the next instruction still tests AL.
  The separate full 186 B provider has three plain RET0 exits.
- One-argument control refresh: operand `+94`, `push edi; mov ecx,esi`, where
  EDI is the original descending slot index. The full 1214 B provider RET4
  consumes precisely that dword.
- Team combo: operand `+9D`, `push ebx; push edi; mov ecx,esi`. The earlier
  unchanged `xor ebx,ebx` supplies full zero for the false Boolean; EDI remains
  the same slot index. The full 544 B provider reads the second argument as a
  byte Boolean and RET8 consumes both original words.

The retained source helper remains exactly `E9 <REL32>` (five bytes), same
COMDAT identity/type/storage and one relocation, now to `rva00529BE0`. It has
no receiver/stack/AL conversion or extra machine code. This is a preserved
artificial helper edge, NOT a new matched native five-byte function.

Both complete combo providers, the complete guard and the existing provider
cleanup funclet are included in the normal gate. Additional strict diagnostics
verify all five scoped rows. The gate's pre-existing funclet note resolves stale
`$L6438` to actual `$L6203` in the UNCHANGED 1214 B provider TU; this is explicitly
reported, not a provider/ledger/pin edit or byte mismatch. No source in that TU
is changed.

## Whole COFF and EH footprint

All **15 actual sections** (nine non-debug/six debug), every raw code/data/
directive byte, relocation and section characteristic match by exact exported
definition or associated-owner key after ONLY the three intended undefined-name
substitutions. All **15 complete section auxiliary records**, including COMDAT
selection, checksum, association identities and reserved/high fields, match.
SafeSEH symbol indices resolve to the same handler; the consumer's `.text$x`
cleanup/handler and `.xdata$x` unwind/FuncInfo records remain identical. A
separate ordinal-runtime comparison also passes, normalizing only defined
static-label identities and SafeSEH indices, not dropping EH data.

All five public definitions—including the existing artificial helper—remain
unchanged, with exactly three undefined substitutions and no weak externals,
new code/data/helpers/aliases or hidden lifetime/cleanup change. Selection
METADATA/eligibility is preserved; actual chosen providers and whole-image
layout remain unverified under UNKNOWN.

All-section inventory SHA256:
`6b3fda25395f0414be77677798de9a6deb783ed880165e76ea70ef15fe63faf2`.
Non-debug runtime SHA256:
`a2eb1a37901530a397cd6df981bc07b1ebe5c556b07ac3a66166b11d684be142`.

## Reference and prior attempts

Read-only BFME 2 `76f0baefa6f285d54bc1ca922397674312a5913f`,
`Code/GameEngine/Source/GameClient/GUI/MpGameSetupSlots.cpp`, near its
`AptMpGameSetup::rva00442BCC` guard, was reviewed. It gives only a related
encoded-slot loop lead, with six widget arrays rather than BFME 1's four guard
arrays. Its comment calling BFME 1's guard shouldRefresh is NOT independent
original naming proof and is not adopted. Native BFME 1 class/slot callers,
complete guard/combo bodies and existing identity records establish these
bindings. No donor address/layout/name/identity, source or gitlink is imported.
The prior 186 B loop-shape attempts and existing team-combo naming/ABI evidence
were read; this does not retry the old body reconstruction or naming inference.

## Validation and current limits

Before/after normal unified consumer + actual provider gates: **5/5 functions
across four TUs**, five literals, 16 DIR32 references, zero skipped refs and
baselined body findings. `find_declared_unmatched.py` reports all source
functions matched under its existing parsing rules; the artificial helper is
still explicitly unrowed debt, not converted by that message. Builds retain
the source's existing `/O2 /DNDEBUG /MD /EHsc` context and approved private
WoW64 prefix, WINEARCH=win64, BUILD_POOL=2, WINEDEBUG=-all, empty displays.
No compiler variant or shared build input is added.

Before preview: **0/4 clean**, 204.8 s, 2 UNKNOWN / 2 independent-debt
verdicts. After: **0/4 clean**, 203.8 s, 3 UNKNOWN / 1 independent-debt. All four
selection sets remain stale; 22,734 cold/changed ledger objects cannot be read.
Historical LINKED **728 -> 728** is unchanged, not current confirmed coverage.
Exactly three old unresolved diagnostics disappear; all duplicate/COMDAT/other
selected diagnostic counts remain, none added. No newly matched bytes, current
confirmed linked-byte gain, helper ownership closure or whole-unit/image closure
is inferred from these three repaired references.

Private artifacts in `build/sol12h-bindings/`: `skirmish-{before-build,after-build,link-before,link-after,routes,footprint,runtime-coff}.log`,
`skirmish-{before.cpp,before.obj,helper-before.txt,callees.txt,native.txt,sources.txt}`,
`skirmish-footprint.json`, `skirmish-runtime-coff.json`, exact claim log,
`check_skirmish_routes.py`, `check_skirmish_footprint.py`,
`check_skirmish_runtime_coff.py`.
