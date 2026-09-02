# 043-replaycam — the camera controls BFME already has, reachable in a replay

Retail BFME1 gives a replay one camera: fixed yaw, fixed pitch, and a height
ceiling. This exposes three more, all of them the engine's own:

| Key | Does |
|---|---|
| `[` / `]` | rotate the camera left / right |
| `PageUp` / `PageDown` | zoom in / out, past retail's ceiling |
| `,` / `.` | pitch the camera down / up |
| `/` | show the controls card again |

Replay-only: the hook returns immediately unless `TheGameLogic`'s mode is
`GAME_REPLAY`, so it cannot affect a match, a skirmish or the shell. Retail's
own `CAMERA_RESET` (numpad 5) puts everything back.

A card listing all of it appears in the corner a few seconds into every replay,
and `/` brings it back — because a control nobody can find is not a feature.

## This does not implement a camera

BFME1 ships a complete keyboard camera and never binds a key to it.
`InGameUI::update` reads four flags every client frame and drives the tactical
view from them:

```
InGameUI+0x12B4 rotate left    -> view->setAngle(getAngle() - speed)   RVA 0x004413C5
InGameUI+0x12B5 rotate right   -> view->setAngle(getAngle() + speed)
InGameUI+0x12B6 zoom in        -> view->zoomIn()    (h = h*0.96 - 1.0) RVA 0x00441427
InGameUI+0x12B7 zoom out       -> view->zoomOut()   (h = h*1.05 + 1.0)
```

`GameData.ini` even carries the tuning constant — `KeyboardCameraRotateSpeed =
0.1`, the value that block fsubs and fadds at `GlobalData+0xCC8`. The feature is
finished, tuned, and unreachable:

* `CommandMap.ini` binds none of the eight `MSG_META_*_CAMERA_*` events. The
  only camera entry it has is `CAMERA_RESET` on `KEY_KP5`.
* The eight one-line setters at RVA `0x0043A6F0`..`0x0043A760` have **no callers
  anywhere in the image** — each is reached only by a single ILT thunk, and
  every one of those thunks is itself unreferenced.
* The only writes to the flags are the three that *clear* them: the
  constructor, `reset`, and `setInputEnabled`.

So this feature writes those four bytes and lets the engine do the work.

## The card

Six lines through `InGameUI::message`, the engine's own message feed — the
surface BFME already uses to tell a player something. It costs no layout, no
font handling and no draw order, it cannot disturb the renderer, and it fades
by itself:

```
Replay: Ctrl+. pause
[ ] rotate camera
PgUp/PgDn zoom
, . tilt camera
Numpad5 reset camera
/ shows controls
```

Short lines on purpose: the feed is **right-aligned to the viewport edge and
does not wrap**, so the first cut's padded two-column layout stretched every
line clear across the battle. Six on purpose too — the feed shows about that
many before the oldest scrolls off, and a seventh cost the header.

**Getting the right overload matters and the vtable will not tell you.** Three
`message`-family entries sit next to each other, all variadic, all with a
16 KB `_vsnwprintf` buffer. Only their frame sizes separate them:

| slot | frame | reads format at | so the format is | which |
|---|---|---|---|---|
| `+0x38` | `0x4014` | `[esp+0x4020]` | arg**3** | `messageColor(color, fmt, ...)` |
| `+0x3C` | `0x4018` | `[esp+0x4020]` | arg**2** | `message(AsciiString, ...)` — and it alone reads `TheGameText` |
| `+0x40` | `0x4014` | `[esp+0x401C]` | arg**2** | `message(UnicodeString, ...)` ← this one |

The first cut called `+0x38` with two arguments, so it read its format from
uninitialised stack and died on `0x0000002C`. The `+0x3C` sibling resolves its
argument through the CSF string table, which is no use for text that is not in
`lotr.csf`.

The vtable base is **`0x010F5B38`**, read off the store the constructor makes at
RVA `0x0044B834` — not inferred from where a known method sits, which is how the
slot was got wrong in the first place.

Being variadic, `message` is `__cdecl` with `this` as the first stack argument,
and it takes its format **by value and destroys it** (`call 0x00C881D0` on the
parameter slot). So each line is a real refcounted `UnicodeString`, built by
`UnicodeString::UnicodeString(const WideChar *)` at RVA `0x00888DE0` — the
GameEngine one, in the same string TU as `AsciiString`'s literal ctor at
`0x00C88BC0`, **not** the WWLib class of the same mangled name that
`reverse/functions.csv` pins at RVA `0x00065410`. Handing it a static body would
hand its destructor a static body to free.

The card text is a printf format, so a stray `%` in it would be read as a
conversion.

## The hook

One detour, RVA `0x004410C0` — `InGameUI::update` itself, at its entry. Chosen
because it is the function that *reads* the flags: they are set and consumed
inside one call, and nothing can clear them in between. That matters —
`setInputEnabled` clears all four, and a replay is exactly the place the engine
likes to disable input.

Held keys, not toggles: the engine reads these as level, once per frame, and
clears nothing itself.

The five stolen bytes are the head of an SEH frame setup (`push -1` +
`mov eax,fs:[0]`, 8 bytes), both position-independent. The payload therefore
runs before that frame exists and must not fault.

## Zoom needs two knobs, not one

The height ceiling alone buys nothing. `W3DView::setCameraTransform` computes
the far clip plane as `Set_Clip_Planes(10.0, TheGlobalData[+0xA28] * 1800.0)` —
the multiplier being the one the `SET_CAMERA_CLIP_DEPTH_MULTIPLIER` script
action writes. At the retail multiplier the terrain is clipped long before the
camera runs out of room. Measured on Fords of Isen, as the fraction of the
frame with terrain in it:

