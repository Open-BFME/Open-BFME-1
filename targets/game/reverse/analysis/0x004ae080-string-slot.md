# 0x004AE080 -- ControlBarSchemeManager::setControlBarSchemeByPlayer

**LANDED 2026-09-28.** Retail 590 B, `ret 4` at +0x24B, now a clean C++ body at
`game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarSchemeManagerSetControlBarSchemeByPlayer_4AE080.cpp`,
byte-verified 590/590 by `add_match`. The whole frame story below is history:
what it took was the parameter-home alias **plus** reading the side through an
in-class `Player::getSide()` accessor instead of a raw `+0x28` cast. See "The
last four bytes" at the foot of this note for that lever and for the two
spellings next to it that miss.

The sections below are the seats' evidence trail, kept as written.

Retail 590 B. The banked attempt that preceded the landing was the
parameter-home alias spelling, measured at 590/590 B with **4 non-relocation
differences, first at +0x1A6, shape 1.000**. The prior best bank was 590 B,
33 differences, shape 1.000, measured quality 0.9441; its predecessor was
571 B, 368 differences, shape 0.951.

## Earlier best: communicator block solved; frame-slot assignment unresolved

At that stage, every one of the 33 remaining bytes was a stack displacement.
That body was instruction-for-instruction retail's, including the branch
polarity, the two constructor call sites, the EH state values 0/1/2, the loop
structure, the x87 sequence and the funclet.

### The spelling that works

```cpp
if (communicatorButton && TheControlBar)
{
    if (TheRecorder->isMultiplayer())
    {
        ControlBarSchemeAsciiString a("NonCommand_Communicator");
        TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton(a) );
    }
    else
    {
        ControlBarSchemeAsciiString a("NonCommand_BriefingHistory");
        TheControlBar->setControlCommand(communicatorButton, TheControlBar->findCommandButton(a) );
    }
}
if(!p)
    return;
{
    ControlBarSchemeAsciiString side = *(const ControlBarSchemeAsciiString *)((const char *)p + 0x28);
    ControlBarScheme *currentScheme = m_currentScheme;
    ... the rest of the Zero Hour body unchanged ...
}
```

The Zero Hour two-armed if/else with a **named** string in each arm is right;
the named strings are the only part that was ever in doubt. The price is the
**one nested block around the whole tail**. That block is the whole trick:

* with `side` at function scope, MSVC 7.1 gives the two arm strings two frame
  slots, the two arms' tails do not merge, and the body is 630 B / 380 diffs /
  shape 0.942 (`_side$ = -28 _a$3702 = -24 _a$3705 = -20`);
* block-scoping the tail takes the function-scope local out of the way, the
  allocator is free to overlap the two sibling arm scopes, and the arms become
  one slot (`_tempScheme$ = -20 _a$3705 = -20 _a$3702 = -20 _this$ = -16`).
  Two identical arm tails then merge, which is retail's shape.

This is `docs/shape_levers.md`, "A frame four bytes too big: put the local in
its own block": *a local declared at the top of the function blocks the
overlap*. It was read as being about a compiler temporary versus a user local;
it is equally about **two user locals in two sibling blocks**, and the blocker
is a function-scope local anywhere in the function, even one declared *after*
the two blocks that need to overlap.

Do not re-try the whole "communicator block is a codegen wall" family. Four
seats called it a wall; it is a scope-placement rule.

### Retail's block, reproduced exactly

```
0062 test al, al
0064 lea  ecx, [esp+0x14]      ; &obj, hoisted ahead of the branch, dead
0068 je   +0x83
006a push "NonCommand_Communicator"
006f call AsciiString(char const *)
0074 lea  ecx, [esp+0x14]
0078 mov  dword ptr [esp+0x24], 0
0080 push ecx
0081 jmp  +0x9a
0083 push "NonCommand_BriefingHistory"
0088 call AsciiString(char const *)
008d lea  edx, [esp+0x14]
0091 mov  dword ptr [esp+0x24], 1
0099 push edx
009a ... shared tail: findCommandButton, setControlCommand, one releaseBuffer
```

One object, two constructor call sites, EH states 0 and 1, one destructor in
the shared tail. The merge works because the arms differ only in the
string constant and the state value, not in the address of the object.

