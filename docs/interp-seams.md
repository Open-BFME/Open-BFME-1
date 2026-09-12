# BFME1 client-frame and render interpolation seams

Static audit of retail `lotrbfme.exe` v1.03. The input image was the untouched
`D:\BFME1\lotrbfme.exe` (SHA-256
`C1A907C44B84DF129C1F18DC7365EA25BA438F9B8F39A374B86ED852936FF0A9`). No game
process was launched, no executable was patched, and no build or auto-test loop
was run. The untracked `049-unitinterp` sources were read as the proposed
consumer, not modified.

Ledger addresses in this note are RVAs. Retail disassembly addresses are VAs,
so `VA = RVA + 0x400000`. Values copied from vtables and thunks are already
absolute VAs. `PROVEN` means the stated control flow or side effect is closed;
`PLAUSIBLE` means the source/shape is strong but an identity or complete call
cone remains open; `OPEN` means the requested claim could not be established.

> Worker reports 1 and 2 finished after this merge; their final versions are kept
> as `docs/interp-seams-1.md` and `docs/interp-seams-2.md`. Worker 2's final
> report upgrades the four draw-module offsets used by `049-unitinterp`
> (Drawable `+0x150`, module vslot `+0x9C`, interface at module `+0x0C`,
> render object at interface `+0x28` = module `+0x34`) from "consistent" to
> PROVEN against the W3DModelDraw constructor, getter and `doDrawModule` body
> at RVA `0x0077B3F0`.

## Summary

| Target | RVA / VA / size | Proposed name | Callers / callees | Status | Evidence pointer |
|---|---|---|---|---|---|
| 1 | `0x006F3FC0` / `0x00AF3FC0` / 1,178 | `W3DDisplay::draw` or a split display-draw wrapper | thunk `0x004093EF`; first-view, camera, `WW3D::Sync`, render helper `0x006EB500` | PLAUSIBLE | retail `0x00AF3FC0+0x2C`, `+0x40E8`, `+0x413D`; `W3DDisplay.cpp:1585-1847` |
| 2 | supplied `0x0043FCD8` is VA/RVA `0x0003FCD8`, 5-byte thunk to `0x0080F5E0`; true draw body unresolved here | `Display::draw` label is incorrect; `Display::getNextView` is proven at the supplied pointer | render-helper callsites; `Display::drawViews` body RVA `0x0040DA30`, VA `0x0080DA30` | OPEN | retail `0x0043FCD8`, `0x004414C0`, `0x0043DA82`; terrain loop `0x00AE8F2B-0x00AE8F7B` |
| 3 | `0x0040DA30` / `0x0080DA30` / 44; `0x0042E570` / `0x0082E570` / 186; model body not closed | `W3DView::update` -> `Drawable::draw` -> `W3DModelDraw::doDrawModule` | update-view region walk; drawable callback; model/debris module writers | PLAUSIBLE | `W3DView.cpp:1123-1440`; `Drawable.cpp:4971-4987`; `W3DModelDraw.cpp:2170-2241` |
| 4 | `0x001BE700` / `0x005BE700` / 65; `0x001C0BE0` / `0x005C0BE0` / 217; `0x00421520` / `0x00821520` / 617 | Object-to-drawable transform synchronization | Thing transform setters -> Object transform callback -> Drawable; phase-2 history recorder | PLAUSIBLE | `Thing.cpp:262-373`; `Object.cpp:1992-2014`; phase-2 `0x0038DE89-0x0038DECF` |
| 5 | `0x0038DA10` / `0x0078DA10` / 2,129 | `GameLogic::update(int phase)` | `GameEngine::_bfme_updateNetworkAndLogic`; Partition/Collision, sleepy vectors, AI/post batch | PROVEN | retail `0x0038DE89-0x0038E17F`; `docs/bfme1-logic-phases.md` |
| 6 | `0x0006E910` / `0x0046E910` / 392 | `GameEngine::update` client-frame ratio | engine loop; `WW3D::Sync` and rope/model interpolation readers | PLAUSIBLE | retail `0x0046E981-0x0046EA81`; `GameEngineUpdate.cpp:154-231` |
| 7 | `0x009201A0` / `0x00D201A0` / 125 | `RenderObjClass::Set_Transform` | W3D model/debris and other render modules; Scene registration | PLAUSIBLE | retail `0x00D201A0-0x00D2021C`; `rendobj.cpp:453-461`; `hlod.cpp:2278-2281` |
| 8 | `0x008FD310` / `0x00CFD310` / 21; `Get_Frame_Time` RVA `0x007239A0` / VA `0x00B239A0` / 12 | `WW3D::Sync` and its time consumers | display clock, animation, particles, snow, tracks, shaders, mappers, camera | PLAUSIBLE | `ww3d.cpp:1333-1337`; `WW3D_Get_Frame_Time.cpp:16-18`; focused absolute-reference scan |

No new ledger row is added by this audit. The existing matched rows are not
relabelled: the remaining names lack the matched-caller identity evidence
required by `AGENTS.md`.

