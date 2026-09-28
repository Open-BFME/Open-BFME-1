# 038-fpsrender: 60 FPS rendering in network matches only

Opt-in experiment, not in the bundle and not proposed for it. One detour, no
pokes.

## What it changes

In a network match the render limit is 60 FPS instead of retail's 38. Units
still step at 30 Hz, and skirmish and the menus stay at 38.

## How it works

A detour at `GameEngine::update` (`0x0006E910`) writes `FramesPerSecondLimit` at
`GameEngine+0x08`: `RENDER_LIMIT` (60) when `TheNetwork` is non-null, retail's
38 otherwise. It touches no sub-steps. In a match the network paces the
simulation, so any render limit works.

Skirmish and the menus keep 38 deliberately. With no network nothing paces the
cycle, the game's speed is the frame rate divided by six, and raising the limit
alone runs a skirmish fast.

## Build

`--dist` refuses it. To measure it with the frame probe and result records:

```bash
python3 tools/modbuild.py --only 020-gameresult --only 036-fpsprobe \
                          --only 038-fpsrender -o build/mods/arm.exe
```

## Limits

* It delivers about a quarter of a whole-game 60 FPS: multiplayer only,
  client-side only, and units still step at 30 Hz.
* Doubling the simulation sub-steps to smooth unit motion is a closed route: it
  breaks everything authored in frames, and the Heal spell ran visibly fast in
  play.
* Measured against retail on a real desktop, it costs nothing (animation 0.942
  vs 0.926, network 4.755/s vs 4.684/s) and improves the typical frame (p90
  24.9 ms vs 28.4 ms). On the machine measured, a ~101 ms stall present in
  stock BFME under Wine, on 4–5% of frames, dominates either way.