| height | retail clip depth | clip depth ×3 |
|---|---|---|
| 615 | 98.0% | 97.9% |
| 715 | 95.9% | — |
| 831 | 66.7% | 93.3% |
| 966 | 33.1% | 84.4% |
| 1121 | **1.0%** | 77% |
| 1301 | **0.0%** | 66% |
| 1800 | 0.0% | 45% (the map has run out) |

So the two move together, by one constant. `View+0x44` is the byte
`W3DView::setHeightAboveGround` consults; zero makes it skip its whole clamp
block, and the clamp then happens here instead, against the same numbers the
engine would have used — the floor and ceiling come from the object embedded at
`View+0x24B8`, whose first two vtable slots return them. Both `View+0x44` and
the clip multiplier are latched on the way into a replay and put back on the way
out, never assumed.

**Removing the clamp is not an option.** `zoomOut` is geometric, so six seconds
of an unclamped key took the camera from 600 to **48,653,620**.

**2× and not 3×** because 3× is past what the renderer looks good at: the map
itself runs out, and the terrain skirt shows through as a flat wedge across the
sky.

## Verified

Retail 1.03 (patch 2.22), one downloaded replay on Fords of Isen, the same
script against both builds. Pixels that changed while a key was held:

| | retail | this build (paused) |
|---|---|---|
| idle, no key | 12,313 | **0** |
| rotate right `]` | 1,428 | **966,933** |
| rotate left `[` | 3,596 | **965,951** |
| pitch down `,` | 12,047 | **969,880** |
| pitch up `.` | 28,191 | **1,565,569** |

Retail cannot be paused, so its idle frame still moves by 12,313 px over five
seconds and every key sits inside that band — that *is* the red: nothing
happens, the game is just playing. This build's idle floor is exactly 0 px, so
every number in its column is camera and nothing else.

Zoom measured separately, since it does not apply while paused (below):

| | retail | this build (running) |
|---|---|---|
| idle, no key | 12,313 | 32,077 |
| zoom out `PgDn` | 5,793 | **1,014,124** |

and instrumented, the height itself: `600 → 1800` held at the ceiling with the
cap released, `→ 120` at the floor, both exact.

## Zoom does not apply while the replay is paused

Held against `039-replayctl`'s pause, `PageUp`/`PageDown` move `View+0x40`
correctly — measured 600 → 1800 → 120 with the logic stopped — but the picture
does not change until the replay is running again. Rotate and pitch are not
affected.

The reason is the engine's, not ours: `setAngle` and `setPitch` end in
`setCameraTransform` and apply at once, while height is a *target* that the view
interpolates toward on the logic tick (`CameraAdjustSpeed = 0.3`, "how fast the
camera snaps to the desired height"). With the logic stopped the interpolation
never steps. Fixing it means driving that interpolation by hand, which is a
bigger change than the one this feature is.

## Not what a replay camera is elsewhere in the engine

BFME1 has a *recorded* camera — `SaveCameraInReplays`, `UseCameraInReplay`
(`GlobalData+0xC0D`), `MSG_SET_REPLAY_CAMERA` — and EA turned it off themselves.
`GameData.ini` line 157:

```
UseCameraInReplay = No    ;Not working, don't use it yet.
```

Left alone. This feature is a live camera for the person watching, not a
recorded one.

## Facts banked along the way

* **`commandmapdebug.ini` ships in `ini.big` and is dead in retail.** All 129
  `DebugCommandMap` entries are there — including `DEMO_LOCK_CAMERA_TO_SELECTION`,
  `DEMO_TOGGLE_ZOOM_LOCK`, `DEMO_BEGIN_ADJUST_PITCH`, `DEMO_BEGIN_ADJUST_FOV` —
  but of every `DEMO_*`/`DEBUG_*` meta message exactly one survives into the
  retail binary (`MSG_META_DEMO_PERFORM_STATISTICAL_DUMP`). The file is a
  leftover, not a door. Do not spend time on it.
* `Data\INI\CommandMap.ini` in `ini.big` is **empty** — a header comment and
  nothing else. Every retail binding lives in `Lang\English\CommandMap.ini`
  inside `lang/english.big`: 88 entries, listed there and nowhere else.
* `TheTacticalView` is VA `0x012F1600`, `TheGlobalData` is `0x012ED5C8`.
* `View` vtable: `+0xF8` setAngle, `+0xFC` getAngle (`fld [ecx+0x28]`), `+0x100`
  setPitch, `+0x104` getPitch (`fld [ecx+0x2C]`), `+0x128` getHeightAboveGround
  (`fld [ecx+0x40]`), `+0x12C` setHeightAboveGround, `+0x130` zoomIn, `+0x134`
  zoomOut. Table base VA `0x011217A0`.
* `View::setPitch` (RVA `0x0045B570`) clamps pitch to a **-36° floor** and
  forces exactly `-0.6283185` below it, so a runaway pitch key cannot invert the
  camera. Above the horizon there is no skybox — the sky renders black.
* Every key here is polled once per client frame, so a tap shorter than a frame
  is missed. A human press is 2-4 frames; an `xdotool key` tap is not, and
  mistaking the second for a dead key cost a build. Hold the key when testing.
* **Three `View` rows in the ledger are mis-pinned onto BFME's layout.**
  `?setHeightAboveGround@View@@UAEXM@Z` at RVA `0x0018F257` is a 10-byte
  `mov [ecx+0x44]` stub; the real one is RVA `0x00742E60`, ~215 bytes, writes
  `+0x40`, and carries seven guards and the clamp. `?setZoomLimited@View@@` at
  `0x00912040` writes `+0x48`, which is not the byte the height clamp reads.
  Trusting those two cost a build: the first cut wrote `+0x48` every frame and
  measured nothing. The vtable is the ground truth here, not the ledger.