## 1. `b_006f3fc0`: display-frame wrapper and animation clock

### Identity and boundary

The complete retail body is RVA `0x006F3FC0`, VA `0x00AF3FC0`, through `ret` at
VA `0x00AF445F`; the decoded body is 1,178 bytes. Its generated thunk is RVA
`0x000093EF`, VA `0x004093EF`. The body is not identity-proven in the ledger,
but several independent shapes support a W3D display owner:

* `[this+0x2C]` is compared with the three exact callback addresses
  `0x0042F9F0`, `0x0043413F`, and `0x0040D779` at VA `0x00AF3FF9`.
  `W3DDisplay::drawCurrentDebugDisplay` has the same callback dispatch shape
  (`W3DDisplay.cpp:1585-1597`).
* VA `0x00AF4043` calls the object virtual slot `+0x74`, and the result is used
  as the first view. The matching retail thunk is `0x00442A05` to the
  `getFirstView` body at VA `0x0080F5D0`; it is not the supplied
  `0x0043FCD8` pointer.
* The body reads the client frame through the GameClient virtual slot `+0x68`,
  compares it with `[0x012BAA2C]`, and calls the camera/update helpers before
  the clock block. These are the fields and call shapes described by the
  current W3D display source.

This makes `W3DDisplay::draw` a good proposed name, but not a ledger-safe one:
the direct render work is delegated to another unnamed body, and no matched
caller names this exact 1,178-byte range.

### Direct order

The retail order is:

1. An early import/device predicate at `0x00AF3FCF-0x00AF3FE5` can return to
   `0x00AF4458`.
2. Two display helpers at `0x00406C6C` and `0x0044068D` run. The callback
   comparison at `0x00AF3FF9-0x00AF4025` optionally calls one of the three
   debug-display bodies.
3. The body samples `GameClient+0xC4` at `0x00AF402A`, obtains the first view,
   obtains the client frame, and either zeroes the frame delta while the
   advance flag is clear or stores the current frame in `[0x012BAA2C]`.
4. The camera/update helper at VA `0x00B44530` is reached through the thunk
   `0x0040E101`. This is still before the animation accumulator.
5. The clock branch runs at `0x00AF40A8-0x00AF413D`. The normal path adds
   `[0x012BB1CC]` to `[0x012F8064]` at `0x00AF40E8`, calls
   `WW3D::Sync` at VA `0x00CFD310`, and returns. The alternate path starts at
   `0x00AF4104`, performs its extra helper gates, adds
   `[0x012BB1CC] * (clientFrame - [0x012BAA2C])` at `0x00AF4132`, calls the same
   `Sync`, and falls through.
6. The remainder begins at RVA `0x006F4142` / VA `0x00AF4142`. It updates
   timing/statistics state, performs the remaining mode and render bookkeeping,
   and calls the separate render helper through thunk `0x0043E13F` at
   `0x00AF4334` (target body RVA `0x006EB500`, VA `0x00AEB500`, 1,215 bytes).
   Cleanup and the final optional callbacks end at `0x00AF445F`.

The bytes therefore do not support a `draw -> Sync` ordering for this body.
They show pre-draw work, then `Sync`, then the remainder and the delegated
render helper. The current source has the same meaningful order: its normal
`W3DDisplay::draw` path advances `syncTime` and calls `WW3D::Sync` before
`updateViews` and the main render block (`W3DDisplay.cpp:1839-1947`). The exact
split between the two retail bodies remains a boundary/name question, not a
reason to reverse the observed order.

### Every gate on the animation add

The accumulator add is not unconditional.

* A nonzero result from the initial import/device predicate exits the body.
* `GameClient+0xC4` is sampled and its negation is retained as a separate
  branch flag. A non-advancing client selects the alternate path.
* The call at `0x00422C96` and `GlobalData+0xC59` determine one alternate flag:
  only the false-result plus set-`+0xC59` combination sets it.
* The call at `0x0040A8A8` can set the same alternate flag.
* `GameLogic+0x11D` forces the alternate path.
* The current client frame is divided by 30 at `0x00AF40C4`; remainder zero
  forces the alternate path.
* In the alternate path, `GlobalData+0xBB9` only gates the optional helper at
  `0x004017FD`; it does not suppress the subsequent accumulator add.

The fast path is consequently the branch with the client advancing, neither
of the two predicate paths selecting the alternate mode, `GameLogic+0x11D`
clear, and `clientFrame % 30 != 0`. The alternate path is the only one that
uses the measured client-frame delta.

## 2. Display render order and the supplied `0x0043FCD8` pointer

### Address correction

The supplied value `0x0043FCD8` is a five-byte retail thunk. Its first jump is
to VA `0x0080F5E0`, whose body loads a `View *` argument and invokes that
view's `+0x23C` link method. It is `Display::getNextView(View *)`, not
`Display::draw`. The related thunks are:

