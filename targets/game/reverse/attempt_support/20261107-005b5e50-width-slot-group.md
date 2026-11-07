> Scratch paths under `build/wf/005b5e50/` below are untracked session files and are not kept.

# 0x005B5E50 width slot: follow-up (2026-11-06, wf session)

Target `?translate@Rva005B5E50@@UAEHPBVRva005B5E50Message@@@Z`, 2473 B.
Bank `targets/game/reverse/attempts/0x005b5e50.cpp` (copied to
`build/wf/005b5e50/base.cpp`, unchanged) still reproduces 2473/2473 B with 3
non-reloc diffs: `mov [esp+0x40],eax` / `mov edx,[esp+0x40]` /
`mov eax,[esp+0x40]` at +0x2EC/+0x37C/+0x3A7; ours use `[esp+0x14]`.
Compiler: the bank's `// cl: /DNDEBUG /MD /EHsc ...` line (VC7.1), `/FAsc`
added for diagnosis only. Read with the earlier handoff
`attempt_support/005b5e50-20261101-frame-group-model.md`.

Retail groups (from disassembly): arg home {msg, text, width}; -40 {all
floats, the three int->float tv temps, both `$T` saved-esp temps}; -44
{disposition}; -36 {pos, mousePos}; -28 {region}. Ours (c3-first): arg home
{msg, text}; -40 {width + everything retail has at -40}.

## New measurements (scripts and .cod listings: build/wf/005b5e50/x, v)

Code-neutral (all keep 2473 B):
- 15 flag sets on the bank (`/G5 /G6 /GX /GR /Gy /Ox /O2 /Ob1`, `/QIfist`):
  identical 3 diffs and groups. `/G7 /Ob0 /Os /Op /Oa /Ow /Oy-` change code.
  No packing lever in flags.
- width/height as an 8-byte aggregate (`unsigned dim[2]`, `struct{h,w}`,
  `struct{w,h}`, `ICoord2D`): code identical (3 diffs) but the width spill
  moves INTO the aggregate's slot in the -36 pos group (`[esp+0x18]`), and -40
  becomes exactly retail's {floats, tvs, $T}; arg home stays {text}. In
  bm-first order the floats join text again. Only shape found that empties
  width out of the float group without code change.
- 4-byte aggregates for width (`unsigned width[1]`, `struct{unsigned v;}`)
  at case top / function scope, address-alias `*pw`: inert (scalarised).
- `const unsigned &width = slot02c()` (and height too): 7 diffs, temp `$S1`
  lands where width did.
- Bookmark case: extra `{}` around text (inert, 3 diffs); early `break`
  form (19), `disposition=1` first (114), no case braces (231).
- `__forceinline` member helper taking `(height,width)` or
  `(selecting,height,width)` by value for the bounds block: inert, both orders.
- if/else inversion of the `slot1c8()` branch: layout changes (860 diffs).
- Local `Pixel p = arg->pixel(); member = p;` at the four anchor stores:
  10-93 diffs, groups unchanged.

Diagnostic (code-changing, to learn the packer; not candidates):
- Removing both `$T` (const-ref `slot034`, literal format): text still alone
  in c3-first. `$T` is not what keeps width out of text's group.
- One extra width reference: width's whole group takes the arg home and text
  shares -40 with disposition (text and disposition do not conflict).
- Case 3 reduced to one float with an int->float tv: the float+tv never join
  a text-only group in either case order (they go with `$T`). A float with no
  tv (`region.y_max-region.y_min`) joins text only when the bookmark case is
  first in source. So case order matters, and tv-carrying floats behave
  differently from plain floats.
- Volatile int live across width (repro of the earlier observation 5):
  c3-first gives -40 {span, width}, -36 {v, pos, mousePos, all angles, tvs,
  $T}; span stays with width because it conflicts with mousePos.

## Reading

Every model consistent with these data (first-fit in source/IL order,
EH object founds but never joins a group, function-scope disposition placed
last, arg home to the group holding the heaviest member) needs retail's float
group to contain a member whose live range overlaps width, or width to be
processed after text while no earlier 4-byte group is free. No natural,
code-neutral source found here provides either. The 8-byte aggregate shape
shows the -40 group can be made retail-exact; what is still missing is a
4-byte home for width that is processed after text (or that conflicts with
the floats) without changing code.

## Next ideas not yet tried

- Combine the aggregate-dims shape with a second, natural 4-byte value that
  forwards width into the arg home (e.g. a by-value parameter of a non-inline
  but visible callee) and check whether the call disappears.
- Look for a BFME 2 donor of the camera translator for the real case
  layout. The `inputs/reference/open-bfme-2` submodule is not initialised in
  this checkout, so it was not consulted; Zero Hour `LookAtXlat.cpp`
  (GeneralsMD) was, and declares `height`/`width` after the anchor update.

Best candidate: `build/wf/005b5e50/base.cpp` (= bank), 3 diffs.
