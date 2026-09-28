# BFME mods in this repository

`python3 tools/modbuild.py --dist` builds this repository's **seven-feature
bundle** at `mods/dist/`. That is a repository artifact, not a statement about
what Arena deploys. The current report from an Arena user is that Arena ships
the network-delay fix only; Arena's deployment configuration is not tracked
here. See [docs/mods.md](../docs/mods.md) for how the patches are built.

| Status | Features | Purpose |
| --- | --- | --- |
| In the repository bundle | [`020-gameresult`](features/020-gameresult/README.md) | Match-result and desync records. |
| In the repository bundle | [`031-earlysend`](features/031-earlysend/README.md), [`033-retrytime`](features/033-retrytime/README.md) | Two network-delay changes: worst freeze 3.7 s → 0.8 s at 150 ms round trip and 3% loss per direction. |
| In the repository bundle | [`039-replayctl`](features/039-replayctl/README.md), [`043-replaycam`](features/043-replaycam/README.md) | Replay-only controls. |
| In the repository bundle | [`042-tracksfix`](features/042-tracksfix/README.md) | Fix for a reproduced terrain-track crash. |
| In the repository bundle | [`048-advancedgfx`](features/048-advancedgfx/README.md) | Graphics options UI; requires its bundled `apt/options.big`. |
| Opt-in AC gameplay fix | [`055-ac-attack-view`](features/055-ac-attack-view/README.md) | The only AC feature players need. A reported scenario passed an offline replay and a live two-client test; broader horde-combat effects remain to be tested before bundling. |
| Opt-in experiment | [`038-fpsrender`](features/038-fpsrender/README.md), `040-horplus` | Render-only 60 FPS attempt and camera change; neither is in the bundle. |
| Developer diagnostics only | `030-netlatprobe`, [`036-fpsprobe`](features/036-fpsprobe/README.md), [`041-tracksprobe`](features/041-tracksprobe/README.md), `045-drawprobe`, `047-uiprobe`, [`056-ac-transition-trace`](features/056-ac-transition-trace/README.md) | Optional measurement tools, not player fixes; `041` includes a deliberate crash trigger. |

There are **16 feature directories**: seven in the repository bundle and nine
opt-in or diagnostic. `036-fpsprobe` has two opt-in build variants,
`036-fpsprobe` and `036-fpsprobe-timing`.

Raising the frame rate is not a free 60 FPS, because game logic is tied to it.
Without a network pacing the match, game speed is the frame rate divided by six,
and doubling the logic sub-steps (the retired `037-fps60`, in git history) ran
animations at double speed.
