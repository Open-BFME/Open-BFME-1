# Astra interpolation seam audit - worker 1

Static semantic-recovery note for the two worker-1 targets in the untouched
BFME1 v1.03 image `D:\BFME1\lotrbfme.exe`. The image base is `0x400000`.
Addresses in the `RVA` columns are image RVAs; a retail instruction address
written as `VA` is `RVA + 0x400000`. Values read from vtables and import
thunks are absolute VAs. No game process was launched, the retail image was
not modified, no build or test loop was run, and no ledger or source file was
changed by this audit.

`PROVEN` below means that the stated bytes or data edge are closed in the
retail image. `PLAUSIBLE` means that the retail shape and the readable source
agree, but a boundary, name, vtable interpretation, or call cone remains
open. `OPEN` means that the requested claim could not be established from the
bounded static scan.

## Bottom line

| Target | Finding | Status |
|---|---|---|
| `b_006f3fc0` | The body at RVA `0x006F3FC0` / VA `0x00AF3FC0` is the strong `W3DDisplay::draw` candidate. The W3DDisplay constructor installs a vtable whose `+0x1C` entry is thunk VA `0x004093EF`, and that thunk jumps to this body. The `Display` callback member at `+0x2C`, first-view use, camera update, clock, statistics and render-helper shape all agree with the readable `W3DDisplay::draw` donor. The C++ spelling is not ledger-safe because no matched row names this exact body and the rendering helper is generated. | Owner/slot PROVEN; method spelling PLAUSIBLE |
| Target-1 timing | Primary add is at RVA `0x006F40E8`; alternate add is at `0x006F4132`. Both call exact `WW3D::Sync` RVA `0x008FD310` / VA `0x00CFD310`. The primary path is a one-step add; the alternate path is a frame-delta-scaled add. All gates are listed below with their actual polarity. | PROVEN |
| `Display::draw` label supplied for VA `0x0043FCD8` | The five-byte thunk jumps to VA `0x0080F5E0` / RVA `0x0040F5E0`, a 24-byte `getNextView(View *)` body. In the raw W3DDisplay table, `+0x74` is instead thunk `0x00442A05` to `getFirstView` RVA `0x0040F5D0`. The supplied draw label is false for this image. | PROVEN correction |
| Render order | Retail code proves `virtual update path -> WW3D::Begin_Render -> virtual draw path -> WW3D::End_Render` in the terrain-LOD loop at RVA `0x006E8F2B`, `0x006E8F66`, `0x006E8F76`, `0x006E8F7B`. A second generated render helper has the same direct order at VA `0x00AEB552`, `0x00AEB60C`, `0x00AEB740`, and `0x00AEB923`. Mapping those virtual slots to the requested main-presentation names is internally inconsistent between the raw table and current source/shims, so the exact main draw call cone remains open. | Instruction order PROVEN; main-presentation identity OPEN |
| Transform-sensitive work | The readable W3DDisplay donor puts particle update, water render-target updates, and projected-shadow render-target updates before the main `Begin_Render`/`drawViews` block. The particle comment explicitly says it reads render-object transforms before the logical reset. Water and projected-shadow source paths render/read render objects, but their exact retail linkage to the main presentation body is not closed. Selection/health-bar UI is post-draw and uses logical Drawable positions, not the render-object matrix. | Source placement PLAUSIBLE; exhaustive retail placement OPEN |

The important consequence for `049-unitinterp` is unchanged by the address
correction: a hook wrapped around `Display::drawViews` cannot affect a
consumer that runs before that call, and the ordinary model module later
writes the authoritative `RenderObjClass` matrix during drawable rendering.

## 1. RVA `0x006F3FC0` (`b_006f3fc0`)

### Boundary and owner evidence

`reverse/ghidra_functions.csv` records `0x006F3FC0` as `FUN_00af3fc0` with
size `1178` (`0x49A`). Linear x86 decoding of the prologue and all reachable
branches reaches the cleanup `ret` at RVA `0x006F445F`; that inclusive decode
spans `0x4A0` bytes. This five-byte disagreement is a boundary/ledger issue,
not a reason to change the ledger in this worker report. The stale
`docs/apt-ui.md` size `3600` is not supported by either the Ghidra row or the
actual control flow.

