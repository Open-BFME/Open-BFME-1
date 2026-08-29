# BFME widescreen UI research

Status: research only. This document records the current evidence and a
future implementation plan. It does not create `mods/features/041-widescreenui/`
and does not change production UI code.

## Executive conclusion

BFME does not have one UI coordinate system that can safely be widened at the
renderer exit. It has several systems which eventually submit mostly
pixel-coordinate primitives, but they do not share the same ownership or
layout contract:

```text
  .wnd text                 ControlBarScheme.ini        ShellMenuScheme.ini
        |                            |                         |
        v                            v                         v
  GameWindow tree          ControlBar windows + skin       direct draw calls
        |                            |                         |
        +------------- physical pixel rectangles -----------+
                                      |
                                      v
                 Render2DClass / DisplayString / W3D callbacks
                                      |
                                      v
                                  framebuffer

  APT screens -------------- separate runtime and screen objects
  Living World ------------- APT overlay plus 3D/data subsystems
  world-space text ---------- worldToScreen, then pixel draw
  mouse/input --------------- physical pixels and inverse ownership mapping
```

The verified `.wnd` path applies independent X and Y ratios at parse time.
ControlBar has a second, explicit independent multiplier driven by
`ScreenCreationRes`, and its skin is drawn by W3D callbacks around a marker
window. Shell menu schemes directly draw stored integer coordinates. APT
screens are constructed by BFME-specific factories, but the APT runtime and
the retail APT files are not present in this worktree. Therefore the safe
future design is owner-scoped transforms with matching input transforms, not a
global 4:3 viewport or a temporary global `Display::getWidth()` substitution.

The existing 040 tactical Hor+ work is useful and orthogonal: it changes the
tactical 3D camera. The historical 041 UI experiment and current 042 renderer
experiment are evidence about failed approaches, not a foundation to revive.

## Evidence and confidence notation

* **High** — directly shown by current source and/or an existing reconstructed
  BFME body or string/xref record.
* **Medium** — source/reference behavior is clear, but the retail data file or
  one BFME-specific body is absent or only partially reconstructed.
* **Low** — an implementation hypothesis that still needs a retail asset,
  runtime trace, or visual test.

No new RVA is asserted here. Addresses mentioned in source comments or
existing tests are not used as new implementation claims.

## Documentation and repository coverage

I read the repository guidance and every file under `docs/` recursively before
the inventory pass:

* `README.md`
* `AGENTS.md`
* `mods/README.md`
* `docs/README.md`
* `docs/boot_order.md`
* `docs/filesystem_family.md`
* `docs/game-quitting.md`
* `docs/ini_schema.md`
* `docs/lan-testing.md`
* `docs/lessons-archive.md`
* `docs/lessons.md`
* `docs/local_fleet.md`
* `docs/matching.md`
* `docs/mods.md`
* `docs/net-latency-fix.md`
* `docs/net-latency.md`
* `docs/structural.md`

The documentation was used as navigation and historical evidence. Current
source, the baseline binary's strings/xrefs, and existing reconstructed
bodies take precedence over speculative historical notes.

### Repository state at investigation time

* Branch: `widescreen-ultrawide-test`.
* `python3 tools/check_csv.py`: passed (`functions.csv` 161761 rows,
  `symbols.csv` 77847 rows).
* Existing history contains 040 tactical Hor+, the removed historical 041 UI
  attempt, and the current 042 renderer experiment.
* The worktree already contains one unrelated unstaged edit:
  `mods/features/042-ultrawide-render/src/ultrawide_render.cpp`, removal of a
  blank line. It was preserved byte-for-byte.
* `git pull --rebase origin master` was attempted before research and was
  refused because that edit is unstaged. It was not stashed, committed, or
  reverted.
* No test executable was built and no production source, modbuild logic, or
  shipped feature was changed by this investigation.

## UI family inventory

