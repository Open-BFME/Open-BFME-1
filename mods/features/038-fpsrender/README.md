# 038-fpsrender — the render rate, and nothing else

`UNSHIPPED`, and not proposed for shipping. One detour, no pokes.

`GameEngine::update` (`0x0006E910`) — the payload writes
`FramesPerSecondLimit` at `GameEngine+0x08`: **60** when `TheNetwork` is
non-null, retail's **38** otherwise. That is the whole feature.

Sixty rather than 76 because 76 was only ever 2×38, which matters to `037`
(it doubles sub-steps, so 76/12 must equal 38/6 — a test enforces that). This
touches no sub-steps, the network paces the simulation in a match, so any limit
works; 60 is what was asked for and costs 21% less. It has its own constant,
`RENDER_LIMIT`.

Skirmish and the menus keep 38 deliberately: with no network nothing paces the
cycle, so the game's speed IS the frame rate over six and raising the limit
alone runs a skirmish fast. `037` shares this detour address on purpose, so
`modbuild` refuses to stack the two.

**Why it is not proposed.** It delivers about a quarter of the ask — multiplayer
only, client-side only. Units still step at 30 Hz, and the route that would fix
that is closed (see `docs/fps60.md`). Measured against retail on a real desktop
it costs nothing (animation 0.942 vs 0.926, network 4.755/s vs 4.684/s) and
improves the typical frame (p90 24.9 ms vs 28.4 ms) — but on that machine a
~101 ms stall present in stock BFME dominates either way.

Everything else — what was tried, what closed, and where the instruments lied —
is in `docs/fps60.md`. Read that before building on this.
