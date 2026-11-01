# 0x005B5E50 width slot: frame-group experiments (2026-11-01, s517)

Bank: `targets/game/reverse/attempts/0x005b5e50.cpp` (2473/2473 B, 3 diffs: retail
keeps `width` in the dead `msg` argument home ESP+0x40, ours at ESP+0x14).
Earlier evidence: `identity_evidence/005b5e50-width-slot.md`. Compiler: the bank's
own `// cl:` flags, VC7.1, `/FAsc` listings read with a private script (output
names in `build/a1s517/`, untracked).

## Retail frame groups (from the disassembly)

- arg home (+8): `width` and the bookmark `text` (UnicodeString, the only EH object)
- -40: the three int->float `fild` temps, every case-3 float (`angle`, `span`) and the
  two `$T` esp-save temps of the bookmark case's by-value arguments
- -44 disposition, -36 pos/mousePos (8 B), -28 region (16 B)

## Observations (FAsc `_name$ = N` tables; facts, not a model)

1. Source order of the `case` blocks does not change code layout: moving case 3 after
   the bookmark case, to the end, or any of 80 random permutations of the ten case
   groups leaves every instruction identical except frame offsets.
2. Every variant lands in one of exactly two frame patterns:
   - case 3 before the bookmark case (bank): `text` alone in the arg home; `width`,
     floats, tv temps and `$T` together at -40. 3 diffs.
   - bookmark before case 3: `text`, `width`, floats and tv temps all in the arg home,
     `$T` alone; frame 0x1C (56 diffs, all displacements).
   Neither is retail's {text, width} / {floats, tv, $T} split.
3. Replacing `text` by a POD without a destructor (diagnostic) puts it in the same
   group as `width` and the floats in case-3-first order. So the EH-tracked object
   does not join a group that already exists when it comes later in source order,
   but later variables do join a group it founded.
4. Which group gets the arg home follows its heaviest member: one shared
   `float angle` declared at case scope (6 references) moves the width/float
   group to +8 and pushes `text` to -40.
5. A diagnostic volatile int live across `width` (assigned before `getHeight`,
   read before the rotate block) pulls the then-branch angle, the tv temps and
   `$T` into the 8-byte pos group and leaves `width` with `span` only. That is
   the only shape that separated `width` from the floats.

## Inert (no change to the two patterns)

Width declared at case top, inside the `!slot1c8()` block or at its definition; height
the same; `pos` declared at case scope (adds 8 B of frame); angle per block,
shared at case scope or block scope; the rotate, pitch, slow-mode `else` branch and
the height/width/bounds part moved into `__forceinline` member helpers (helper locals
get late symbol numbers) in every combination with five case-3 positions; width via
an inline out-reference setter, through a `*const` pointer (7 diffs), as a wrapper with
an empty destructor, or `volatile` (7 diffs, still at -40).

## Reading

Under any first-fit grouping consistent with observations 2 and 3, retail's split
needs a variable in the float group whose lifetime overlaps `width` (as in
observation 5), or an EH-object lifetime rule that this source does not trigger. No
code-neutral source that does either was found. Next: look for a retail-real
4-byte spilled value live across width's range (from the getHeight call at +0x2D4
to the last bounds compare at +0x3AE), or a second destructible object.