The direct code thunk in `reverse/functions.csv` is:

```text
thunk RVA 0x000093EF / VA 0x004093EF
    jmp VA 0x00AF3FC0
```

The W3DDisplay constructor at RVA `0x006EF850` stores vtable VA
`0x0111EDD0` at `this+0x00` (the store is at RVA `0x006EF876`). The raw table
entry at `0x0111EDD0+0x1C` is VA `0x004093EF`. Therefore this body is the
override reached through the W3DDisplay table at that slot. The base Display
table installed by the Display constructor is VA `0x010F0DC0`; its same
offset contains a small virtual-forwarder thunk rather than this W3D body.
That is direct owner/slot evidence, although the ledger still intentionally
calls the body `b_006f3fc0`.

The method name `W3DDisplay::draw` is a semantic recovery, not a new ledger
claim. The readable source has the same unusual sequence of
`IsIconic`, `updateAverageFPS`, debug callback dispatch, first-view/camera
work, `WW3D::Sync`, time throttling, statistics and render-helper work in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp:1700-2040`.
The member layout used by the body is also the Display layout: the callback
pointer is at `+0x2C`, as spelled by the local W3DDisplay class in
`W3DDisplayDrawCurrentDebugDisplay.cpp:22-38`.

This is the safe identity statement:

```text
W3DDisplay owner: PROVEN
W3DDisplay draw-slot override: PROVEN
source-level method spelling W3DDisplay::draw: PLAUSIBLE, strongly supported
ledger-name replacement: OPEN and intentionally not attempted here
```

### The `+0x2C` callback dispatch

At VA `0x00AF3FF9` (RVA `0x006F3FF9`) the body loads `[this+0x2C]` and compares
it with the three exact callback addresses supplied in the assignment:

```text
0x0042F9F0
0x0043413F
0x0040D779
```

The matching branch callsites are:

| Instruction RVA | Call target | Static target | Finding |
|---:|---:|---:|---|
| `0x006F4005` | thunk VA `0x00422BEC` | body RVA `0x006F0300`, `gatherDebugStats@W3DDisplay`, size `4490` | exact named/matched callee |
| `0x006F4015` | thunk VA `0x00448216` | body RVA `0x006F2CC0`, generated, size `3881` | exact edge; semantic name open |
| `0x006F4025` | thunk VA `0x0040A03D` | body RVA `0x006EE800`, generated, size `2784` | exact edge; semantic name open |

The constants and the `+0x2C` field match the debug-display callback member
and the three-way callback shape in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawCurrentDebugDisplay.cpp:40-69`.
The timing body calls the branches before its view/clock work, so this is
debug/statistics preparation, not evidence that the supplied `0x0043FCD8`
pointer is `draw`.

### Important vtable correction inside Target 1

At VA `0x00AF4043` (RVA `0x006F4043`) the body executes:

```asm
mov  edx, [this]
call dword ptr [edx+0x74]
mov  edi, eax
...
mov  ecx, edi
call VA 0x00B44530       ; updateCameraMovements
```

The raw W3DDisplay table at VA `0x0111EDD0` contains:

```text
vtable +0x74 = VA 0x00442A05 -> VA 0x0080F5D0 / RVA 0x0040F5D0
```

The target body is four bytes:

```asm
mov eax, [ecx+0x18]
ret
```

This is `Display::getFirstView`. The return value is then used as the view
object for `W3DView::updateCameraMovements` at RVA `0x00744530`, so the
`+0x74` call cannot be a void `Display::draw` call in this image. This is
also why the direct first-view result is saved in `EDI` before the clock
branch. The supplied `0x0043FCD8` value is not this entry; it is the next
raw table entry, `+0x78`, and is `getNextView` (Target 2 below).

### Exact client-frame order

The following is the byte order of the body. “Before draw” here means before
the render block/delegated helper; the call at `0x006F4043` is first-view
acquisition, not a draw call.