* VA `0x004414C0` -> VA `0x0080DA30`, the 44-byte `Display::drawViews` loop;
* VA `0x0043DA82` -> VA `0x00AEA1C0`, the W3D display `updateViews` body.

`Display::drawViews` itself is exact in the retail/source pair: it loads
`m_viewList`, calls each `View` at vtable `+0x178`, then advances with
`+0x23C` (`Display.cpp:192-201`). The requested `Display::draw` identity at
`0x0043FCD8` is therefore OPEN and must not be entered in the ledger.

### Render call order

The separate render helper at RVA `0x006EB500` / VA `0x00AEB500` has the
following direct shape:

* VA `0x00AEB552` invokes the display virtual `+0x80` update path;
* VA `0x00AEB60C` calls `WW3D::Begin_Render` at VA `0x00CFE280`;
* the successful branch invokes display virtual `+0x7C` at
  `0x00AEB740`, which is `drawViews`;
* its normal cleanup calls `WW3D::End_Render` at VA `0x00CFD880` (the early
  branch does so at `0x00AEB66A`; the normal branch at `0x00AEB923`).

An independent, fully visible retail caller in the terrain-LOD timing loop
proves the exact sequence at VA `0x00AE8F2B`, `0x00AE8F66`, `0x00AE8F72`, and
`0x00AE8F7B`:

```text
updateViews -> WW3D::Begin_Render -> drawViews -> WW3D::End_Render
```

That loop is not the presentation frame; it can call `drawViews` repeatedly
while measuring terrain LOD. The main presentation source path has the same
order at `W3DDisplay.cpp:1885-1947` and `:2025`, with the following additional
work around it:

| Work | Position relative to main `drawViews` | Transform implication |
|---|---|---|
| `updateViews`, visibility region and camera work | before | Uses current logical/drawable state; not the delayed matrix |
| particle-manager update | before | Source comment at `W3DDisplay.cpp:1891-1898` says it is intentionally before the logical reset so linked particles can read client render-object transforms |
| water render-target textures | before | The affected object set and exact reflection consumer remain open |
| projected-shadow render-target textures | before | Prepass can read current transforms; exact affected-object route remains open |
| terrain tracks and shroud update | before `Sync` and before `drawViews` | These are separate terrain/track render objects; no unit-root read was proven here |
| normal model module draw | inside `drawViews` | `W3DModelDraw::doDrawModule` writes the adjusted current matrix later, overwriting a pre-hook blend |
| in-scene shadow/particle rendering | inside the scene render | Can see the blend only if its route runs after the hook; cache lifetime is Target 7 |
| selection, health-bar, caption, veterancy and construction icons | after model draw in `drawablePostDraw` | Helpers use logical `Drawable` positions (`W3DView.cpp:1029-1053,1799-1813`; `Drawable.cpp:5073-5123,5787-5920`), so they remain current rather than blended |

The current `unitinterp_begin` is placed before the complete `drawViews` body.
For ordinary models, that is before the final `W3DModelDraw` transform write,
not at the final consumer seam. Its restore also writes `record->current`, an
old sampled matrix, rather than a saved copy of the exact post-owner matrix.

## 3. W3DView update and model transform writers

### Update and drawable iteration

`W3DView::updateView` calls `update` (`W3DView.cpp:1123-1131`). After camera
and camera-lock work, the body computes an axis-aligned region and tests
`WW3D::Get_Frame_Time()` at `W3DView.cpp:1433-1440`. Only a nonzero frame time
reaches `TheGameClient->iterateDrawablesInRegion`.

The matched `GameClient::iterateDrawablesInRegion` body is RVA `0x0042E570`,
VA `0x0082E570`, 186 bytes. Its list head is `GameClient+0x10`; it follows
`Drawable+0x104` and calls the callback `drawDrawable`, which calls
`Drawable::draw(View *)` (`W3DView.cpp:741-748`). The relevant ABI offsets used
by the proposed feature are consistent with this path but are not individually
ledger-proven: draw modules at `Drawable+0x150`, module `getObjectInterface`
at vslot `+0x9C`, interface pointer at module `+0x0C`, and the model's
`RenderObjClass *` at interface `+0x28` (module `+0x34`).

`Drawable::draw` builds one local matrix from the current Drawable transform,
post-multiplies the instance matrix when non-identity, applies
`applyPhysicsXform`, and calls every module (`Drawable.cpp:4971-4987`). The
normal model path then reaches `W3DModelDraw::doDrawModule` and writes the
render-object transform after `unitinterp_begin` (`W3DModelDraw.cpp:2170-2241`).

### Set_Transform classification

The accessible source inventory classifies the relevant calls as follows.