| Family | Data/assets seen in evidence | Runtime owner | Coordinate contract | Final draw/input path | Confidence |
|---|---|---|---|---|---|
| GameWindow layouts | `.wnd`; `ControlBar.wnd`, `ReplayControl.wnd`, menu, popup, load-screen, and message-box names | `GameWindowManager`, `GameWindow`, `WindowLayout` | `SCREENRECT ... CREATIONRES`; independent X/Y parse scaling; children become parent-relative | `winRepaint` -> `drawWindow` -> callback/images/text; raw physical mouse hit tests | High |
| Control Bar | `Data\\INI\\ControlBarScheme.ini`, `Default\\ControlBarScheme.ini`, mapped images; `ControlBar.wnd` | `InGameUI`, `ControlBar`, `ControlBarSchemeManager`, W3D callbacks | scheme `ScreenCreationRes` multiplier plus separately parsed window geometry and marker offsets | W3D command-bar callbacks, direct `TheDisplay` draws, GameWindow hit regions | High |
| Shell GameWindow UI | `Menus/*.wnd`, shell background and message/load layouts | `Shell`, `ShellMenuSchemeManager`, `GameWindowManager` | stack of window layouts; scheme image/line coordinates are stored integers | window repaint and transitions | High/Medium |
| Shell APT UI | `MainMenu.apt`, `OnlineShell.apt`, `Options.apt`, `Skirmish.apt`, `LanLobby.apt`, etc. | APT screen factories and WindowManager APT APIs | runtime-owned APT coordinate system not present in source tree | APT manager/runtime; input callbacks registered by screen objects | Medium for existence, Low for scaling |
| Living World | `LivingWorldUI.apt`, `GuiFX.apt`, LivingWorld INI blocks and campaign data | APT screen plus `TheLivingWorldManager`, logic and campaign manager | UI portion is APT; map/army/animation records are not GameWindow layouts | indexed APT show/hide plus 3D/data subsystems | High for ownership, Low for APT scaling |
| World-space UI | floating text, world animations, build/radius cursors | `InGameUI`, `TacticalView`, `Anim2D`, display strings | world projection returns physical pixel position; animation size also follows zoom | submitted during `preDraw`, before ordinary UI | High |
| Loading/mission UI | `ShellGameLoadScreen.wnd`, `MultiplayerLoadScreen.wnd`, map-transfer and connection layouts; load-screen APT names | `LoadScreen`, `WindowVideoManager`, `InGameUI` | GameWindow creation resolution plus video/window dimensions | window tree or per-window movie buffer; load branch draws UI and mouse | High |
| Fullscreen movies/cinematics | `VideoPlayer`, global and cameo video buffers, cinematic text | `W3DDisplay`, `InGameUI`, `WindowVideoManager` | fullscreen movie is explicitly scaled to current display; window movie uses target window rect | after ordinary UI and mouse for global movie; window callback for window movie | High |
| Text/tooltips/mouse | font fields, `DisplayString`, `Mouse` INI fields | font/display-string manager, `W3DMouse`, WindowManager | mostly physical pixel positions; some percentages and a subtitle-specific 800x600 scale | Render2D sentence quads; cursor/tooltip drawn after UI; input remains physical | High |

## Asset and loader map

The repository does not contain the retail loose UI data. The baseline folder
contains the retail executables and manifest, but no loose BFME `.wnd`, `.apt`,
`.big`, mapped-image, texture, font, or CSF set. The following are therefore
real retail names recovered from source literals, executable strings, and
`reverse/string_xrefs.tsv`; the actual contents and exact field values must be
recovered from the user's retail archives before implementation.

| Asset class | Representative names/paths | Loader/owner | What is known |
|---|---|---|---|
| Window layouts | `ControlBar.wnd`, `ReplayControl.wnd`, `InGamePopupMessage.wnd`, `ControlBarPopupDescription.wnd`, `Menus/BlankWindow.wnd`, `Menus/MessageBox.wnd`, `Menus/QuitMessageBox.wnd`, `Menus/MapSelectMenu.wnd`, `Menus/LanLobbyMenu.wnd`, `Menus/ShellGameLoadScreen.wnd`, `Menus/MultiplayerLoadScreen.wnd`, `Menus/MapTransferScreen.wnd`, `Menus/GameSpyLoadScreen.wnd`, `Menus/EstablishConnectionsScreen.wnd` | `GameWindowManager::winCreateFromScript`; `WindowLayout::load` | Parsed into named GameWindow trees. Exact `SCREENRECT` and `CREATIONRES` values are absent from this checkout. |
| Frontend/menu APT | `MainMenu.apt`, `OnlineShell.apt`, `Options.apt`, `Skirmish.apt`, `LanLobby.apt`, `LoadScreen.apt`, `DisconnectScreen.apt`, `SaveLoad.apt`, `QuitMenu.apt`, `ScoreScreen.apt`, `CampaignReview.apt`, `SpellStore.apt`, `InGameChat.apt`, `PlayerStatus.apt`, `Objectives.apt` | BFME APT screen factory table and WindowManager | Factory source proves fixed-size screen objects and callback registration. The APT runtime and files are absent. |
| APT overlays | `BannerUI.apt`, `LivingWorldUI.apt`, `GuiFX.apt`, `Background.apt`, `AptLevel0.apt` | `BannerUI`, APT WindowManager, screen objects | `BannerUI` is loaded with `loadAptWindow`; Living World visibility calls indexed `showAptWindow`/`hideAptWindow`. |
| ControlBar skin | `Data\\INI\\ControlBarScheme.ini`, `Data\\INI\\Default\\ControlBarScheme.ini` | `ControlBarSchemeManager::init` and scheme selection | 68-field schema includes `ScreenCreationRes`, mapped images, layer positions/sizes, and named HUD marker rectangles. |
| Mapped images | `Data\\INI\\MappedImages\\TextureSize_512`, `...\\HandCreated`; user-data mapped-image directory | `GameClient::init` creates `TheMappedImageCollection`; `ImageCollection::load(512)` loads directories | A `MappedImage` stores texture name/dimensions and UV mapping; the texture itself is archive-backed. |
| Gameplay/UI INI | `Data\\INI\\InGameUI.ini`, `CommandButton.ini`, `CommandSet.ini`, `Mouse.ini`, `WindowTransitions.ini` | `InGameUI`, `ControlBar`, `Mouse`, transition manager | Font, message, subtitle, tooltip, command, and transition policies are code/data mixed. |
| Localized text/fonts | `Lang\\%s\\Lotr.csf`, language font fields and substitutions | global language data, game text, font library | Language data can replace several InGameUI fonts and adjust point sizes. |
| Movies | names passed to `TheVideoPlayer->open`, including `VSSmall` for a load-screen overlay | `WindowVideoManager`, `InGameUI`, `W3DDisplay` | Movie buffers are allocated at stream dimensions, then drawn into a window or the full display. |
| Living World data | `LivingWorldMapInfo`, `LivingWorldAnimObject`, `LivingWorldCampaign`, army/player records | INI parsers and Living World managers | These records describe map objects, animation objects, campaign and army state; they are not evidence for APT screen geometry. |