| RVA range / callsite | Operation and effect | Status |
|---|---|---|
| `0x006F3FCF-0x006F3FE5` | Load `ApplicationHWnd` from `0x012ED238`; call imported `IsIconic` through `0x01359020`; if nonzero, jump to cleanup RVA `0x006F4458`. | PROVEN |
| `0x006F3FEB` | Call thunk VA `0x00406C6C` to exact body RVA `0x006E85F0`, the matched `W3DDisplay::updateAverageFPS`. | PROVEN |
| `0x006F3FF2` | Call thunk VA `0x0044068D` to matched body RVA `0x006E9190` (`bfmeGo1087A@BfmeQ1087`, size `95`). The helper's role in the draw donor is not independently renamed here. | PROVEN edge; semantics PLAUSIBLE |
| `0x006F3FF9-0x006F4025` | Compare `m_debugDisplayCallback` and optionally run one of the three debug/statistics bodies listed above. | PROVEN |
| `0x006F402A-0x006F4043` | Read `TheGameClient` at `0x012F1464`, sample `GameClient+0xC4`, save the negated byte as `BL`, and call vtable `+0x74` to obtain the first view in `EDI`. | PROVEN |
| `0x006F404E-0x006F4075` | Call GameClient vslot `+0x68` to obtain `currentFrame`; compute `ESI = currentFrame - [0x012BAA2C]`. If `GameClient+0xC4 == 0`, zero `ESI` and leave `[0x012BAA2C]` unchanged. Otherwise call the same frame getter again and store that value in `[0x012BAA2C]`. | PROVEN |
| `0x006F4075-0x006F40A8` | Build `BL`: `isGamePaused` body RVA `0x00383480` is called through VA `0x00422C96`; if not paused, nonzero `GlobalData+0xC59` sets `BL`; `isTimeFast` body RVA `0x00336FB0` through VA `0x0040A8A8` also sets `BL`. | PROVEN |
| `0x006F40A8-0x006F40DA` | Evaluate the primary animation-add gates. A failure jumps to alternate RVA `0x006F4104`; a pass reaches camera update and the one-step add at `0x006F40E8`. | PROVEN |
| `0x006F40DC-0x006F40F9` | On the primary path call `W3DView::updateCameraMovements` body RVA `0x00744530` through thunk VA `0x0040E101`; then add `[0x012BB1CC]` to `[0x012F8064]`, store it, push the new time and call `WW3D::Sync` VA `0x00CFD310`. | PROVEN |
| `0x006F4104-0x006F4141` | Alternate path: begin statistics, optionally update terrain tracks, add `[0x012BB1CC] * ESI` to `[0x012F8064]`, store it, and call the same `WW3D::Sync`. | PROVEN arithmetic; track-helper name PLAUSIBLE |
| `0x006F4142-0x006F445F` | Remaining wall-clock throttle, screenshot/statistics state, generated render-helper calls, tactical/game-mode loop and final display callback/tail. Detailed below. | PROVEN control flow; helper identities partly OPEN |

The primary path returns after the `Sync` cleanup at RVA `0x006F4103`; it
does not reach the `0x006F4142` remainder. The alternate path performs the
remainder after its `Sync`.

### Every gate on the animation accumulator add

Let:

```text
c4       = byte [TheGameClient + 0xC4]
noAdvance = (c4 == 0)       ; saved as BL and [ESP+0x17]
frame    = GameClient vslot +0x68 result
delta    = frame - [0x012BAA2C]
```

The body does not use the natural-language name “advance flag” as a truth
value. The exact polarity is `BL = 1` when `c4 == 0`, not when the client is
advancing.

The frame-history behavior is:

```text
delta = current frame - previous frame
if c4 == 0:
    ESI = 0
    previous frame remains unchanged
else:
    ESI = delta
    previous frame = current frame
```

The primary add at RVA `0x006F40E8` is reached only when all of these are
true:

1. The earlier `IsIconic(ApplicationHWnd)` test was false. A true result
   exits the complete body before any add.
