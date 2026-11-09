# 0x00514A40 AptInGameChat slot 2 (628 B): 19 -> 13 bytes, 2026-11-07

> `build/wf/00514a40/` paths below are untracked scratch and are not kept. The banked source is `targets/game/reverse/attempts/0x00514a40.cpp`.

Best candidate: `build/wf/00514a40/best.cpp`. Symbol
`?rva00514A40@AptInGameChat@@QAEHHPAX0@Z`. cl `/DNDEBUG /MD /EHsc`. The
`/Iinputs/reference/shims/stringinline` flag on the cl line is still present
but the TU no longer includes that header. Probe: 628/628, 13 non-reloc
diffs, shape **1.000** (allocation only). The previous bank
(`targets/game/reverse/attempts/0x00514a40.cpp`) still reproduces at
19 diffs, shape 0.995.

## What moved (new)

The setCursorTooltip by-value copy at +0x1F4 is fixed. Retail emits
`mov ecx,esp` before `mov [esp+0x2c],esp`. That needs an inline copy
constructor written as a **body call** of the private
`StringBase<unsigned short>` copy constructor:
`{ ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase( other ); }`.
The StringInline mem-initializer forwarder
`: StringBase<unsigned short>( other ) {}` gives the opposite order.
- The sibling `BfmeAptScreenInGameChatSelectedFriends.cpp` uses the same
  body-call form, but on WWLib's non-derived `unicode_string.h`.
- That non-derived class still gives 19, with the order unfixed
  (`v/ww.cpp`, `v/sbu.cpp`). The class has to stay derived from
  `StringBase<unsigned short>`, as in StringInline.
- Either argument spelling works: `other` or
  `*(const StringBase<unsigned short> *)&other`.
- The dtor form, the `str()` form and the inline vs out-of-line base dtor
  make no difference (36-way sweep `v/cls_*`: every body-call variant
  gives 13, every mem-init variant gives 19).
- Landing needs a TU-scoped class view or a new shim. The shared
  StringInline.h must not be edited, because its rule 2 is proven for
  other bodies.

## Remaining 13 bytes (unchanged since the 0.97 bank)

In the status 1/4 arms (1 tail-merges into 4) and the APT:Null arm, retail
loads the GameText vtable into EAX and the by-value slot pointer into EDX,
and `lea eax` gives format's `this`. Ours uses arm 2's choice in every arm
(EDX vtable, EAX slot, `lea ecx`):
```
+01ac retail: mov eax,[ecx]; push edx; call [eax+0x28]; lea eax,[esp+0x38]; push eax
      ours  : mov edx,[ecx]; push eax; call [edx+0x28]; lea ecx,[esp+0x38]; push ecx
+0173/+01a0 retail mov edx,esp   ours mov eax,esp
+01c7..+01de (Null arm) same swap
```
The `_WriteBarrier`/`_ReadWriteBarrier` statements in the arms are
inherited from the bank. They are not clean C++ by the workflow rule.
Without them every arm tail-merges into arm 2 (609 B, 160 diffs).

## Evidence that the residue is a rotation phase, not a construct

- The matched sibling `_bfme_send` (0x00514000, same TU family) shows the
  same pattern. The first arm in layout is EDX/EAX style; later arms are
  EAX/EDX style and tail-merge.
- Synthetic probes (`v/T*.cpp`, `v/U*.cpp`) show the style flips with the
  code before the arm:
  - one fetch+format alone is EAX style;
  - in a two-arm if/else, the first arm is EAX style and the second EDX
    style;
  - a preceding `rva00512890(5,name)` call gives EDX style, but
    `rva00512890(msg,name)` gives EAX style.
- An EDX-style arm is a fixed point of the scratch rotation: EAX/ECX/EDX
  are handed out in turn, and the vtable load skips ECX because the
  receiver holds it. So once arm 2 is EDX style, ours keeps every later
  arm EDX style (`v/D1.cpp`: four unmerged arms, all EDX style). In retail,
  something between arm 2's format `this` and arm 1's slot advanced the
  rotation one step. That was not found.

## Ruled out this session (diffs; barrier base 13 unless noted)
- Rotation lever: `tools/rotation_sweep.py` single and `--pairs` on the
  barrier bank (19 throughout) and on the barrier-free body. The only mover
  was an identity copy of the Null fetch, which adds copy-ctor calls (59).
- Receiver copy `rcopy(TheGameText)->fetch` in all 15 arm subsets: 13 with
  barriers, 160 without.
- Explicit `, 0` versus the default argument, in all 15 arm subsets: 19.
- Pure-virtual fetch, with or without the other slots also pure: 13, or
  160 without barriers.
- The Send TU's whole class model (`v/sendmodel.cpp`): 19.
- `UnicodeString(fetch())`/cast wrappers: grow the body (459+).
- `switch(status)` (dec chain, 261/161); nested else-chains (160); random
  sweep of cond order, unsigned status, decl order, local `str`
  (`v/g_*`, 40 variants: 160/183).
- `str()` spellings: static `TheNullChr`, validate/peek layers, if-return
  (13 or 160); pointer-local form (254).
- Adding `operator=`, a wide ctor or `TheEmptyString`: 13.
- `/D_STLP_USE_STATIC_LIB` plus `<vector>`: 13.
- Barrier-subset map `v/bar????.cpp` (diagnostic only): only 0111 gives 19
  on the old class.
- Donors: BFME 2 has no buddy-tooltip handler (no BuddyIs* strings).
  Zero Hour LobbyUtils/WOLBuddyOverlay share callees only.

## Next ideas (untested)
- Look for a folded temp at the end of arm 2 or the start of arm 1 that a
  plausible original would contain, such as a status enum or a debug macro
  that leaves a dead temp.
- Find the construct that makes `_bfme_send` split its arms naturally:
  minimise its switch until the split disappears.