## End-to-end traces

### GameWindow `.wnd`

**Load:** `WindowLayout::load` calls `TheWindowManager->winCreateFromScript`.
The script parser reads a `WINDOW` block, builds a `GameWindow`, stores the
first window and all created windows in the script info, and can run layout
callbacks. `InGameUI::createControlBar` and `createReplayControl` use this
same path directly.

**Geometry:** `parseScreenRect` reads `UPPERLEFT`, `BOTTOMRIGHT`, and
`CREATIONRES`. It computes:

```text
sx = Display.width  / CREATIONRES.x
sy = Display.height / CREATIONRES.y
physical edge = (Int)(creation edge * corresponding scale)
```

For a child, the parser obtains the parent's absolute screen position and
stores the scaled absolute upper-left minus that parent position as the
child's local origin. Width and height are the differences of the scaled
edges. A root keeps the scaled screen origin. This matters: applying a second
center translation to every child would double-translate the tree.

**Absolute position and hit testing:** `GameWindow::winGetScreenPosition`
recursively sums each `m_region.lo`; `winGetSize`/`winSetSize` use the physical
window size. `winPointInChild` and `winPointInWindow` compare the raw mouse
pixel coordinates against those absolute rectangles. `winSendInputMsg`
delivers the packed physical `(x,y)` to the callback and bubbles key/mouse
messages through parents where appropriate.

**Draw:** `GameWindowManager::winRepaint` draws below, ordinary, and above
root windows. `drawWindow` draws the parent callback, children in reverse
order, and borders at the appropriate stage. Hidden parents suppress their
subtrees. A transition handler draws after the window roots.

### ControlBar and HUD

`InGameUI::init` creates a full-width tactical view, sets its height to about
`0.77 * Display.height`, creates `ControlBar.wnd`, creates replay controls,
then constructs and initializes `TheControlBar`.

`ControlBar::init` loads command button/set data, creates the scheme manager,
finds the named GameWindow regions (`RightHUD`, command windows, selection
windows, cameo, power/money, options, worker, beacon and other controls), and
stores foreground/background marker screen positions. The GameWindow regions
are therefore the hit-test and callback ownership, even where the artwork is
not drawn by the normal window image callback.

`ControlBarSchemeManager::init` loads the default and normal scheme INIs.
Scheme selection computes an independent multiplier:

```text
scheme_x = Display.width  / selected.ScreenCreationRes.x
scheme_y = Display.height / selected.ScreenCreationRes.y
```

`ControlBarScheme::init` also uses a local multiplier while repositioning
named windows and the known `UL/LR` rectangles. `drawBackground` and
`drawForeground` multiply each image part's position and size, then add the
callback's offset. The W3D command-bar callbacks compute that offset as the
current window's absolute position minus the stored marker position and call
the scheme draw methods.

Other W3D callbacks draw radar, video, borders, fills, grid lines, supply and
command images directly through `TheDisplay` using pixel coordinates. A global
renderer transform cannot distinguish these from unrelated GameWindow, movie,
tooltip, or debug primitives.

### Shell and frontend

