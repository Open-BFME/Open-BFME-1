# The MSVC 7.1 loop-head aligner (measured, 0x006BC750)

## Symptom

Clean C++ that matches retail instruction for instruction lands N+7 bytes wide.
The extra bytes are a `lea esp,[esp]` (or a shorter nop) wedged between the
loop's entry test and its first instruction, with every branch displacement
behind it shifted by the pad's length. `probe.py` reports a 0.96-0.97 shape
score and names the first divergence `length-delta`.

For `0x006BC750` the pad sat at `+0x29` and the body measured 79 against 72.

## The rule

It is arithmetic on the loop head's address mod 16, nothing else:

| natural head mod 16 | pad | emitted as |
| --- | --- | --- |
| 0 | 0 bytes | -- |
| 1..8 | **0 bytes** | the pass declines: reaching the next 16-boundary would cost 15..8 bytes |
| 9 | 7 bytes | `lea esp,[esp]` |
| 10 | 6 bytes | `lea ebx,[ebx]` |
| 13 | 3 bytes | `lea ecx,[ecx]` |
| 15 | 1 byte | `nop` |

Measured by sweeping the head over offsets 0..31 with an inline-asm `nop`
filler ahead of the loop. The harness that produced the table prints each
symbol's head, natural head, mod16 and pad kind straight out of the `.obj`;
it is untracked scratch at `build/wk/pad.py` (with `build/wk/try.py` for a
single-symbol disassembly), so re-create it from this table if it is gone.

## What does NOT move it

All of these were measured on this body and all left the pad in place:

- **Compiler flags.** 30+ combinations (`/Os` `/O1` `/O2` `/Ot` `/Ob1` `/Ob2`
  `/Oi` `/Oy` `/GF-` `/Gz` `/Gs999999` `/Zp1` `/Zp4` `/Zp8` `/Zp16` `/EHsc`
  `/G5` `/G6` `/G7` `/Gy-` `/GL-` `/J-` `/Gw`). `/Os` and `/O1` drop the pad but
  rewrite the entry test into `cmp dword ptr [ecx+N],0` plus a reload, so the
  head no longer matches retail.
- **Placement.** A preceding function of 0..19 varying byte lengths, with and
  without `/Gy-`. The alignment base is the function's own start, not a running
  section counter, so the "put another function ahead of it" idea in
  `docs/shape_levers.md` is dead for a body whose head already lands in the
  pad zone.
- **Loop spelling.** `while`, `for (;*p;p++)`, `do{}while(*p)` under an
  `if (*p != 0)` guard, a hoisted cursor with an infinite `for(;;)` plus
  `break`, and a `goto` loop with an identical block layout.
- **Body size and calls.** A standalone micro-benchmark pads a pointer-walk loop
  head with an indirect call, with a direct call, and with no call at all. The
  pass is not conditional on the body's contents.

A prior session concluded from the third and fourth bullets that the pad was
"unconditional for this loop class" and recorded
`blocker=toolchain/loop-head-alignment`. That conclusion was correct about the
*aligner* and wrong about the *loop*: the head address is fixed by the prefix
that retail also has, so the only remaining degree of freedom is the body.

## The lever

Give the optimizer a reason to reshape the loop **after** the aligner has run.
A redundant null test on the element pointer does it, because the fold that
deletes it happens too late to re-trigger alignment:

```c
while (*p != 0)                              /* 79 bytes: pad at +0x29 */
{
        BfmeUBM *u = (*p)->bfmeGetBM();
        if (u != 0)
                u->bfmeStopBM();
        p++;
}

while (*p != 0)                              /* 72 bytes: no pad */
{
        BfmeItemBP *item = *p;

        if (item != 0)
        {
                BfmeUBM *u = item->bfmeGetBM();
                if (u != 0)
                        u->bfmeStopBM();
        }

        p++;
}
```

The `if (item != 0)` is provably dead -- the loop condition just tested `*p` --
and the emitted code is byte-identical to the second listing above. The
alignment pass sees a loop whose shape it has already committed to; the later
fold does not re-open the question.

Bisected variants that also work: re-testing `*p` directly instead of through a
local, and nesting two such tests. Variants that do **not**: two statements in
the body without a redundant test, a second virtual call, a direct call, a
`continue`, an early `return` before the loop, a hoisted first-element local, and
a sentinel end pointer. The redundant test is the lever, not loop size or shape.

## Cost

`0x006BC750` had ten prior verdicts (3 `partial`, 7 `blocked`) across four
models before this. Verdict history is in `targets/game/reverse/re_attempts.log`;
the generalisable write-up is the "loop-head aligner" section of
`docs/shape_levers.md`.