## The last 33 bytes: which local takes the dead parameter home

Retail's frame is `sub esp, 0xc` and holds three objects; `tempScheme` is in
the dead `p` parameter home. The banked body allocates two frame slots and
puts `side` in the parameter home instead, so every displacement is four low
and the frame is one dword short.

| object | retail | banked |
|---|---|---|
| command name (both arms) | `[esp+0x14]` | `[esp+0x10]` |
| `side` | `[esp+0x10]` | `[esp+0x28]` (dead `p` home) |
| list iterator | `[esp+0x18]` | `[esp+0x14]` |
| `tempScheme` | `[esp+0x2c]` (dead `p` home) | `[esp+0x10]`, shared with the name |
| `this` | `[esp+0x1c]` (the `push` slot) | `[esp+0x18]`, same slot, four low |

So exactly one swap is needed: `side` must be the bottom frame object and
`tempScheme` must be the local the dead parameter home is given to.
`docs/shape_levers.md` says the home goes to a **block-scoped** local and that
"which block-scoped local wins the slot is still open". **That question is now
answered and it answers against the body** — see "The last 33 bytes are
closed" below: the home goes to the first *class* local in a nested block, which
is always `side`, and the only escape (function scope) disables slot overlap
for the entire function.

Measured and rejected, all leaving the same 33 bytes:

| change | result |
|---|---|
| `side` at function scope, rest in a block | 630 B, 380 diffs, 0.942 |
| one outer block around the arms and the tail | 507 B, 348 diffs, 0.736; the SEH prologue collapses and `this` is never spilled |
| `side` direct-init instead of copy-init | 590 / 33 / 1.000, unchanged |
| tail in two sibling blocks | 612 B, 375 diffs |
| tail in a doubly nested block | 507 B, 348 diffs |
| `currentScheme` / `tempScheme` / `it` declared in a different order | 584-710 B, MSVC starts duplicating objects |
| `for`-form loop | 488 B, 327 diffs |
| bare temporaries instead of named locals in the arms | 590 / 33 / 1.000, unchanged |
| `const` `side` | does not compile (`side.set` needs a non-const object) |
| two-statement `tempScheme` | 590 / 33 / 1.000, unchanged |

## Earlier conclusion (superseded): parameter home prefers a class local (2026-09-28)

A second seat measured the two rules the open question turns on, with the
`/FAsc` slot table as the oracle, and they are jointly unsatisfiable.

**Rule 1 — one function-scope local with a slot disables *all* frame-slot
overlap in the function.** Not just the documented "a local at the top blocks
the overlap": with `side` at function scope the two communicator objects stop
sharing *and* stop overlapping the iterator, so nothing is packed at all.

| variant | frame | slots | size |
|---|---|---|---|
| banked (`side` block-scoped in the tail block) | `sub esp,8` | arms+`tempScheme` -20, iterator -24, `side` **+8** | 590 / 33 / 1.000 |
| `side` function scope, rest in a block | `sub esp,0x10` | arms -20 and -24 (split), `side` -28, `tempScheme` **+8** | 630 / 380 / 0.942 |
| same, rest not in a block | `sub esp,0x10` | as above | 630 / 380 / 0.942 |
| Zero Hour spelling (name is an unnamed temporary), `side` function scope | `sub esp,0x10` | two temporaries -20 and -24 (split), `side` -28, `tempScheme` **+8** | 630 / 380 / 0.942 |
| unused function-scope `int` (eliminated, no slot) | `sub esp,8` | unchanged | 590 / 33 / 1.000 |

So `side` at function scope *does* hand the dead parameter home to
`tempScheme`, exactly as retail does — and it costs 40 bytes, because it turns
off every overlap in the function.

**Rule 2 — the dead parameter home goes to the first CLASS local in a nested
block**, never to a POD while a class local competes, and neither declaration
order nor block nesting changes that.