2. `c4 != 0`, because `saved noAdvance` is tested at `0x006F40AC` and a true
   value jumps to the alternate path.
3. `BL != 0` at `0x006F40B0`. This means either the game was not paused and
   `GlobalData+0xC59 != 0`, or `ScriptEngine::isTimeFast()` returned true.
   The `GlobalData+0xC59` test is skipped when `isGamePaused()` is true.
4. `GameLogic+0x11D == 0` at `0x006F40BA-0x006F40C2`. A nonzero byte forces
   the alternate path.
5. `current client frame % 30 != 0`. The division by `0x1E` begins at
   `0x006F40C4`; a zero remainder at `0x006F40D8-0x006F40DA` forces the
   alternate path.

On the primary path the exact arithmetic is:

```text
[0x012F8064] = [0x012F8064] + [0x012BB1CC]
WW3D::Sync([0x012F8064])
```

The setter for `[0x012BB1CC]` is the separate body at RVA `0x006FB9C0`; this
report does not infer a fixed runtime value from the compiled immediate.

The alternate path at RVA `0x006F4104` is selected if any primary condition
fails. It calls `Debug_Statistics::Begin_Statistics` body RVA `0x00937EB0`
through VA `0x00D37EB0`. It then performs this optional track branch:

```text
if GlobalData+0xBB9 != 1 and TheTerrainTracks != NULL:
    call thunk VA 0x004017FD -> body RVA 0x0072EEB0
```

The generated body at `0x0072EEB0` starts by reading `WW3D::SyncTime` and
walking a track-system list. The readable donor
`W3DTerrainTracks.cpp:763-816` identifies the likely operation as
`TerrainTracksRenderObjClassSystem::update`; the exact retail name remains
PLAUSIBLE rather than ledger-safe.

The alternate accumulator arithmetic at RVA `0x006F4132` is:

```text
[0x012F8064] = [0x012F8064] + [0x012BB1CC] * ESI
WW3D::Sync([0x012F8064])
```

`GlobalData+0xBB9` therefore gates the optional terrain-track helper, not the
alternate accumulator add. If `c4 == 0`, `ESI` is zero and the alternate add
is a zero add; if `c4 != 0`, `ESI` is the sampled frame delta.

### The remainder beginning at RVA `0x006F4142`

The remainder is after the alternate `Sync` and is not reached by the primary
fast-return path.

#### Wall-clock and tactical throttling (`0x006F4142-0x006F41BF`)

* `[0x012F8224]` bit 0 is a one-time initialization flag. If clear, the body
  sets it, calls imported `timeGetTime` through IAT VA `0x01359544`, and stores
  the first result in `[0x012F8220]`. It then samples the current time on every
  entry.
* The tactical-view virtual at `TheTacticalView` VA global `0x012F1600`, slot
  `+0xD8`, supplies a time multiplier. When the result is greater than one,
  `[0x012BAA5C]` is decremented. If the decremented value remains greater
  than one, the body jumps directly to cleanup at `0x006F4458`; otherwise the
  counter is reloaded from the same tactical query.
* When the multiplier is not greater than one, `[0x012F8220]` is set to
  `currentTime - 0x1E`.
* A nonzero byte at `[this+0x111]` is a second direct early exit to
  `0x006F4458`.

#### Fast-spin time gate (`0x006F41C0-0x006F41FA`)

When `GlobalData+0xBB9 != 1` and `GlobalData+0x1E` is nonzero, the body
repeatedly samples `timeGetTime` while
`currentTime - [0x012F8220] < 0x1D` (29 ms). It finally stores the sampled
time in `[0x012F8220]`. This is a wall-clock loop, separate from the
`WW3D::Sync` accumulator.

#### Statistics/render-target capture path (`0x006F4200-0x006F43D5`)

The path is entered only when both `[0x012F804C] > 0` and
`GlobalData+0xECC != 0`. It sets `GlobalData+0xED0`, computes the float at
`GlobalData+0xED4` from the integer at `+0xECC` and constant VA `0x0111E36C`,
queries window rectangles through imported functions, allocates an image
buffer through VA `0x00C81F70`, and loops over the requested samples.