| Site | Classification | Frequency / effect |
|---|---|---|
| `W3DModelDraw.cpp:2225-2231` | main `doDrawModule` writer | Every invocation of a visible model draw with a non-null render object; it copies the Drawable-composed matrix, applies model adjustment, and calls `Set_Transform` |
| `W3DModelDraw.cpp:711,741` | temporary identity and restore around a model/bone query | Exceptional query path, paired writes; not a per-frame placement writer |
| `W3DModelDraw.cpp:2757,2763` | another temporary identity and restore | Exceptional query path, paired writes; not the ordinary draw path |
| `W3DModelDraw.cpp:3305` | model recreation/state transition | Exceptional object/model setup path |
| `W3DModelDraw.cpp:5018-5021` | `reactToTransformChange` writer | Transform-change notification outside the view traversal; can write before the later draw-module call |
| `W3DDebrisDraw.cpp:267,286` and `W3DDebrisDrawDoDrawModule.cpp:258` | debris-owned render object | Own path, not the model interface selected by the feature; normal debris draw writes per call |
| `W3DDefaultDraw.cpp:90,105,166` | default/test asset paths | Conditional/test or fallback module paths, not proof of normal retail model coverage |
| `W3DTreeDraw` / `W3DPropDraw` | terrain-managed objects and no-op module draws | Their terrain object is not moved by a model-root `Set_Transform` |

The source tree contains roughly 70 `Set_Transform`-like sites when camera,
water, DX8 world matrices, lights, shadows, and all draw modules are included.
The table closes the normal model writer and the visible alternate families,
but not every retail callsite and derived module. The BFME
`W3DModelDraw::doDrawModule` body itself remains present-unmatched, so a
claim that all 70 sites push every frame would be false. Target 3 remains
PLAUSIBLE until that full call graph and every module interface are recovered.

## 4. Object-to-Drawable transform synchronization

### Primary logic path

`Thing::setPosition`, `setOrientation`, and `setTransformMatrix` update the
Object transform and cached position/angle, then invoke the appropriate
transform-change virtual when the position or orientation changed
(`Common/Thing/Thing.cpp:262-373`). The Object transform-change source path
then calls
`m_drawable->setTransformMatrix(this->getTransformMatrix())`
(`GameLogic/Object/Object.cpp:1992-2002`). This is the primary
Object-to-Drawable synchronization; it occurs during object/module logic
updates, chiefly the phase-1 object work, not inside `drawViews`.

The no-argument BFME Object helper at RVA `0x001BE700` / VA `0x005BE700`,
65 bytes, is a separate exact notification body. It refreshes shroud,
collision, partition, and contain state. It should not be conflated with the
longer old-matrix transform callback whose source body performs the Drawable
copy. The old-matrix callback's exact retail identity is not promoted from the
short existing row.

Phase 2 does not copy the Object matrix into the Drawable. At
`GameLogic::update` VA `0x0078DE89-0x0078DECF`, it updates PartitionManager and
CollisionManager, then walks Objects and calls the exact
`Drawable::bfmeRecordTransform` body at RVA `0x001C0BE0` only when
`Object+0x168 != GameLogic+0x3C`. That 217-byte body copies the prior/current
Drawable transform-history fields and records the phase frame. The large
phase-1 callback at RVA `0x0041B200` is still an unnamed generated body; its
identity and complete transform-side effects remain open.

### Render composition and physics

The Drawable's persistent transform is not the final matrix sent to a model:

```text
Object transform -> Drawable transform
                    -> instance matrix (if non-identity)
                    -> applyPhysicsXform
                    -> each DrawModule::doDrawModule
                    -> model RenderObjClass::Set_Transform
```

`Drawable::applyPhysicsXform` is an in-place adjustment of the local matrix
passed to draw modules, not a rewrite of the base Drawable matrix. It checks
the Object physics state, global/tactical/script/client freeze conditions,
then applies total Z translation and Y/X/Z rotations for pitch, roll, and yaw
(`Drawable.cpp:1540+`). The separate `Drawable::setInstanceMatrix` state is
an additional visual matrix; a BFME history helper records prior instance data
and frame expiry, but the complete instance lifecycle is not closed here.

### Other writers and exceptions

Locomotor, PhysicsBehavior, topple/death, projectile, helicopter, contain,
rider, and formation code can call Object transform setters. Those calls use
the same Object-to-Drawable callback when the Object is the owner. Physics and
topple paths can also write an Object matrix directly before the callback.
`Drawable::reactToTransformChange` broadcasts to modules, and
`W3DModelDraw::reactToTransformChange` can write its render object directly;
these are additional writers outside the normal view loop.

The source contains explicit contained/rider activity, including a scatter
path that calls `bfmeRecordTransform(frame)` around a rider position change
(`OpenContainScatterToNearbyPosition.cpp:127-130`). Horses/riders, mounted
heroes, garrisoned models, formation offsets, attached effects, and all
factory-created draw-module variants were not exhaustively enumerated. The
correct static conclusion is therefore that the base Object-to-Drawable path
is understood, while “every visible unit has one synchronized root history”
is not proven.

## 5. Phase re-entry under the pacing cave

### Engine control flow