`Shell` owns a screen stack, pending push/pop state, a background, animation
manager, and `ShellMenuSchemeManager`. `push(filename)` shuts down the current
screen and later loads the requested screen; `showShell` creates the initial
frontend screen when the stack is empty; `hideShell` shuts down and disables
the shell. The source fallback uses a `Menus/MainMenu.wnd` path, while the
BFME-specific reconstructed show-shell thunk contains an APT `MainMenu.apt`
branch and a LAN-lobby `.wnd` branch. This discrepancy is a real branch/data
distinction, not a reason to normalize the names.

`ShellMenuScheme` parses `ImagePart` (`Position`, `Size`, `ImageName`) and
`LinePart` (`StartPosition`, `EndPosition`, `Color`, `Width`). Its draw method
calls `TheDisplay->drawImage`/`drawLine` with the stored integer coordinates;
no creation-resolution scaling is visible in the source. This is a separate
future hook from GameWindow parsing.

### APT screens

`AptScreenFactories.cpp` provides BFME-specific factories for the APT screen
names. Each factory allocates a fixed-size screen object, passes the APT
context to its constructor, and returns the object. Screen constructors
register named callbacks such as initialization, quit, chat, player color, and
button handlers through the APT/WindowManager bridge. Other source uses
`showAptScreen`, `showAptScreenWithArg`, `setAptScreenRef`, `showAptWindow`,
`hideAptWindow`, and `bfme_setAptText`.

The APT runtime implementation and the retail `.apt` layout data are not in
the source tree. We can establish ownership and lifecycle, but not yet the
APT root transform, stage viewport, or whether a given screen uses its own
scale/letterbox policy. A future APT transform must be based on a runtime
trace or a verified retail body; changing GameWindow parser state is not a
substitute.

### Living World

Living World is a mixed subsystem. `INILivingWorld.cpp`,
`INILivingWorldAnimObject.cpp`, `INILivingWorldCampaign.cpp`, and related
parsers populate map, animation, campaign, army, and player records owned by
the Living World managers. `GameEngine::init` registers the APT player, Living
World manager, game client, Living World logic, and campaign manager in the
normal boot order.

The visible map UI is an APT window. The verified visibility helpers only guard
the indexed screen state:

```text
showAptLivingWorldUI -> showAptWindow(index), visible = true
hideAptLivingWorldUI -> hideAptWindow(index), visible = false,
                         closing = false
```

APT strings and callbacks include region name/bonus/conquered labels and
Palantir-style region button callbacks. Thus Living World should be treated as
an APT screen with separate 3D/data support, not as a ControlBar or `.wnd`
root.

### World-space overlays and ordinary InGameUI

`InGameUI::preDraw` handles build placement icons, radius cursors, floating
text, and world animations. Floating text calls tactical `worldToScreen`,
centers the string on the returned physical pixel position, and draws it with
`DisplayString`. World animations also project to screen and scale their frame
size using tactical zoom before drawing an `Anim2D` image.

The retail `postDraw` body is still represented by a byte-true thunk in this
checkout, with a disabled reference-shaped C++ body nearby. The visible source
therefore cannot by itself prove every post-draw branch identity. The branches
that are directly readable elsewhere include messages, special/named timers,
subtitles, RMB scroll anchor, direct command-bar shortcut text, and popup
layouts. They must be audited as separate pixel/percentage owners in the
future work.

## Framebuffer and low-level 2D path

The W3D frame order is verified in `W3DDisplay::draw`:

```text
Begin_Render
  if load-screen render:
      InGameUI draw, Mouse draw, End_Render
  else:
      drawViews()                         # 3D views and their 2D scene
      TheInGameUI->DRAW()                 # ordinary UI
      TheMouse->DRAW()                    # cursor and tooltip
      global InGameUI video buffer         # full-display movie, if active
      copyright DisplayString
      letterbox
      cinematic DisplayString
      debug/perf overlays
End_Render
```

The code uses both lowercase virtual calls and the BFME `DRAW` macro/slot
path, so the exact retail body of a particular UI phase must not be inferred
from the stubbed base `Display::draw` alone. The ordering above is the
device-specific body that matters for presentation.

`W3DDisplay::setWidth` and `setHeight` update `Render2DClass`'s coordinate
range to `(0,0)-(Display.width,Display.height)`. The renderer maps pixel-like
coordinates approximately as:

```text
clip_x =  2*x / Display.width  - 1
clip_y =  1 - 2*y / Display.height
```

with the existing half-pixel/UV bias rules. `drawImage`, `drawVideoBuffer`,
`drawFillRect`, `drawOpenRect`, and `drawLine` all consume display-pixel
coordinates. Images carry UV rectangles and raw texture/filename state;
`ImageCollection::load(512)` loads mapped-image definitions, not an alternate
logical viewport.

Text follows the same final pixel convention. `W3DDisplayString::draw` puts
the sentence at the requested integer `(x,y)`. `Render2DSentenceClass` creates
a renderer using the current screen resolution, adds sentence quads, and
renders them through the same Render2D mapping. This makes the low-level path
uniform at the last stage, but it does not make all callers uniform.

