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
| Opt-in, incomplete | [`055-ac-attack-view`](features/055-ac-attack-view/README.md) | Improves target discovery, but rear Uruks still cancel after a re-click. **Do not treat as an AC fix.** |
| Opt-in experiment | `038-fpsrender`, `040-horplus` | Render-only 60 FPS attempt and camera change; neither is in the bundle. |
| Broken or unfinished | `034-framedrain`, `037-fps60`, `044-modpanel` | Desyncs, changes spell timing, or does not draw, respectively. Do not ship. |
| Diagnostic only | `030-netlatprobe`, `036-fpsprobe`, `041-tracksprobe`, `045-drawprobe`, `047-uiprobe` | Measurement tools; `041` includes a deliberate crash trigger. |
| Not registered with the mod builder | `035-adaptretry`, `049-unitinterp`, `050-ratiocont` | Abandoned or incomplete source, not selectable by `modbuild.py`. |

There are **21 feature directories**: seven in the repository bundle, eleven
opt-in or diagnostic directories, and three not registered with the builder.
`036-fpsprobe` has two opt-in build variants, so `modbuild.py` lists twelve
opt-in names. None of the FPS experiments is in the repository bundle; the
full 60 FPS attempt is [documented as broken](../docs/fps60.md).
