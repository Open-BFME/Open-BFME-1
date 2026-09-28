# BFME mods in this repository

`python3 tools/modbuild.py --dist` builds this repository's **seven-feature
bundle** at `mods/dist/`. That is a repository artifact, not a statement about
what Arena deploys. The current report from an Arena user is that Arena ships
the network-delay fix only; Arena's deployment configuration is not tracked
here. See [docs/mods.md](../docs/mods.md) for how the patches are built.

| Status | Features | Purpose |
| --- | --- | --- |
| In the repository bundle | `020-gameresult` | Match-result and desync records. |
| In the repository bundle | `031-earlysend`, `033-retrytime` | Two network-delay changes. |
| In the repository bundle | `039-replayctl`, `043-replaycam` | Replay-only controls. |
| In the repository bundle | `042-tracksfix` | Fix for a reproduced terrain-track crash. |
| In the repository bundle | `048-advancedgfx` | Graphics options UI; requires its bundled `apt/options.big`. |
| Opt-in AC gameplay fix | [`055-ac-attack-view`](features/055-ac-attack-view/README.md) | The only AC feature players need. The reported scenario passed an offline replay and a live two-client test; broader horde-combat effects remain to be tested before bundling. |
| Opt-in experiment | `038-fpsrender`, `040-horplus` | Render-only 60 FPS attempt and camera change; neither is in the bundle. |
| Developer diagnostics only | `030-netlatprobe`, `036-fpsprobe`, `041-tracksprobe`, `045-drawprobe`, `047-uiprobe`, [`056-ac-transition-trace`](features/056-ac-transition-trace/README.md) | Optional measurement tools, not player fixes; `041` includes a deliberate crash trigger. |

There are **16 feature directories**: seven in the repository bundle, the opt-in
AC fix, two opt-in experiments, and six developer diagnostics. The full 60 FPS
attempt raised the game speed and is retired; it is in git history.