### The separate `W3DView::m_2DCamera`

`W3DView::init` creates `m_2DCamera`, positions it at Z 1, and sets its view
plane to `(-1,-0.75)` through `(+1,+0.75)` with clip planes near `0.995` and
`2.0`. `W3DView::draw` renders its 2D scene through that camera. This is a
fixed 4:3 W3D scene-space contract and is not the same object as
`W3DDisplay::m_2DRender`, which maps integer display pixels. It must not be
changed as a side effect of a GameWindow or ControlBar transform.

## Numeric scaling examples

The following table is an exact parser example for a `.wnd` block with
`CREATIONRES 800 600` and source rectangle
`UPPERLEFT 100 100 BOTTOMRIGHT 300 200`. Each edge is cast to `Int` after its
own multiplication. These are parser outputs, not a claim that every retail
layout uses `800x600`.

| Display | sx | sy | Parsed rectangle |
|---|---:|---:|---|
| 800x600 | 1.000 | 1.000 | `(100,100) -> (300,200)` |
| 1024x768 | 1.280 | 1.280 | `(128,128) -> (384,256)` |
| 1280x800 | 1.600 | 1.333 | `(160,133) -> (480,266)` |
| 1920x1080 | 2.400 | 1.800 | `(240,180) -> (720,360)` |
| 2560x1080 | 3.200 | 1.800 | `(320,180) -> (960,360)` |
| 3440x1440 | 4.300 | 2.400 | `(430,240) -> (1290,480)` |
| 3840x1600 | 4.800 | 2.667 | `(480,266) -> (1440,533)` |
| 5120x1440 | 6.400 | 2.400 | `(640,240) -> (1920,480)` |

This demonstrates why a renderer-only horizontal crop is not equivalent to
the retail parser: at 1280x800 and wider, a 4:3-created rectangle is already
non-uniformly scaled to the physical display before it reaches Render2D.

For comparison, the following is the centered height-led 4:3 band arithmetic
used by the old renderer experiment's tests. It is a candidate policy, not
verified vanilla behavior:

```text
band = min(Display.width, Display.height * 4 / 3)
left = (Display.width - band) / 2
```

| Display | Candidate band | Candidate left margin |
|---|---:|---:|
| 800x600 | 800 | 0 |
| 1024x768 | 1024 | 0 |
| 1280x800 | 1066 | 107 |
| 1920x1080 | 1440 | 240 |
| 2560x1080 | 1440 | 560 |
| 3440x1440 | 1920 | 760 |
| 3840x1600 | 2133 | 853 |
| 5120x1440 | 1920 | 1600 |

The candidate band is useful as a policy primitive, but it must be applied
only to elements whose owner has opted into that logical canvas. Applying it to
all Render2D submissions also changes text, cursors, tooltips, direct HUD
primitives, window movies, and any unrelated 2D scene that shares the exit.

## Coordinate classes and responsive policy

The future policy should be expressed in terms of an element's owner and
anchor, not its file extension alone.

### Responsive tiers

1. **Native 4:3:** no behavior change. Existing creation-resolution scaling,
   ControlBar scheme scaling, APT behavior, and physical input must remain
   byte/visually compatible.
2. **Near-wide (16:10 and 16:9):** retain the existing vertical design scale;
   center-owned content stays in a safe 4:3-like canvas while edge-owned HUD
   elements can use the newly available side space only after their window and
   input regions move together.
3. **Ultrawide:** keep the same height-led policy, with a minimum safe-area
   width. Center-owned modal screens remain centered; edge-owned HUD pieces
   anchor to the chosen safe-area edge; full-screen backgrounds/movies are
   explicitly cover/stretch assets; tactical world visibility comes from 040.

### Element classification

| Class | Examples | Policy |
|---|---|---|
| Center-anchored | modal popups, frontend menu bodies, score/review panels, centered cinematic text | transform the logical root as a unit and center it in the safe area; preserve internal layout |
| Edge-anchored | ControlBar marker/HUD groups, radar/command regions, tooltip/cursor edge offsets | anchor the complete visual and hit-test group to a physical or safe-area edge; never move only artwork |
| Full-screen cover | splash/background images, transitions, global movies, letterbox | opt into cover/stretch semantics independently; do not use this as the general UI policy |
| World-space | floating text, world animations, tactical radius/build visuals | leave in tactical/world projection space; only adjust the tactical camera or world projection deliberately |
| Screen overlay | subtitles, messages, named/superweapon timers, debug text | give each owner an explicit safe-area anchor and scale rule; audit direct pixel code |
| APT-owned | Main Menu, Online Shell, Living World and other APT screens | transform only at a verified APT screen/stage boundary after runtime inspection |
| Input-only geometry | GameWindow regions, ControlBar buttons, APT callback hit targets | apply the inverse of the visual transform before hit testing, or move the actual regions with the visuals |

