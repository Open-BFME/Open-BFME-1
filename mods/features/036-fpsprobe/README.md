# 036-fpsprobe — did the screen change, or only the loop?

`UNSHIPPED` — an instrument, and it writes tens of lines a second.

## The hook

`DX8Wrapper::End_Scene`'s `mov eax,[TheD3DDevice]` at `0x00909039` — five bytes,
one whole instruction, no relative operand, and **past the `flip` test**
(`0x00909011`…`0x00909045`), so it fires once per frame that really reaches the
screen and never on a render-to-texture pass. `EndScene` has already run, which
is what makes a backbuffer readback legal there. `TheD3DDevice` is `0x01340534`.

## What it emits

Per sampled present: QPC, the engine ms clock, its own present counter, the
network frame, the client frame (via `getFrame` through the vtable slot
`GameEngine::execute` itself uses), the sub-step phase (`GameLogic+0x168`), the
desync flag, `work`/`idle`/`limited`, the animation clock, the logic CRC, and
192 FNV-1a cell hashes over a full-coverage 16×12 partition. Eight consecutive
presents every 2000 ms, so consecutive-frame comparisons are meaningful.

Build it as **`036-fpsprobe-timing`** to compile the readback out. That readback
is a whole-frame GPU→CPU copy — 0.34 MP at the rig's 660×520, 1.44 MP at a real
desktop — so at high resolution the instrument becomes a significant part of what
it measures. The clocks and timing survive; only the cell hashes go.

## It stops rather than degrades

A multisampled backbuffer, an unknown format, a geometry change mid-capture, or
a failed lock ends the capture with a reason in the file. Half a capture under
two coordinate systems, silently, is worse than none.

## What its numbers cannot tell you

The cell hashes measure how OFTEN pixels change, never how a motion LOOKS. A
sawtooth changes every frame and scores perfectly — this probe rated a build a
player was watching visibly stutter as *healthier* than retail. `docs/fps60.md`
has that post-mortem; read it before drawing a conclusion from a duplicate rate.

Two readings it got wrong and how they were caught: `0x01340594` was taken for a
frame counter and took five distinct values across 336 presents; the tile grid
covered 16% of the screen before it was made a full partition. Both were found
by checking the instrument against something it did not produce.