Within the sample loop:

* VA `0x00AF4334` (RVA `0x006F4334`) calls thunk VA `0x0043E13F` to generated
  body RVA `0x006EB500`, size `1215`, with the current display object and a
  sample argument. The return byte controls whether the following capture
  state is retained. This is the only direct render-shaped subordinate called
  by `b_006f3fc0`; its exact class/method identity is OPEN.
* VA `0x00AF436F` calls thunk VA `0x00441AC9` to the matched
  `W3DDisplay::captureScreen` body RVA `0x006EA890`, size `501`.
* VA `0x00AF43AD` calls thunk VA `0x0043A26A` to matched
  `W3DDisplay::saveScreenShot` body RVA `0x006EDF00`, size `353`.
* The sample counter `[0x012F804C]` is decremented after the loop, and the
  buffer is released through the allocator/free helper at VA `0x00C81EF0`.

If the statistics path is not entered, the fallback at RVA `0x006F43D7`
calls the same generated `0x006EB500` helper with a different argument.

#### Tactical/game-mode loop and tail (`0x006F43D7-0x006F445F`)

If the render helper returns true and the saved state byte at
`[ESP+0x17]` is true, the body calls the tactical virtual at `+0x74` at RVA
`0x006F43F3`. This is a boolean query on the tactical object, not the Display
vtable. A false result can loop back to `0x006F41C0` when GameLogic mode is 1
or 5, or when `isGamePaused()` at VA `0x00422C96` is false. The loop therefore
combines tactical pacing, game mode and pause state.

The final cleanup path checks `[0x012F804C]` and `GlobalData+0xECC`. If the
counter is still positive while `+0xECC == 0`, it decrements the counter,
calls `this` vtable `+0x124` at RVA `0x006F444D`, and tail-calls VA
`0x0043809B` to body RVA `0x00754A10`. The vtable target and the guarded tail
are exact edges, but their source names are OPEN.

There is no direct `WW3D::Begin_Render` or `WW3D::End_Render` call in
`b_006f3fc0`, and there is no direct `Display` vtable call at `+0x7C` or
`+0x80`. The body reaches the generated render helper at `0x006EB500` in the
statistics/fallback path. This is why the method name is semantically strong
but the single-body rendering identity is not ledger-closed.

## 2. Display render order and the supplied VA `0x0043FCD8`

### Address audit

The supplied pointer must be read as a low absolute VA. Its first five bytes
are:

```asm
VA 0x0043FCD8 / RVA 0x0003FCD8: e9 03 f9 3c 00
    jmp VA 0x0080F5E0 / RVA 0x0040F5E0
```

The target body, 24 bytes, is the matched `Display::getNextView(View *)`
shape: load the stack `View *`, return null for a null argument, otherwise
load the View vtable and call its `+0x23C` next link before returning. It is
not `Display::draw`.

The relevant raw W3DDisplay table is VA `0x0111EDD0`:

| Raw W3D table offset | Entry VA | Target body / observed shape | Safe interpretation |
|---:|---:|---|---|
| `+0x74` | `0x00442A05` | `0x0080F5D0` / RVA `0x0040F5D0`, `mov eax,[ecx+0x18]; ret` | `getFirstView` |
| `+0x78` | `0x0043FCD8` | `0x0080F5E0` / RVA `0x0040F5E0`, 24-byte next-link body | `getNextView(View *)` |
| `+0x7C` | `0x00427F75` | `0x0080D9E0` / RVA `0x0040D9E0`, 63-byte shell-guarded view-list walker; calls View `+0x174` and `+0x23C` | update-looking/list-walk body; exact public name open |
| `+0x80` | `0x004414C0` | `0x0080DA30` / RVA `0x0040DA30`, 44-byte list loop; calls View `+0x178` and `+0x23C` | current matched ledger name `Display::drawViews` |
| `+0x84` | `0x0043DA82` | `0x00AEA1C0` / RVA `0x006EA1C0`, 323-byte W3D display video-buffer creation body | `W3DDisplay::createVideoBuffer` |