## Stretch locations and explicit non-stretch locations

Stretch/cover is appropriate only where the asset is intended to fill the
frame: splash/transition backgrounds, letterbox/movie surfaces when the game
already requests fullscreen playback, and explicitly selected background
artwork. It is not appropriate for text, cursor art, tooltip boxes, command
buttons, ControlBar skin layers, modal panels, or world-space overlays unless
their owner explicitly requests it.

The critical audit rule is that a `drawImage` call does not reveal whether its
asset is a background or a button. The owner, source rectangle, and clipping
behavior have to decide. Mapped-image names and the absent retail data are
insufficient evidence for a blanket stretch rule.

## Proposed future `041-widescreenui` plan

This is an implementation plan only. The directory and feature are not being
created in this investigation.

### Phase 0 — capture contracts before changing behavior

* Recover representative retail `.wnd`, ControlBar INI, APT, mapped-image,
  language, and movie data from the user's archives.
* Record each screen's root creation resolution, named root bounds, scheme
  `ScreenCreationRes`, marker positions, APT stage dimensions, and whether a
  screen is modal, edge-owned, or full-screen.
* Add no global transform. Verify the 4:3 baseline first, including menu,
  load, tactical, replay, tooltip, popup, movie, subtitle, and Living World
  paths.

### Phase 1 — one policy record and safe-area arithmetic

* Add a tiny TU-scoped policy/helper for display size, safe-area rectangle,
  center/edge anchors, and forward/inverse integer mapping.
* Keep the 4:3 path an exact no-op.
* Define rounding and clipping once. Do not temporarily overwrite
  `TheDisplay` width around arbitrary calls; nested parser/scheme calls make
  that stateful approach fragile.

### Phase 2 — GameWindow roots and input as one operation

* Hook the verified `.wnd` parse boundary or the root layout result so the
  selected root policy is applied once.
* Preserve the parser's parent-relative child contract. Do not add a second
  transform to child rectangles.
* Move/scale the real GameWindow hit regions with their visuals, or map the
  physical mouse point into the same logical space before
  `winPointInChild`/`winPointInWindow`. Test capture, drag, modal, tooltip,
  focus, and keyboard bubbling.
* Cover menus, message boxes, loading screens, replay, popups, and ControlBar
  child regions individually.

### Phase 3 — ControlBar owner path

* Apply the policy at scheme selection/initialization and to the named marker
  geometry, preserving the existing `ScreenCreationRes` multiplier model.
* Treat `ControlBar.wnd` hit regions, marker positions, direct W3D callback
  offsets, scheme images, and special-power text as one group.
* Test normal, observer, low-control-bar, production queue, radar, cameo
  movie, command transitions, upgrade/purchase science, tooltips, and all
  side/player-template branches.

### Phase 4 — ShellMenuScheme and direct screen overlays

* Give `ShellMenuScheme::draw` its own center/edge/full-screen policy because
  its source stores direct integer positions rather than `.wnd` creation
  rectangles.
* Audit direct `InGameUI` positions: popup percentage conversion, subtitle
  800x600 multiplier, named/superweapon timers, message lists, RMB anchor,
  build/radius indicators, and any verified post-draw branch.
* Make text wrapping use the resulting safe-area width, not an unrelated
  physical width, for center-owned panels.

### Phase 5 — APT/Living World after runtime evidence

* Trace one frontend APT screen, one online APT screen, and the Living World
  screen through screen construction, stage size, draw, callback hit testing,
  hide/show, and teardown.
* Only then add a screen/stage transform or per-screen safe-area metadata.
  Keep APT changes separate from GameWindow and ControlBar hooks.
* Verify BannerUI, GuiFX, load/score/objectives/player-status screens and
  region callbacks independently.

### Phase 6 — final overlays and regression matrix

* Explicitly classify fullscreen global movies, per-window movies, cursors,
  tooltips, letterbox, cinematic text, and transitions.
* Use the resolution matrix in this document plus native 4:3, windowed mode,
  load-screen render, replay, observer, multiplayer, APT, and Living World
  scenarios.
* Require visual checks for anchoring, no double-scale, no clipped hit region,
  no stretched text, and no changed 4:3 behavior. Build and test the feature
  only after the source/ledger changes are independently identified.

### Candidate semantic hook inventory

These are ownership points, not new addresses:

* `.wnd` `parseScreenRect` / root layout result;
* `ControlBarSchemeManager` selection and `ControlBarScheme::init` marker
  geometry;