The exact retail `GameEngine::update` body is RVA `0x0006E910`, VA
`0x0046E910`, 392 bytes. The cave's denied phase-2..6 branch rewinds
`GameEngine+0x30` to `phase-1`, restores registers, and falls through to the
original `_bfme_updateNetworkAndLogic`. It therefore does not deny the call:
the denied phase executes now, and the next engine iteration retries the same
phase number without a phase-1 frame increment.

The retail `GameLogic::update(int phase)` body is RVA `0x0038DA10`, VA
`0x0078DA10`, 2,129 bytes. Its phase blocks are fixed by the direct jump and
call shapes at `0x0038DE89-0x0038E17F`:

| Re-run phase | First invocation | Immediate retry with the same logic frame |
|---:|---|---|
| 2 | PartitionManager update, CollisionManager update, then conditional transform-history recording | PartitionManager and CollisionManager run again unconditionally. The Object `+0x168 == current frame` test normally prevents a second `bfmeRecordTransform` for the same Object/frame. |
| 3 | First half of sleepy vector 0 | Due entries are tested by `wakeFrame <= currentFrame`; after callback return the wake is clamped to at least `currentFrame+1`, so ordinary entries do not fire again on the retry. |
| 4 | Second half of sleepy vector 0 | Same wake-frame result for that half. An external wake-now or callback mutation can change this, but it is not the ordinary path. |
| 5 | Sleepy vectors 1 and 2, then AI and the phase-5 post batch | Sleepy entries normally do not re-fire immediately, but the AI/post-simulation calls and destruction/shroud/object-creation/victory tail are reached again because those calls are not protected by the sleepy wake comparison. |
| 6 | Sleepy vector 3 | Same ordinary one-fire-per-frame wake behavior as phases 3 and 4. |

The sleepy loop at `0x0038DF79-0x0038DF92` calls an entry's update virtual
slot 0, interprets its return as a sleep, and stores the next wake frame at
`0x0038DFFB`. This is a per-call scheduler decision, not a hidden “already
ran in this engine iteration” bit.

The exact CollisionManager wrapper at RVA `0x009A2560` forwards to owned data
at RVA `0x009A4A30`. The 41-byte owned body sets its busy byte at
`+0xC06D`, calls three collision-processing helpers, and clears the byte. No
current-frame guard exists in that body, so the phase-2 retry double-processes
the collision pass.

### Movement clock and locomotion

`AIUpdateInterface::update` calls `doLocomotor` after the state machine and
turret work (`GameLogic/Object/Update/AIUpdate.cpp:2141+`). `doLocomotor` calls
`Locomotor::locoUpdate_moveTowardsPosition` for explicit/path movement and
returns `UPDATE_SLEEP_NONE` while movement or other constant calling is
required (`AIUpdate.cpp:3325+`). The BFME locomotor body at RVA `0x002BAFB8`
is still a generated ASM dump; its exact internal integration and identity
cannot safely be inferred from the dump alone.

`PhysicsBehavior::update` is clearer. It integrates acceleration into velocity,
translates the Object matrix, calls `obj->setTransformMatrix`, and returns
`calcSleepTime` (`PhysicsUpdate.cpp:656-953`). Motive expiry is compared with
`TheGameLogic->getFrame()` and uses `MOTIVE_FRAMES = LOGICFRAMES_PER_SECOND/3`
(`PhysicsUpdate.cpp:72,438-443`); it does not use `WW3D::Get_Frame_Time` or
`0x012BB1CC`.

Thus movement integration is per update-module invocation, using the fixed
logic-frame/model units. The ordinary sleepy scheduler prevents a moving
entry that just returned sleep-none from being called again in the same frame,
but the cave's phase retry still repeats unconditional phase work and can
repeat any leaf that is explicitly woken. The admitted phase sequence is not a
clean set of 30 Hz movement samples. A render interpolation layer must not use
the cave's phase retry as proof that each sample represents one complete,
once-only simulation step.

## 6. GameEngine client-frame ratio and rope reference

### Producer semantics

At RVA `0x0006E981-0x0006E9DD`, `GameEngine::update` reads:

* `+0x30`: current client phase/period;
* `+0x34`: client-frame counter/denominator;
* `+0x38`: clipped client-frame ratio;
* `+0x3C`: deferred ratio/counter reset flag.

The helper in `Common/GameEngineUpdate.cpp:154-164` and the matching retail
instructions compute `period / counter`, then clip the result to `[0,1]`.
This is not a generic elapsed-wall-clock value.

The `period == 6 && ratioPending` special case at `0x0046E981-0x0046E993`
copies period 6 into `+0x34` and clears `+0x3C` before computing `newPeriod =
period+1`. The new period is stored in `+0x30`, and the ratio is calculated
from that new period. When the new period exceeds 6, the body saves the period,
sets `+0x30` to 1 for the phase-1 call, recomputes the ratio, and calls
`_bfme_updateNetworkAndLogic(1)`. If `GameClient+0xC4` says the logical frame
advanced, it leaves the phase-1 state and sets `+0x3C`; otherwise it restores
the saved period and recomputes the ratio. This explains why the pending bit is
deferred across the phase-1 boundary.

