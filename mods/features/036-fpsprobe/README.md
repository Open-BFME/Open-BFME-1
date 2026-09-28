# 036-fpsprobe: frame timing and pixel changes at Present

Developer instrument, opt-in and not in the bundle: it writes tens of lines a
second, and `--dist` refuses it.

## What it records

The hook is `DX8Wrapper::End_Scene`'s `mov eax,[TheD3DDevice]` at `0x00909039`:
five bytes, one whole instruction, and past the `flip` test
(`0x00909011`…`0x00909045`). It therefore fires once per frame that really
reaches the screen and never on a render-to-texture pass. `EndScene` has already
run there, which makes a backbuffer readback legal. `TheD3DDevice` is
`0x01340534`.

Every 2000 ms it logs eight consecutive presents, so consecutive-frame
comparisons are meaningful. Each sampled present records QPC, the engine ms
clock, the probe's own present counter, the network and client frames, the
sub-step phase (`GameLogic+0x168`), the desync flag, `work`/`idle`/`limited`,
the animation clock, the logic CRC, and 192 FNV-1a cell hashes over a
full-coverage 16×12 partition.

It stops rather than degrades. A multisampled backbuffer, an unknown format, a
geometry change mid-capture or a failed lock ends the capture with the reason in
the file.

## Build variants

`modbuild.py` builds it by name as `036-fpsprobe`, or as `036-fpsprobe-timing`
with the backbuffer readback compiled out. The readback is a whole-frame GPU→CPU
copy (0.34 MP at 660×520, 1.44 MP at a real desktop), so at high resolution the
instrument becomes a significant part of what it measures. The timing variant
keeps the clocks and timing and drops only the cell hashes.

## Limits

The cell hashes measure how often pixels change, never how a motion looks. A
sawtooth changes every frame and scores perfectly: this probe rated a build as
healthier than retail while a player watching that build saw a floating "+15"
rise and snap back. The clock-based readings, the animation clock and
`work + idle`, held up where the pixel metrics did not.