The base Display table at VA `0x010F0DC0` has the same `+0x74` through
`+0x80` entries and a base function VA `0x00C8C500` at `+0x84`. The related
low-VA thunks are exact:

```text
0x00442A05 -> 0x0080F5D0 -> Display::getFirstView candidate
0x0043FCD8 -> 0x0080F5E0 -> Display::getNextView
0x00427F75 -> 0x0080D9E0 -> shell-guarded View +0x174 walker
0x004414C0 -> 0x0080DA30 -> current matched Display::drawViews body
0x0043DA82 -> 0x00AEA1C0 -> W3DDisplay::createVideoBuffer candidate
```

This raw table is shifted from the labels in the assignment and from the
TU-local comments in `W3DDisplayCalculateTerrainLOD.cpp`. The shift is not a
cosmetic naming issue: it changes which function a virtual call actually
reaches. The safe result is to retain the byte-true body names and report the
slot-name conflict as OPEN.

### Proven render-call order

The exact 44-byte body at RVA `0x0040DA30` / VA `0x0080DA30` is the current
matched `Display::drawViews` loop in `reverse/functions.csv`. Its bytes load
`Display+0x18`, call each View at vtable `+0x178`, then follow the View link at
`+0x23C`. It does not itself call `Begin_Render` or `End_Render`.

An independent retail caller closes the requested four-call order. The exact
matched `W3DDisplay::calculateTerrainLOD` body is RVA `0x006E8E60`, VA
`0x00AE8E60`, size `556`. In each timing sample, its instructions are:

```text
RVA 0x006E8F2B  call [edi vptr+0x80]
RVA 0x006E8F66  call VA 0x00CFE280  ; WW3D::Begin_Render, RVA 0x008FE280
RVA 0x006E8F76  call [edi vptr+0x7C]
RVA 0x006E8F7B  call VA 0x00CFD880  ; WW3D::End_Render, RVA 0x008FD880
```

The source/TU for this matched body names the first virtual `updateViews`
and the second `drawViews` (`W3DDisplayCalculateTerrainLOD.cpp:154-160`),
giving the semantic sequence:

```text
updateViews -> WW3D::Begin_Render -> drawViews -> WW3D::End_Render
```

The instruction order is PROVEN. The semantic names are PLAUSIBLE because
the raw W3D table currently routes `+0x80` to the body already named
`Display::drawViews`, while the raw `+0x7C` body has the update-looking
`View+0x174` shape. This body/source/table disagreement must be resolved
before assigning a new identity or moving an interpolation hook.

The generated helper at RVA `0x006EB500`, VA `0x00AEB500`, size `1215`, has a
second direct render-shaped sequence:

```text
VA 0x00AEB552  call [this vptr+0x80]
VA 0x00AEB60C  call VA 0x00CFE280  ; Begin_Render
VA 0x00AEB66A  call VA 0x00CFD880  ; early End_Render branch
VA 0x00AEB740  call [this vptr+0x7C]
VA 0x00AEB923  call VA 0x00CFD880  ; normal End_Render branch
```

This helper is called by Target 1 at RVA `0x006F4334` and `0x006F43D7` via
thunk VA `0x0043E13F`. Its generated row is byte-matched but its class,
signature and whether the call is the main presentation pass or a statistics
capture pass are OPEN. Consequently the following claims are separated:

* `Begin_Render -> virtual draw -> End_Render` is PROVEN in this helper and
  in `calculateTerrainLOD`.
* The exact *main presentation* caller-to-helper path is OPEN from this
  bounded pass; Target 1 contains no direct Begin/End call.
* VA `0x0043FCD8` is not a valid proof of `Display::draw`; it is proven
  `getNextView`.

### Readable main-draw donor and relative transform consumers

The current readable `W3DDisplay::draw` donor in
`W3DDisplay.cpp:1704-2025` provides the following intended presentation
order around the main view render:

```text
terrain tracks / shroud work
WW3D::Sync
updateViews
particle-manager update
water render-target update
projected-shadow render-target update
End_Statistics
WW3D::Begin_Render
drawViews
UI, mouse, video, overlays
WW3D::End_Render
```

This is source/reference evidence, not a substitute for the unresolved retail
main-call edge. The transform-sensitive items are classified below.

| Consumer | Evidence and position relative to main `drawViews` | Does it read the unit RenderObj transform before `drawViews`? | Status |
|---|---|---|---|
| Particle manager | The donor calls `TheParticleSystemManager->update()` at `W3DDisplay.cpp:1890-1898`, after `updateViews` and before the main render. The adjacent comment explicitly says this placement lets linked particle systems look up an object's render-object transform while the client transform is valid and before reset to the logical transform. | Yes in the source path; it is outside a hook wrapped only around `drawViews`, so it would see the current/unblended matrix. Exact retail call linkage from `b_006f3fc0` is not closed. | Placement PLAUSIBLE; retail edge OPEN |
| Water reflections | The donor calls `TheWaterRenderObj->updateRenderTargetTextures(...)` at `W3DDisplay.cpp:1901-1902`, before the main render. The matched/source water path (`W3DWater.cpp:1235-1318`, `renderMirror` body RVA `0x007A2B00`) opens a separate Begin/scene-render/End pass; the scene render consumes RenderObj transforms. | Yes for objects rendered into the reflection target, if this prepass is active. It occurs before the drawViews hook in the donor. Exact linkage from the retail main display body remains open. | Source placement PLAUSIBLE; retail linkage OPEN |
| Projected shadows | The donor calls the projected-shadow manager's render-target update at `W3DDisplay.cpp:1904-1907`, before main `Begin_Render`. `W3DProjectedShadowManager::updateRenderTargetTextures` is present-unmatched at `W3DProjectedShadow.cpp:346-363`; its `W3DProjectedShadow::updateTexture` path reads `m_robj->Get_Position()` and object bounds before rendering a shadow target. | Yes for active projected-shadow render targets in that path; they would see the pre-hook/current matrix. Exact BFME callsite and full affected-object cone are open. | Source/dataflow PLAUSIBLE; retail placement OPEN |
| Terrain tracks | Target 1's alternate branch calls generated body RVA `0x0072EEB0` when `GlobalData+0xBB9 != 1` and the terrain-track singleton is non-null. The source donor `W3DTerrainTracks.cpp:763-816` reads SyncTime, used track modules and edge timestamps, and releases/fades track state. | No unit RenderObj `+0x18` read was found in this inspected update body. Track render objects may be consumed later by scene rendering, but that exact path was not closed. | Callsite PROVEN; unit-transform conclusion PLAUSIBLE |
| Ordinary model/debris modules | The matched model draw path reaches `W3DModelDraw::doDrawModule` body RVA `0x0077B3F0`; its root submission at RVA `0x0077B680` calls render-object vtable `+0x54` (`Set_Transform`). `RenderObjClass::Set_Transform` RVA `0x009201A0` stores the matrix at RenderObj `+0x18`. This is inside the drawable/view render. | The module is the later authoritative writer. A matrix prewritten by `unitinterp_begin` is overwritten by this eligible module draw, so the hook is not the final consumer seam for ordinary models. | Dataflow PROVEN |
| In-scene shadows and other render-object decals | `W3DShadow.cpp:127-147` and the matched `renderShadows` family show shadow rendering through projected-shadow/render-object code, but the exact ordering inside the View render and the exact decal consumers are not closed in this scan. | OPEN whether each specific pass is before or after the ordinary model write; a pass before the hook or before the module write sees the current/unblended matrix. | OPEN |
| Selection, health-bar, veterancy, caption and construction UI | `W3DView.cpp:1029-1053` calls `Drawable::drawIconUI` in `drawablePostDraw`; `W3DView.cpp:1807-1814` runs that post-draw walker after drawable rendering. `Drawable.cpp:5073-5123,5787-5920` uses logical Drawable position/health-box data and `worldToScreen`, not RenderObj `+0x18`. | No render-object transform read was found in this post-draw UI route; it is after `drawViews`, not a pre-draw consumer. Exact retail helper identities remain partly open. | Source placement/dataflow PLAUSIBLE |