### Readers and rope behavior

The focused source readers of `GameEngine+0x38` are:

* `W3DStatusCircleRenderBFME.cpp:303-312`, blending previous/current status
  intensity;
* `W3DModelDrawHandleClientTurretPositioningRva0075F400.cpp:107,129-143`,
  blending client turret angle/pitch;
* `Common/BfmeCalc919G.cpp:73-81,173-186`, using `Matrix3D::Lerp` for the
  cached matrix and Hermite interpolation for position;
* `Common/BFMERopeDrawableInterpolatedPosition.cpp:18-26,59-83`, using two
  stored position/tangent samples and Hermite alpha;
* `Common/BFMERopeDrawableLinearInterpolatedPosition.cpp:13-19,42-64`,
  using `position0 * (1-alpha) + position1 * alpha`.

Representative raw load addresses from the focused retail scan are below;
the complete containing-body inventory follows. Names not backed by a matched
caller are intentionally left unresolved:

| Load RVA | Containing evidence | Disposition |
|---|---|---|
| `0x00411B57` | `bfmeGetETE`, body RVA `0x00411B20`, 113 bytes | ratio/interpolation helper; exact semantic name open |
| `0x0029BD36` | body RVA `0x0029BD20`, 36 bytes, `bfmeGoUKD` row | ratio multiplied into an object value; exact consumer open |
| `0x0041CFB4`, `0x0041D0C0`, `0x0041D17A` | adjacent rope family | consistent with Hermite/linear rope getters |
| `0x007265F0`, `0x0075F45C`, `0x00762CE4`, `0x0076BF9E` | model/animation family | direct reference found, owner and meaning open |

### Complete direct reader inventory

The focused absolute-reference scan found the following nine function bodies
that load the GameEngine singleton at `0x012ED524` and then read or multiply
`GameEngine+0x38`. This is exhaustive for direct absolute loads in the
scanned `reverse/ghidra_functions.csv` envelopes. An indirect reader or a
body that receives a copied ratio would require a separate data-flow pass.

| Reader body | RVA / VA | Size | Reader operation and relevant callers | Status |
|---|---:|---:|---|---|
| `BfmeThingUKD::bfmeGoUKD` | `0x0029BD20` / `0x0069BD20` | 36 B | After checking `GameEngine+0x30 == 1`, loads `+0x38`, multiplies by `this+0x18`, adds `this+0x44`, and converts to integer. No named direct caller in the ledger. | reader PROVEN; higher-level meaning PLAUSIBLE |
| `BfmeHostETE::bfmeGetETE` | `0x00411B20` / `0x00811B20` | 113 B | Loads `+0x38` and passes it with `this+0x168`, `this+0x198`, and output `this+0x1C8` to VA `0x00CD8480`. No named direct caller. | reader PROVEN; helper meaning PLAUSIBLE |
| `BfmeCalc919G::bfmeCalc919G` | `0x0041CEC0` / `0x0081CEC0` | 364 B | Uses `+0x38` for a matrix lerp at VA `0x00CD8480`, then position/tangent Hermite interpolation at VA `0x00DFA11F`. | PROVEN |
| `BFMERopeDrawable::get` | `0x0041D090` / `0x0081D090` | 147 B | Uses `+0x38` as Hermite alpha over two stored rope position/tangent samples and writes the result to `+0x230`. | PROVEN |
| `BFMERopeDrawable::getPositionLinear` | `0x0041D150` / `0x0081D150` | 164 B | Uses the same ratio for component-wise `(1-alpha)*p0 + alpha*p1` interpolation. | PROVEN |
| `W3DStatusCircle::Render` | `0x00726290` / `0x00B26290` | 2,243 B | Reads `+0x38` on the render path and blends previous/current status intensity. | PROVEN reader; virtual caller route open |
| anonymous turret-positioning body | `0x0075F400` / `0x00B5F400` | 823 B | Reads the ratio to blend previous/current turret angle with wrap-around and AI turret state. | reader PROVEN; clean identity PLAUSIBLE |
| anonymous body `0x007629F0` | `0x007629F0` / `0x00B629F0` | 834 B | Performs a direct ratio multiply alongside object/geometry rotation and trigonometric work. | reader PROVEN; role OPEN |
| anonymous body `0x0076BF20` | `0x0076BF20` / `0x00B6BF20` | 278 B | Reads the ratio after a period-one special path and blends/clamps a state value. | reader PROVEN; role OPEN |

The named `BfmeCalc919G` reader has these direct callers:

| Caller RVA / VA | Caller |
|---:|---|
| `0x001E8970` / `0x005E8970` | `Weapon::preFireWeapon` |
| `0x002A9850` / `0x006A9850` | `WeaponSetSpecialAbilityUpdate` destructor |
| `0x006FC0D0` / `0x00AFC0D0` | `W3DInGameUI::drawPlaceAngle` |
| `0x00731D60` / `0x00B31D60` | `W3DTerrainVisual::addFactionBibDrawable` |
| `0x00750870` / `0x00B50870` | `BfmeThing919G::bfmeGo919G` |
| `0x007508A0` / `0x00B508A0` | `W3DDebrisDraw::doDrawModule` |
| `0x00751320` / `0x00B51320` | `BfmeThing919H::bfmeGo919H` |
| `0x0075C050` / `0x00B5C050` | `W3DModelDraw::nukeCurrentRender` |

Its exact shape is:

```text
Matrix3D::Lerp(matrix0 + 0x31C, matrix1 + 0x34C, alpha, cached + 0x200)
bfmeVec3Hermite(cached position,
                position0 + 0x37C, tangent0 + 0x388,
                position1 + 0x394, tangent1 + 0x3A0,
                alpha)
cached translation = Hermite result
```

The bytes and named callers establish that this is a real client-frame
interpolation consumer, not a generic render delta.

The rope code is the clearest engine reference: it blends two cached samples,
with either Hermite position/tangent interpolation or direct linear position
interpolation, using the engine ratio as alpha. The source names the samples
`m_position0` and `m_position1`; their temporal “older/current” interpretation
is not assumed here.

The ratio producer and all nine direct absolute reader bodies are proven as
separate mechanisms. Indirect/copy-propagated readers and clean identities
for the anonymous bodies remain open, so this target is PLAUSIBLE rather than
a new ledger claim.

## 7. `RenderObjClass::Set_Transform` side effects

### Exact base behavior

The 125-byte retail body at RVA `0x009201A0`, VA `0x00D201A0`, copies all 12
matrix words from the argument into `RenderObjClass+0x18..0x44`. It then:

1. calls the identity check at VA `0x00D1FF40` and stores the resulting flag at
   `+0x7C`;
2. clears bit `0x20000` in the flags at `+0x10`, invalidating cached bounding
   volumes;
3. reads the scene at `+0x80`; when the object is top-level (no container at
   `+0x84`), calls scene virtual slot `+0x38` with registration type 3.

`rendobj.h` identifies bit `0x20000` as `BOUNDING_VOLUMES_VALID`. The later
bounding getters lazily transform the object-space sphere/box and set the
valid bit again (`rendobj.cpp:1027-1040`). The setter therefore invalidates
the bounds; it does not compute them synchronously.

The BFME `SimpleSceneClass::Register` carrier maps type 3 to the render-list
registration path (`SimpleSceneClass_Register_Thunk.cpp`). This is a scene
notification/list operation, not proof of an immediate spatial-cell or
visibility recomputation. Culling consumes the invalidated bounds later.

### Derived objects and cached consumers

The base setter does not recursively walk HLOD children. The derived source
shapes are:

* `Animatable3DObjClass::Set_Transform` calls the base and marks the hierarchy
  invalid (`animobj.cpp:372-376`);
* `HLodClass::Set_Transform` then marks sub-object transforms dirty
  (`hlod.cpp:2278-2281`), allowing later validation to propagate to children.

The surveyed base setter has no direct shadow-caster or light-environment cache
update. The scene renderer builds light environment data at render time. There
are, however, downstream transform-derived histories:

* volumetric shadow mesh update stores `objectToWorld` in
  `m_objectXformHistory[light][mesh]` after rebuilding a volume
  (`W3DVolumetricShadow.cpp:3222-3478`);
* projected shadow bounds read `Get_Position`/`Get_Bounding_Box` and store an
  area-effect box (`W3DShadowTexture::updateBounds`).

If either route runs while the temporary blended transform is installed, its
derived history can survive the later restore. The actual route from the main
presentation pass to each cache is not fully closed, so persistence is a
proven consequence of such reachability, not a claim that every frame hits it.

Two calls per moving model cost at least two 48-byte matrix copies, two
identity scans, two bounding-valid-bit clears, and two scene registration
attempts. HLOD dirty propagation, lazy bound recomputation, and shadow-volume
rebuilds can add work proportional to child count. No cycle or millisecond
estimate is claimed statically. Base invalidation is PROVEN; complete derived
cache behavior is not, so the target remains PLAUSIBLE.

## 8. `WW3D` frame time, SyncTime, and the animation-step field

### Clock definitions

The exact 21-byte `WW3D::Sync` body at RVA `0x008FD310`, VA `0x00CFD310`, is:

```text
PreviousSyncTime = SyncTime;
SyncTime = argument;
```

`WW3D::Get_Frame_Time` at RVA `0x007239A0`, VA `0x00B239A0`, returns
`SyncTime - PreviousSyncTime`. `W3DView::update` uses a nonzero result as the
drawable-iteration gate.

