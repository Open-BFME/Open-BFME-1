# 043-replaycam: rotate, tilt and zoom the camera in replays

Retail BFME1 gives a replay one camera: fixed yaw, fixed pitch and a height
ceiling. This adds three more controls, all driven by the engine's own camera
code. It is in the repository bundle, `mods/dist`.

| Key | Does |
|---|---|
| `[` / `]` | rotate the camera left / right |
| `PageUp` / `PageDown` | zoom in / out, past retail's ceiling |
| `,` / `.` | pitch the camera down / up |
| `/` | show the controls card again |

Keys act while held. Retail's own `CAMERA_RESET` (numpad 5) puts everything
back. A card listing the controls appears a few seconds into every replay.

Replay-only: the hook returns immediately unless `TheGameLogic`'s mode is
`GAME_REPLAY`, so it cannot affect a match, a skirmish or the shell.

## How it works

BFME1 ships a finished, tuned keyboard camera and never binds a key to it.
`InGameUI::update` reads four flags every client frame (`InGameUI+0x12B4` to
`+0x12B7`: rotate left, rotate right, zoom in, zoom out) and drives the tactical
view from them. No `CommandMap.ini` entry binds them, and their eight setters
(RVA `0x0043A6F0` to `0x0043A760`) have no callers.

One detour at the entry of `InGameUI::update` (RVA `0x004410C0`) sets those
flags from the keys, so nothing can clear them before the engine reads them.
Pitch goes through `View::setPitch`, whose −36° floor stops a held key from
inverting the camera.

Zoom needs two knobs. The far clip plane is `TheGlobalData+0xA28` × 1800, and at
retail's multiplier the terrain covers 1% of the frame by height 1121. The mod
doubles that multiplier and clears `View+0x44`, so the engine skips its height
clamp; the mod then clamps height itself, against the floor and ceiling the
engine supplies. Both values are latched on entering a replay and restored on
leaving. Unclamped, the geometric zoom went from 600 to 48,653,620 in six
seconds.

The card uses `InGameUI::message`, the engine's own message feed, so it needs no
draw code and fades by itself.

## Build

`python3 tools/modbuild.py --dist` builds the bundle into `mods/dist/`.

## Verified

Retail 1.03 (patch 2.22), one replay on Fords of Isen, the same script against
both builds. Pixels changed while a key was held:

| | retail | this build (paused) |
|---|---|---|
| idle, no key | 12,313 | **0** |
| rotate right `]` | 1,428 | **966,933** |
| pitch up `.` | 28,191 | **1,565,569** |

Retail's keys all stay inside its own idle band. Zoom, measured with the replay
running, moved 1,014,124 px against this build's idle 32,077, and the height
stopped exactly at 1800 and 120.

## Limits

* Zoom does not redraw while the replay is paused: height is a target the view
  approaches on the logic tick. Rotate and pitch work paused.
* Above the horizon the sky renders black; there is no skybox.
* BFME's recorded replay camera (`UseCameraInReplay`), which EA shipped
  disabled as not working, stays off.