| variant | who takes `+8` |
|---|---|
| banked | `side` |
| `tempScheme` declared *and initialised first* (its `xor esi,esi; mov [..],esi` now precedes the `side` copy ctor) | `side` |
| `tempScheme` declared first, assigned after the `isEmpty` check | `side` |
| `currentScheme` first, then `tempScheme = 0`, then `side` | `side` |
| `side` in the outer tail block, `tempScheme`+loop in a nested block | `side` |
| `tempScheme` in the outer tail block, `side` in a nested block | `side` |
| tail block opened *before* `if(!p) return;` | `side` |
| extra sibling block around the communicator `if`; arms nested one level deeper | `side` (unchanged, 590 / 33) |
| a second short-lived class local `probe` added after `side` | `side` (`probe` takes frame slot -20) |

**The proof that this closes the body.** `q1` above is the informative one: add
one short class local in its own nested block after the `isEmpty` check. The
frame becomes `sub esp,0xc` and the slot order becomes *exactly retail's* —
`_probe$ = -20`, arms+`tempScheme = -24`, iterator = -28 — with `side` still
in the parameter home. Retail is the same three slots in the same order with
`side` at -20, the name alone at -24 and `tempScheme` in the parameter home.
Every remaining byte therefore follows from the single parameter-home
assignment; nothing else about the frame is in dispute.

Retail's source has `side` as a block-scoped class local (its copy ctor at
+0xd7 and its `releaseBuffer` at +0x228 are one scope-exit cleanup, EH state 2)
and yet the home holds a POD. In the original spelling, `side` took the dead
parameter home; function-scope `side` disabled overlap. The parameter-home
alias below resolves placement without changing compiler or `/F` switch, so
this conclusion applies only to those earlier spellings.

## Frame model (solved)

MSVC 7.1 counts the return address as part of the frame, so with `E0` = the
caller's esp *before* the call, the body's esp is `E0-40` and:

| displacement | address | holds |
|---|---|---|
| `+0x10` | E0-24 | bottom frame slot |
| `+0x14` | E0-20 | middle frame slot |
| `+0x18` | E0-16 | top frame slot |
| `+0x1c` | E0-12 | the `push fs:[0]` slot; retail stores `this` here and the epilogue's `mov fs:[0], ecx` reads it back |
| `+0x20` | E0-8 | the `push handler` slot |
| `+0x24` | E0-4 | the `push -1` trylevel slot, which is also the EH state variable (states 0, 1, 2, -1) |
| `+0x28` | E0+0 | return address |
| `+0x2c` | E0+4 | the `Player *` parameter, reused for `tempScheme` and the `fild` scratch after `p` dies |

The `[esp+0x24]` state store that looks like it addresses the return address is
the trylevel slot, and `[esp+0x2c]` is the dead parameter home.

## Tools that made this cheap

- `python3 tools/probe.py SRC.cpp '?setControlBarSchemeByPlayer@ControlBarSchemeManager@@QAEXPAVPlayer@@@Z' 0x4AE080 [--all|--shape]` -- `--shape` reporting **1.000** is the signal that only allocation is left.
- Add `/FAsc /Fa<relpath>.cod` to the `// cl:` line and read the `_name$ = -NN` table: it is the only reliable way to see which objects share a slot.
- `python3 tools/dis_retail.py 4AE080` for the retail listing.
- `build/work/s2/` in this worktree holds the sweep harness (`batch.py` prints frame/size/call counts, `scopes*.py` are the scope sweeps, `slot.py` and `slot2.py` are the standalone models that show VC7.1 does overlap sibling-block objects in a dynamic frame with an SEH record). It is untracked scratch.
- `build/work/w3/` holds the second seat's harness: `gen.py` (substitute the tail of the banked body), `try.py NAME...` (probe each variant, print size/diffs/first-diff/shape), `slots.py NAME...` (recompile with `/FAsc` and print the `_name$ = -NN` table), `v*.py` generate the named variants in `build/work/w3/v/`. All of it is untracked scratch.
- `build/work/w4/` holds this seat's harness: `base.cpp` (copy of the banked stash), `gen.py`, `v/{A,B,C,D}.cpp`. All untracked scratch.

## Absolute-address proof: the residue is exactly one swap (2026-09-28)