The direct answer to the matrix question is therefore conditional but useful:

1. A consumer that runs before `drawViews` reads the matrix currently stored in
   RenderObj `+0x18`; `unitinterp_begin` has not yet installed its blended
   matrix there. Such a consumer sees the unblended/current matrix.
2. The readable particle placement is an explicit example of that case.
   Water and projected-shadow render-target passes are source-backed examples
   whose scene/shadow paths read render objects, but exact retail main-call
   linkage is still OPEN.
3. Selection and health-bar decals are not evidence of a pre-draw RenderObj
   read in this code: their source route is post-draw and projects logical
   Drawable state.
4. Ordinary model rendering is a separate issue: it writes the RenderObj
   matrix during `drawViews` after the interpolation pre-hook, which explains
   the current feature's final-writer seam.

## Static proof ledger for this worker

| Claim | Evidence | Status |
|---|---|---|
| `b_006f3fc0` body begins at RVA `0x006F3FC0` and has the decoded cleanup at `0x006F445F` | Retail bytes; Ghidra row size `1178` has a five-byte boundary disagreement | Boundary PROVEN; exact ledger size OPEN |
| Body owner is W3DDisplay | W3DDisplay constructor vtable VA `0x0111EDD0`; raw `+0x1C` entry VA `0x004093EF`; thunk jumps to body; `+0x2C`/draw-source shape agrees | PROVEN owner |
| C++ method is `W3DDisplay::draw` | Unique readable donor shape and draw-slot override; no matched ledger row names body and helper is generated | PLAUSIBLE |
| `+0x74` call in Target 1 returns first View | raw entry `0x00442A05` -> four-byte `this+0x18` getter; result passed to camera update | PROVEN |
| supplied VA `0x0043FCD8` is `Display::draw` | thunk target is 24-byte next-view body | DISPROVEN; corrected PROVEN |
| `Display::drawViews` body at RVA `0x0040DA30` | 44-byte list loop, View `+0x178`, next `+0x23C`, current matched row | PROVEN body shape; raw-slot label conflict remains |
| `update -> Begin_Render -> draw -> End_Render` instruction order | exact `calculateTerrainLOD` callsites and generated helper callsites | PROVEN instruction order |
| exact raw slot names `+0x7C/+0x80` for update/draw | raw W3D table conflicts with current source/TU names | OPEN |
| main presentation call chain from Target 1 to the four render calls | Target 1 has no direct Begin/End; generated helper identity/call role open | OPEN |
| particles, water, projected shadows before main draw | readable W3DDisplay donor; only particle transform read is explicit in the comment | Source PLAUSIBLE; retail placement OPEN |
| selection/health-bar UI reads RenderObj `+0x18` before draw | source post-draw route uses Drawable logical position and projection | Not supported; post-draw PLAUSIBLE |

## OPEN items left for the parent audit

* Reconcile the BFME Display vtable order: raw W3D entries put
  `getFirstView`, `getNextView`, an update-looking walker, the matched
  `drawViews` body, and `createVideoBuffer` at `+0x74..+0x84`, while the
  current source/TU comments assign the two view-render slots differently.
* Identify the generated body RVA `0x006EB500` and prove whether its
  `Begin_Render`/virtual-draw/`End_Render` sequence is the main presentation
  path or statistics/screenshot rendering.
* Find a disassembly-backed named caller or an exact vtable/source match for
  the `W3DDisplay::draw` spelling, if a ledger-safe name is required.
* Close the retail call cones for particle update, water reflection targets,
  projected shadow targets, in-scene shadow/decal rendering, and all other
  RenderObj transform consumers relative to the drawViews hook.
* Resolve the Ghidra `1178`-byte range versus the linear decode through
  `0x006F445F` before any future ledger boundary update.