* `ShellMenuScheme::drawImage`/`drawLine` ownership path;
* `InGameUI` direct percentage/pixel overlay functions;
* WindowManager mouse conversion before GameWindow hit testing;
* verified APT screen/stage creation and show/hide boundary;
* per-window movie draw callback versus global fullscreen movie draw;
* only the explicit final presentation path for elements already classified as
  full-screen cover.

### What the future feature must not touch casually

* Do not change the 040 tactical camera or `W3DView::m_2DCamera` as part of UI
  work.
* Do not change global `Render2DClass` coordinate range, a shared viewport, or
  surface-copy rectangles as a universal UI fix.
* Do not overwrite `TheDisplay` width around calls without a proven complete
  nesting model.
* Do not assume APT uses GameWindow `.wnd` scaling.
* Do not modify `tools/modbuild.py`, ship a feature, or add a test EXE during
  the research phase.
* Do not edit or recreate absent retail UI data from memory. Recover the
  actual archive files first.

## Relationship to existing work

### 040 tactical Hor+

040 is a focused tactical-camera change. It recomputes the tactical view
plane for the display aspect and preserves the native vertical extent while
revealing more horizontal world. Its owner is the tactical 3D projection, so
it should remain independently testable and should not be folded into UI
layout transforms.

### Historical 041 UI experiment

The removed historical feature temporarily changed display width while
`parseScreenRect` and ControlBar scheme selection ran, translated roots, and
adjusted ControlBar marker offsets. It correctly identified that `.wnd` and
ControlBar are separate paths, but it was a naked payload and its visible
result was not accepted. Keep it as historical evidence only; do not restore
its source as the new feature.

### Current 042 renderer experiment

042 keeps Render2D's full physical range, changes the final viewport to a
centered height-led 4:3 band, and maps the ready-surface copy destination as a
second exit. Its tests prove arithmetic and detour construction, not that all
UI owners share the same intended presentation. The current branch also has a
pre-existing blank-line edit in that file. The research conclusion is that a
renderer-wide intervention is too broad for the first UI implementation,
especially because fullscreen movies, cursors, tooltips, APT, direct W3D
draws, and input do not share one layout contract.

## Unknowns to resolve before implementation

1. Exact `CREATIONRES` and root rectangles for representative retail `.wnd`
   files.
2. Exact default/side-specific `ScreenCreationRes`, image parts, and marker
   rectangles in retail ControlBar INIs.
3. APT stage dimensions, root transforms, internal clipping, and input mapping
   for frontend and Living World screens.
4. Which shell branch/data combination is used for each game mode when the
   source `.wnd` fallback and BFME APT thunk differ.
5. The complete identity of all retail `InGameUI` post-draw branches that are
   currently represented by byte-true thunks.
6. Which mapped-image and movie assets are intentional cover/stretch assets.
7. Windowed-mode client-area and mouse-limit behavior for every safe-area
   policy.

## Confidence summary and recommended order

High-confidence facts are the `.wnd` independent scaling and parent-relative
geometry, physical mouse hit tests, GameWindow draw order, ControlBar's
`ScreenCreationRes` multiplier, mapped-image load directories, Render2D pixel
mapping, frame order, W3DView's separate 2D camera, movie buffer ownership,
and Living World's APT visibility ownership.

Medium-confidence facts are the exact Shell branch used in every mode, the
screen-specific retail asset values, and the interaction of partially
reconstructed post-draw bodies with all overlays.

Low-confidence facts are any APT coordinate policy and any claim that a
renderer-level viewport is visually correct for every BFME UI family.

Recommended order is: recover representative retail data; freeze the 4:3
baseline; implement safe-area helpers; solve GameWindow plus inverse input;
solve ControlBar; solve ShellMenuScheme/direct overlays; trace and solve APT;
then classify fullscreen movies/transitions and run the complete matrix.

## Git and verification handoff

The only intended new file from this task is this research document. The
existing `042-ultrawide-render.cpp` edit remains untouched. `check_csv.py` and
`git diff --check` passed. No production build was run because this request
was explicitly investigation-only. The document is intentionally not
committed here: the required pre-commit rebase is blocked by the unrelated
unstaged 042 edit, and preserving that user work is safer than stashing or
including it in a research commit.

## Phase 1 implementation findings

### Retail data recovered

The representative retail data was inspected read-only from these local
archives:

* `/home/thag/Games/The Battle for Middle earth/Window.big`
* `/home/thag/BFME1/window.big`

Both copies contain the same 18 `.wnd` entries. No retail archive was modified
and no proprietary asset was copied into Git. Representative `CREATIONRES`
records are all `800 600`:

* `window\menus\blankwindow.wnd`: root `0 0 -> 800 600`.
* `window\menus\mapselectmenu.wnd`: root `0 0 -> 800 600`; children include
  `ListboxMap 200 96 -> 560 448` and `ButtonOK 22 554 -> 196 590`.