Both bodies execute identical push/add sequences (shape 1.000), so esp is
identical at every instruction and only the frame base differs (ours 4 higher:
`sub esp,8` vs `sub esp,0xc`). Pairing the displacements gives absolute
addresses (offsets from retail's post-prologue esp `E_b`):

| object | retail | banked | same address? |
|---|---|---|---|
| communicator name | `[esp+0x14]` | `[esp+0x10]` | YES (base+0x14 both) |
| `side` | `[esp+0x14]` at +00d3 (one push outstanding) = base+0x10 | `[esp+0x2c]` = dead `p` home | NO |
| `tempScheme` | `[esp+0x2c]` = dead `p` home | `[esp+0x10]` = base+0x14, shared with the name | NO |
| iterator | `[esp+0x18]` | `[esp+0x14]` | YES (base+0x18 both) |
| `this` spill / EH state / `p` home | fixed slots | same absolute | YES |

So the name and the iterator sit at byte-identical addresses in both builds.
The ONLY placement differences are `side` (retail: bottom frame slot;
ours: parameter home) and `tempScheme` (retail: parameter home; ours: the
name's slot). All 33 diffs are that one swap plus the 4-byte frame shift.
No other object, ordering, EH state, or register choice is in dispute.

Correction to the frame-model table above: the body esp after the prologue is
`E0-44`, not `E0-40` (3 SEH pushes + `sub esp,0xc` + 4 register pushes below
the return address), so every `E0-` label in that table reads 4 high; the
relative conclusions (three contiguous frame slots + home) are unaffected.
Retail's slots are `side` = E0-28, name = E0-24, iterator = E0-20, home = E0+0
(`p` is thiscall's first stack param, so the home is E0+0, not E0+4). The
`push` at +00d2 explains why `side`'s construction displacement (+00d3
`[esp+0x14]`) numerically equals the name's: one push is outstanding, so it
addresses the next slot down.

Consequence for future levers: anything that does not change which object
takes the dead parameter home at `side`'s birth cannot move a single byte.
`p`'s last use is the copy source (`+00cf add eax,0x28; +00d2 push eax`), so
the home is free exactly as `side` is born and MSVC hands the destination the
source's dead home. Keeping `p` alive longer would need a second `p` use that
retail does not have (all post-copy `[esp+0x2c]` traffic is provably
`tempScheme`: the NULL init at +012e, the loop reads, the `fild` scratch
reuse). Giving the home to an earlier-born object needs an earlier class local
that retail's instruction order has no room for (copy at +00d7 precedes the
first tail load at +00dc).

## This seat's variants (all worse; stash unchanged, still 590/590 33/1.000)

| variant | change | result |
|---|---|---|
| A | drop `currentScheme`, use `m_currentScheme` directly (ZH-faithful) | 590 B, 40 diffs, 3 structural at +00ea |
| B | A + ZH unnamed-temporary communicator spelling | 590 B, 40 diffs, 3 structural (same as A) |
| C | A + loop/iterator in a further nested block | 590 B, 40 diffs, 3 structural (same as A) |
| D | A + `tempScheme` declared before `side` | 591 B, 219 diffs, 7 structural |

Finding: `currentScheme` is load-bearing for REGISTER allocation, not just a
style extra. Without it the early-return compare becomes `lea ecx,[eax+0xc]`
plus a `mov ecx,[edi]` reload (variant A `--shape`), versus retail's
`lea ecx,[esi+0xc]` / `mov ecx,esi`: the POD local pins `m_currentScheme` in
esi across the `compare(side)` call. ZH gets away without it; this TU does
not. Do not remove it. The communicator temp spelling (B) and iterator depth
(C) are neutral, as before; declaration order (D) is catastrophic, as before.

## Parameter-home alias breakthrough; four register-order bytes remain (2026-09-28)

After the earlier bank, explicitly reusing the dead incoming `Player *p`
parameter slot closes the placement gap:

```cpp
Player *&tempScheme = p;
tempScheme = 0;
...
if(!tempScheme || ((ControlBarScheme *)tempScheme)->m_ScreenCreationRes.x <
                    CBScheme->m_ScreenCreationRes.x)
    tempScheme = (Player *)CBScheme;
```

This is after the null return and after the `side` copy, when the original
parameter value is dead. The alias makes the parameter home live as
`tempScheme`, so VC7.1 keeps `side` in the bottom frame slot instead of placing
it over `p`. Casts are needed only where the reused `Player *` value is viewed
as a `ControlBarScheme *`. The result reproduces the retail frame size, every
stack displacement, communicator construction/EH shape and the rest of the
590-byte instruction stream. Probe: **590/590, 4 non-relocation bytes,
shape 1.000**.

The only remaining differences are the order of the two callee-saved reloads
at +0x1A6/+0x1AA: retail loads the list iterator into EDI then `tempScheme`
into ESI; the alias spelling loads the same values in reverse order. The
allocation-only `rotation_sweep.py` found exact scratch-only hypotheses by
wrapping the communicator-button initializer or either command argument in its
temporary identity inline. Those wrappers are probe devices, not source to
land. Natural local-copy, split-assignment, reference-alias, typed-alias and
register-qualified spellings did not reproduce the extra allocation step.
`shape_family_levers.py` (4 variants) and `eh_levers.py` (8 sampled of 128)
also did not improve the alias body. Keep the earlier 590/33 body as history;
the new alias source is the preferred bank, but is not a byte match.

## The last four bytes: an in-class accessor, not a cast (2026-09-28, landed)

The residue was the order of two callee-saved reloads at the loop back edge
(+0x1A6/+0x1AA): retail reloads `this` into EDI and the dead parameter home
(`tempScheme`) into ESI, the alias body reloads them the other way round.
`alloc_residue.py` classes it as **callee-saved**, which
`allocation_residue.md` says the rotation lever does not reach.

`rotation_sweep.py` nevertheless confirmed a synthetic identity inline in
argument position as EXACT, and mapped the sites: the communicator button's
initialiser, the guard, `TheRecorder->isMultiplayer()`, arm 1's two arguments,
`TheControlBar->findCommandButton` -- all in the communicator block, none of
them in the shared tail. Fourteen natural respellings of those sites all miss:
named locals for the window manager, the name key generator, the recorder, the
control bar and the display; `NAMEKEY()` in the Generals header form
(`static`, `inline`, `static __inline`); a `__inline` accessor for each global;
dereferenced receivers (`(*TheControlBar).findCommandButton`); a NULL macro or a
cast for the first argument; a `const char *` local for either button name; a
cast on the button, the found command or the name argument; a comma operator.
None of them emits a byte, and none of them moves the reload order.

What does work is a **member call the front end can inline**: the address of
the side string has to come out of a function, not a cast.

```cpp
class Player
{
public:
	const AsciiString &getSide(void) const
	{
		return *(const AsciiString *)((const char *)this + 0x28);
	}
};

AsciiString side = p->getSide();
```

The `/FAsc` listing shows why the search was so unproductive: the identity
inline and the plain cast emit **identical** code, and only the front end's
label counter differs (its temporaries are numbered from 3701 in the plain
body and from 3707 with the wrapper, 3712/3718, 3758/3764, 4081/4095). The
lever is invisible in the object file and shows up only as a reordering
hundreds of bytes away, which is why four seats read it as a register wall.

Three neighbouring spellings, all measured, so the next seat does not repeat
them:

| spelling | result |
|---|---|
| accessor defined **in the class body** (above) | **EXACT**, 590/590 |
| same accessor defined out of line as `inline` after the class | 590 B, 4 diffs |
| Generals' by-value `getSide()` (`return m_side;`) | 587 B, 311 diffs, first +0xC4 |
| named member `p->m_side` behind `char pad[0x28]` | EXACT (same effect) |
| a `const char *` local for either button name | 590 B, 4 diffs |
| a static free function returning the side pointer | 590 B, 4 diffs |

The by-value row is the one the retail bytes also rule out independently: two
copy constructors would be called, and there is one (+0xD7) with a single
`releaseBuffer` at +0x234, so BFME's accessor returns a reference. The in-class
versus out-of-line row is the front end's inline-visibility, nothing to do with
codegen quality.

Landed with `Player::getSide()` in the class body, the string view named
`AsciiString` (the pinned `findCommandButton` and `findControlBarScheme`
symbols are mangled over that name, so the real one resolves and the sibling
0x004ADE40's invented `ControlBarSchemeAsciiString` view is not needed), and
the naked `__emit` lift deleted.