There are two relevant retail/source chains. The anonymous body in Target 1
directly adds `[0x012BB1CC]` (or that value times a client-frame delta) to an
accumulator and passes the result to `WW3D::Sync`. The readable current
`W3DDisplay.cpp` path instead advances a local `syncTime` by
`TheW3DFrameLengthInMsec` (33 ms) and calls `WW3D::Sync(syncTime)`
(`W3DDisplay.cpp:1803-1809,1839-1847`). The bridge proving whether those are
the same retail method/path, including fast/frozen and terrain-LOD calls, is
not closed.

### Consumer inventory

| Consumer | Clock read | Static consequence of a correct 17 ms `Sync` delta |
|---|---|---|
| `W3DView::update` | `Get_Frame_Time()` | Zero delta skips drawable iteration; cadence and visibility are coupled to Sync |
| `Animatable3DObjClass` | `SyncTime - LastSyncTime` (`animobj.cpp:1007-1017,1120-1125`) | Animation frame advances by elapsed Sync time; no fixed 33 ms was found in the formula |
| particle emitters/buffers | `Get_Frame_Time` and `Get_Sync_Time` (`part_emt.cpp:591-649`; `part_buf.cpp:2044-2063,2396+`) | Emission, age, kinematics, and visual state are time-based, but update cadence and transform placement remain separate seams |
| snow | `Get_Frame_Time` (`W3DSnow.cpp:179`; `W3DSnowManagerUpdate.cpp:131`) | Phase advances by the Sync delta |
| rings, spheres, projected textures | `Get_Frame_Time` (`ringobj.cpp:1188-1237`; `sphereobj.cpp:1143-1190`; `texproject.cpp:1349-1359`) | Formulas are elapsed-time based; exact retail call cadence for the present-unmatched bodies is open |
| terrain tracks | Sync timestamps and fade (`W3DTerrainTracks.cpp:302,421,768+`) | Fade uses `SyncTime - timeAdded`; an incorrectly halved delta changes wall-time fade |
| terrain shader | Sync timestamp/delta | Cloud drift is elapsed-time based |
| texture mappers and texture lifetime | `LastUsedSyncTime`, `LastAccessed` | UV temporal state and resource aging use SyncTime; not all are visible geometry motion |
| shader manager | current Sync tick | Time-based shader bookkeeping follows SyncTime |
| camera duration/easing | direct `[0x012BB1CC]` reads in camera update/rotate/pitch/zoom/reset bodies | Changing 33 to about 17 changes duration-to-frame conversion and can double frame counts for a millisecond duration |
| waypoint camera movement | `TheW3DFrameLengthInMsec` in the readable update path | Separate-clock exception; changing `[0x012BB1CC]` does not retime this path automatically |
| water tracks | `timeGetTime()` and wall-clock difference (`W3DWaterTracks.cpp:898-949`) | Separate wall-clock exception; not a SyncTime consumer |

The direct camera field readers include the recovered bodies around RVAs
`0x0073BDD0`, `0x0073BEA0`, `0x0073BF80`, `0x0073C440`, `0x00743640`,
`0x0073FC40`, `0x0073FCF0`, `0x0073FDD0`, `0x0073FE80`, and
`0x00744530`. The feature can therefore affect camera timing even if the
anonymous display-to-Sync identity is wrong.

The formulas for animation, particles, snow, tracks, shaders, and mappers are
compatible with a monotonic real-elapsed Sync clock. That is only a
conditional result. The proposed field steering is not globally certified
safe until the anonymous Target-1 caller, the local display `syncTime`, render
target call cadence, and the separate camera/waypoint/water clocks are tied
together.

## OPEN items

1. The exact class/method identity of the 1,178-byte `0x006F3FC0` body and the
   exact identity/signature of its render helper at `0x006EB500`.
2. The supplied `Display::draw` pointer is disproven as labelled, but the true
   BFME `Display::draw` vtable entry and a matched caller naming it are not
   recovered in this pass.
3. A complete retail call graph for every W3D draw module and every roughly 70
   `RenderObjClass::Set_Transform` site, including all tree, prop, rope, laser,
   debris, attachment, and terrain variants.
4. The exact retail identity of the phase-1 Drawable callback at `0x0041B200`
   and the complete Object transform callback that writes the Drawable matrix.
5. Exhaustive mounted, rider, contained, garrisoned, formation, death/topple,
   and attached-effect transform-writer coverage.
6. The exact locomotor integration body/clock behind
   `locoUpdate_moveTowardsPosition`; its source representation is still a
   generated ASM dump.
7. An exhaustive list and identity proof for every `GameEngine+0x38` reader,
   plus the final semantics of the unresolved model/animation absolute loads.
8. Whether all main-scene, water-reflection, projected-shadow, and
   terrain-LOD render passes see the temporary blend or the current transform.
9. Whether a blended matrix reaches and persists in every shadow/HLOD/light or
   particle cache before `unitinterp_restore` writes the historical matrix.
10. The bridge between `[0x012BB1CC]`, the anonymous retail Sync caller, and
    the readable 33 ms `W3DDisplay` source path; without it, 60 Hz clock safety
    remains conditional rather than proven.