* `window\menus\shellgameloadscreen.wnd`: root `0 0 -> 800 600`; children
  `ProgressLoad 608 568 -> 756 584` and `StaticTextLegal 140 570 -> 660 598`.
* `window\replaycontrol.wnd`: root `412 384 -> 600 456`; child
  `ButtonPause 420 424 -> 496 448`.
* `window\controlbar.wnd`: root `ControlBarParent 0 416 -> 800 600`; it is
  intentionally phase-1 pass-through.
* `window\ingamepopupmessage.wnd`: root `164 124 -> 336 280`; it is
  intentionally pass-through because message overlays are deferred.

`QuitMessageBox.wnd`, `LanLobbyMenu.wnd`, and `MainMenu.wnd` were not present in
either local `Window.big`; the implementation recognizes those names when a
different retail branch supplies them rather than inventing their data.

### Implemented policy and pipeline

`mods/features/041-widescreenui/src/widescreen_ui.cpp` is one CRT-free,
no-STL, no-external-DLL payload. It uses:

```text
safeHeight = physicalHeight
safeWidth  = min(physicalWidth, floor(physicalHeight * 4 / 3))
safeLeft   = floor((physicalWidth - safeWidth) / 2)
safeTop    = 0
map(source, origin, span, creation) = origin + source * span / creation
```

The integer division is C++ signed truncation toward zero; shipped `.wnd`
coordinates are positive. The normal payload returns without writing parser
locals for every display at or below 4:3, preserving retail bytes and rounding
exactly. `--ui-debug` keeps the same selected roots but uses a centred square
safe area, so `3440x1440` visibly becomes a `1440x1440` band.

The first hook at `winCreateFromScript` entry classifies the active by-value
`AsciiString`: the first dword is the proven `StringBase<char>::m_data`, whose
retail header places characters at `m_data + 8`. Selected `FULLSCREEN` roots are
`BlankWindow`, `MainMenu`, `MapSelectMenu`, `LanLobbyMenu`, and
`ShellGameLoadScreen`; selected `CENTERED_UI` roots are `MessageBox`,
`QuitMessageBox`, and `ReplayControl`. `ControlBar`, its popup description,
`InGamePopupMessage`, experience/IME windows, and all other roots are
`PASSTHROUGH`.

The parser hook is intentionally local rather than a display-width spoof. The
current 453-byte `parseScreenRect` body is at RVA `0x004854F0`; its sole caller
is at RVA `0x00488127` and passes four output globals. The capture site at RVA
`0x00485604` runs before the first `fild/fmul` pair and receives the current
parser ESP through the generated `stackaddr:0` shim. The transform site at RVA
`0x00485648` runs after all four retail float-to-int conversions and before the
unchanged `parent` branch. Proven local offsets are `createX +0x1C`,
`createY +0x20`, `loX +0x24`, `loY +0x28`, `hiX +0x2C`, and `hiY +0x30`. The payload
replaces those four scaled absolute values; retail then subtracts the existing
`parent->winGetScreenPosition`, so the root receives `safeLeft` once and
children/grandchildren remain parent-relative. Mouse hit testing therefore
uses the same `GameWindow` geometry; no world input, camera, ray, minimap, or
renderer path is touched.

`tools/cave.py` gained the narrowly scoped `stackaddr:N` generated-shim form
needed for the two parser-local hooks. `tools/modbuild.py` registers
`041-widescreenui` as unshipped, adds `--ui-debug`, and reports every hook's
original bytes, patched bytes, payload RVA, displaced length, and resume RVA.
The feature does not use any 040 or 042 target.

### Static and manual-test scope

At `3440x1440`, normal selected UI uses the centred `1920x1440` band with
`760`-pixel side margins. Debug selected UI uses the centred `1440x1440` band
with `1000`-pixel side margins. At `5120x1440`, normal selected UI uses the
`1920x1440` band with `1600`-pixel side margins. Expected-to-change screen
names are the selected ordinary `.wnd` roots above. Expected-unchanged names
include `ControlBar.wnd`, `ControlBarPopupDescription.wnd`,
`InGamePopupMessage.wnd`, APT `.wnd` controls, and direct ShellMenuScheme,
Living World, subtitles/timers/messages, renderer viewport, `m_2DCamera`, and
fullscreen movie paths.

The focused source/binary suite covers the representative rectangle, native
4:3 root/child/grandchild exact equality, ultrawide parent-relative geometry,
the debug square, current retail hook bytes, generated stack-frame shims, and
absence of 042 detours. The focused run passed `77 tests, 14 subtests`; the
ledger check passed with `161761` function rows and `77847` symbol rows.

### Phase 1 status

The three requested executables were built and statically verified. Runtime
visual status is intentionally **awaiting manual testing**; no claim is made
about the visual result until the target screens are launched at the requested
resolutions. Phase 2 is not started.
