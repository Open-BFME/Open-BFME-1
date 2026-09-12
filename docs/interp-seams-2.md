# Interpolation seams - worker 2

Static audit of the untouched retail `D:\BFME1\lotrbfme.exe` (image base
`0x400000`). No game process was launched, the executable was not patched, and
no build or commit was run. This note is limited to the worker-2 W3D view,
draw-module, and Object-to-Drawable transform seams.

Ledger and disassembly addresses below are RVAs unless marked `VA`.
`VA = RVA + 0x400000`. A `PROVEN` result closes the stated retail control/data
flow. `PLAUSIBLE` means the retail shape and source agree but a name, vtable
slot, or complete call cone is still open. `OPEN` means the requested claim
was not established. A `matched` or generated row is not by itself identity
proof.

## Bottom line

The normal unit transform path is:

```text
Object transform
  -> Object::reactToTransformChange
  -> bound Drawable transform
  -> Drawable instance matrix (when non-identity)
  -> Drawable::applyPhysicsXform
  -> each Drawable draw module
  -> W3DModelDraw::doDrawModule
  -> RenderObjClass::Set_Transform
```

The final ordinary model write is now statically closed. Retail
`W3DModelDraw::doDrawModule` is the body at RVA `0x0077B3F0`, size 1,209, and
its root transform submission is at RVA `0x0077B680` (VA `0x00B7B680`). It
loads the render object from `module+0x34`, adjusts the composed matrix, and
calls render-object vtable `+0x54` (slot 21). That is a per-draw write, subject
to the module's render-object and state gates, not an only-on-change write.

The object-side publication is also closed as a dataflow: the retail
`Object::reactToTransformChange` body reads `Object+0x80` as the Drawable,
passes `Object+0x08` as the matrix, and reaches the transform-copy body at
RVA `0x00132200` through ILT `0x000361CE`. The existing ledger has a second,
distinct transform-copy body at RVA `0x00132350` behind ILT `0x00023D49`; the
two bodies must not be merged because they use different transform-change
callback ABIs.

The W3DView/update callback chain is structurally strong but not completely
name-safe. The retail body at RVA `0x007446A0`, size 2,618, has the W3DView
update shape and ends in a drawable-list walk, but it is still a generated
`d_007446a0` row. Its live W3DGameClient dispatch is vslot `+0x54` (slot 21),
whose body is RVA `0x00431A60`; that is a second list/status/region iterator,
not the exact matched slot-20 walker at RVA `0x0042E570`. The callback literal
in the update-looking body is RVA `0x0073AD50`, whose short body does not
match the source `drawDrawable` shape. Also, the exact `Display::drawViews`
loop calls View vtable `+0x178`, while the currently decoded W3DView owner
table routes that slot through the update-looking body. Those are
identity/layout debts, not permission to claim a clean `drawViews -> drawView`
mapping.

## 1. W3DView and drawable-list traversal

### Retail view owner and update-looking route

The constructor body at RVA `0x00745B10` installs the following constants:

| Object part | Retail value | Evidence | Status |
|---|---:|---|---|
| primary vtable | VA `0x011217A0` | constructor store at `this+0x00`; destructor restores the same family | PROVEN owner table |
| secondary/base vtable | VA `0x01121790` at `this+0xB4` | constructor and destructor stores | PROVEN layout |
| SubsystemInterface subobject | VA `0x01121764` at `this+0xFC` | constructor store at `this+0xFC` | PROVEN layout |

The primary-table entry at `0x011217A0+0x178` is VA `0x004216AC` (an ILT/thunk
cell). Its target is the 15-byte `forward@Rva0073AF80VCall` body at RVA
`0x0073AF80`. That forwarder adds the secondary-base offset (`this+0xFC`)
and redispatches through secondary vtable `+0x14` (slot 5). The secondary
entry is VA `0x00407F31`, which jumps to VA `0x00B446A0` (RVA `0x007446A0`).

The body at RVA `0x007446A0` is a generated 2,618-byte range, but its retail
shape is specific enough to call it the W3DView update candidate:

* after camera and view-region work it reads `WW3D::SyncTime` at VA
  `0x0133F420` and subtracts the previous value at VA `0x0133F424`;
* a zero delta branches around the drawable walk;
* the nonzero path updates the camera frustum and calls the `TheGameClient`
  virtual at `+0x54` with a computed region pointer and callback pointer;
* the callsite passes callback literal VA `0x00B3AD50` and uses a pointer
  formed with `+0x104`.

`WW3D::Get_Frame_Time` itself is the exact 11-byte body at RVA `0x007239A0`
(VA `0x00B239A0`); it returns the same SyncTime-minus-previous value. The
retail update body inlines the two global loads, so the gate behavior is
`PROVEN`, while a direct call edge to `Get_Frame_Time` is not required.

The frame-time gate is specifically the inline sequence at RVA `0x00745074`
(VA `0x00B45074`): load `[0x0133F420]`, subtract `[0x0133F424]`, and branch
around the list callback when the delta is zero. On the nonzero path the body
loads `TheGameClient`, passes a computed float/region value, a Drawable-list
pointer formed with `+0x104`, and callback RVA `0x0073AD50` to vslot `+0x54`.
That exact callsite is a proven dispatch to the live W3DGameClient table, but
the callback's source-level meaning is still open.

The source names this route `W3DView::updateView -> UPDATE() -> update()`
(`W3DView.cpp:1123-1440`). The body identity remains `PLAUSIBLE` rather than
ledger-safe because its current row is generated and the callback/table
conflict below is unresolved.

### Exact drawable-region walker

`GameClient::iterateDrawablesInRegion` is an exact matched body at RVA
`0x0042E570`, size 186. Its retail dataflow is:

```text
TheGameClient + 0x10       -> Drawable list head
Drawable       + 0x104     -> next Drawable
Drawable::getPosition      -> region tests
callback(drawable, userData)-> indirect call for each accepted Drawable
```

The list and `+0x104` link are `PROVEN` by the body and by
`Code/GameEngine/Source/GameClient/GameClient_iterateDrawablesInRegion.cpp`.
The callback ABI is also visible: the exact slot-20 walker pushes the user
data and Drawable arguments before the indirect call. The W3DView source
callback is:

```cpp
static void drawDrawable(Drawable *draw, void *userData)
{
    draw->draw((View *)userData);
}
```

That source-level edge makes `Drawable::draw` the intended consumer for the
ordinary update path, but the retail callback literal is not closed. RVA
`0x0073AD50` disassembles as a 20-byte helper which forwards two stack
arguments to a BitFlags helper and returns; there is no ledger row naming it
`drawDrawable`, and it does not look like the source callback. The callback
edge is therefore `PLAUSIBLE`, not `PROVEN`. The exact BFME body at the
`+0x54` dispatch (RVA `0x00431A60`) must also be distinguished from the
matched generic region walker at `0x0042E570`.

The previously suggested RVA `0x0041B200` is not this callback. It is the
generated `?d_0041b200` body, size 1,368, which copies a large state block and
sets fields near `+0x3B4`/`+0x23C`. Its callback identity is not established.

### Display traversal and the vtable-name conflict

The exact matched body `Display::drawViews` at RVA `0x0040DA30`, size 44,
loads the View list at `Display+0x18`, calls each View at vtable `+0x178`,
then advances through vtable `+0x23C`. That agrees with
`Code/GameEngine/Source/GameClient/Display.cpp:195-201` at the byte level.

There is also an unnamed retail body at RVA `0x0040D9E0`, size 63 (return at
`0x0040DA1E`). It performs the Display state gates, walks `Display+0x18`,
calls each View at vtable `+0x174`, and advances through `+0x23C`. This is
the static body corresponding to the `Display::updateViews` loop in the
source, but it has no accepted ledger identity. It is important evidence for
the call order even though it does not by itself resolve the W3DView table
slot/name contradiction.

There is, however, a current retail-table contradiction:

* the source/shim label for `+0x178` is `View::drawView`;
* the W3DView owner table at VA `0x011217A0+0x178` reaches the secondary
  SubsystemInterface slot 5 and the update-looking body at RVA `0x007446A0`;
* the nearby unnamed body at RVA `0x0040D9E0` is the `+0x174` traversal
  shape expected for `Display::updateViews`, but it has no accepted ledger
  identity and therefore cannot by itself repair the naming by elimination;

The secondary W3DView table also contains a strong draw-body candidate: its
slot 7 reaches generated body RVA `0x0073E050`, whose long scene/UI shape and
tail callbacks are consistent with `W3DView::draw`. The extra BFME
SubsystemInterface slots and the current owner-table labels are not fully
reconciled. The safe static name for the first call is therefore “View
traversal slot `+0x178`”, not an accepted retail `drawView` or `updateView`
name until the vtable order is corrected.

The source render order is still clear: `W3DDisplay::draw` calls
`updateViews()` before the main `drawViews()` block
(`W3DDisplay.cpp:1885-1944`), and the W3DView update source performs the
drawable-region callback before the scene render. The exact callback address
and the table-name contradiction are the remaining static qualifications.

## 2. Drawable/module/render-object ABI

The offsets used by the Astra notes and `unitinterp` can be separated into
proven offsets and a common-base-relative offset:

| Object | Offset | Meaning | Evidence | Status |
|---|---:|---|---|---|
| `GameClient` | `+0x10` | global Drawable list head | exact region walker | PROVEN |
| `Drawable` | `+0x104` | next Drawable | exact region walker and source shim | PROVEN |
| `Drawable` | `+0x150` | draw-module pointer array | BFME layout in `Drawable.cpp` and source `getDrawModules` use | PROVEN static layout |
| draw module | `+0x9C` | `getObjectDrawInterface`/object-interface getter vslot | BFME draw-module skeleton and W3DModelDraw primary table slot 39 | PROVEN |
| W3DModelDraw | `+0x0C` | secondary `ObjectDrawInterface` subobject | ctor writes secondary vtable `0x01123C68`; getter returns `this+0x0C` | PROVEN |
| ObjectDrawInterface subobject | `+0x28` | W3DModelDraw render-object pointer | equivalent to W3DModelDraw/module `+0x34` | PROVEN |
| RenderObjClass | vtable `+0x54` | `Set_Transform`, slot 21 | RenderObjClass declaration and retail callsites | PROVEN |
| RenderObjClass | `+0x18` | stored 12-float transform | `Set_Transform` body and `fps60.md` | PROVEN |

The W3DModelDraw constructor at RVA `0x00773360` writes primary vtable VA
`0x01123D38` and secondary ObjectDrawInterface vtable VA `0x01123C68` at
`this+0x0C`. The destructor at RVA `0x0077B090`, size 682, restores the same
vtable family. The primary W3DModelDraw table entry at slot 9 (`+0x24`) is
an ILT at RVA `0x00038E15` which reaches body RVA `0x0077B3F0`.

The W3DModelDraw primary table entry at slot 39 (`+0x9C`) is an ILT at RVA
`0x0000D7EC` which reaches a getter body at RVA `0x00751D90`. That body
returns `this+0x0C` when `this` is non-null. This is the direct retail proof
for the interface pointer used by the unit-interpolation code.

The generated row and current `reverse/symbols.csv` pins around RVA
`0x0075BE60` (`isLaser`) and `0x0075BF30` (`getObjectDrawInterface`) have
suspicious argument/return shapes and do not match this getter. They are not
used as evidence here. The vptr stores, table slot, getter bytes, and
W3DModelDraw body dataflow take precedence over those stale names.

### Final model write

The retail body at RVA `0x0077B3F0` has the following decisive sequence near
its end:

```text
load [this+0x34]                    ; RenderObjClass*
copy Drawable/model transform to a local Matrix3D
call adjustment helper               ; model attachment/construction adjustment
load render-object vtable
call [renderObject vtable + 0x54]   ; Set_Transform(local Matrix3D)
```

The call instruction is RVA `0x0077B680` (VA `0x00B7B680`). Since
`this+0x0C` is the ObjectDrawInterface subobject, the same field is
`interface+0x28`. This corrects the potentially misleading shorthand
“render object at module `+0x28`”: `+0x28` is relative to the secondary
interface pointer; the module-relative address is `+0x34`.

`RenderObjClass::Set_Transform` is the exact body at RVA `0x009201A0`, size
125, and stores the supplied Matrix3D in the render object transform at
`+0x18`. The final render-object submission is consequently a real consumer
seam, unlike a write to Drawable position or to the Drawable list link.

## 3. Set_Transform cadence inventory

This is the static classification of the draw-module and adjacent render
object writers found in the source/retail evidence. “Every draw” means every
eligible invocation of the owning module; it does not remove null-render,
hidden, animation, scale, or other upstream conditions.

| Retail site or source site | Owner/path | Cadence and meaning | Status |
|---|---|---|---|
| RVA `0x0077B680` | `W3DModelDraw::doDrawModule`, body `0x0077B3F0` | Every eligible ordinary model draw. Writes the adjusted Drawable-composed Matrix3D to `module+0x34` render object through vslot `+0x54`. | PROVEN |
| RVA `0x0075099F` | `W3DDebrisDraw::doDrawModule`, body `0x007508A0`, size 478 | Every eligible debris draw when a render object exists and the instance-scale branch does not replace the matrix write with `Set_ObjectScale`. | PROVEN; matched row |
| RVA `0x00750DD5` | `W3DDebrisDraw::setModelName`, body `0x00750CC0`, size 474 | Model creation/replacement. The initial transform is an initialization write, not a frame writer. | PROVEN; matched row |
| RVA `0x007515DB` | W3DDefault constructor candidate, body `0x007513C0` | Constructor/model initialization write. It is not evidence of per-frame submission. | PLAUSIBLE; generated identity |
| `W3DDefaultDraw.cpp:166` | `W3DDefaultDraw::doDrawModule` | Source path writes every eligible draw when its render object exists and `instanceScale == 1`; exact BFME retail body/callsite is not closed. | OPEN |
| `W3DDefaultDraw.cpp:105` | `W3DDefaultDraw::reactToTransformChange` | Only when the Drawable transform-change notification runs; not a guaranteed every-frame write. | OPEN retail identity |
| `W3DDebrisDraw.cpp:267` | `W3DDebrisDraw::reactToTransformChange` | Only on transform-change notification; separate from the exact per-draw debris body. | OPEN retail identity |
| `W3DModelDraw.cpp:5020` | `W3DModelDraw::reactToTransformChange` | Only on transform-change notification. It copies the Drawable transform, applies model adjustment, and writes the render object before the next draw-module call. | OPEN retail identity |
| `W3DModelDraw.cpp:3305` | `W3DModelDraw::setModelState` | Render-object recreation/model-condition transition. The write belongs to replacement/setup, not a normal frame. | OPEN retail identity |
| `W3DModelDraw.cpp:711,741` | `nukeCurrentRender` | Paired temporary identity and restore around a query or teardown path. It is not a persistent interpolated root. The owning body `nukeCurrentRender` at `0x0075C050`, size 290, is matched. | PROVEN local body; call context open |
| `W3DModelDraw.cpp:2757,2763` | particle/bone recalculation | Paired temporary identity and restore while reading/updating attached particle/bone state. It can occur during drawing, but it is not the authoritative final root write. | PLAUSIBLE source path |
| `W3DRopeDraw` body `0x0075AD20` | rope draw module | Exact matched body updates `Line3DClass` geometry and does not show a render-object vslot `+0x54` transform submission. | PROVEN negative result |
| `W3DPropDraw` body `0x00759560` | terrain prop module | Exact matched transform-change body adds/updates the terrain prop path; it does not establish a model-root `Set_Transform` call. | PROVEN negative result |

The direct source inventory therefore closes the ordinary model writer and
the exact debris writer, but it does not close every retail draw-module
variant. In particular, W3DDefault and W3DModelDraw's non-draw virtuals still
need independent retail boundaries if the requested all-site table is to be
accepted.

### Why a raw `+0x54` search is not the requested inventory

`+0x54` is slot 21 for many unrelated render-object and game interfaces. A
read-only scan found 217 `call [register+0x54]` instructions across the image;
most are not `RenderObjClass::Set_Transform`. The W3DView update body itself
contains a GameClient vtable `+0x54` call, as do camera, mouse, prop-buffer,
water, network, and other paths.

The exact direct `E8` references to the RenderObjClass::Set_Transform body at
VA `0x00D201A0` were only:

```text
RVA 0x009312F8   CameraClass transform override/helper
RVA 0x00932658   CameraClass constructor initialization
RVA 0x00951A7B   Line3DClass constructor initialization
RVA 0x00956AA8   AABoxRenderObjClass transform override
RVA 0x00956B58   OBBoxRenderObjClass transform override
RVA 0x00957C9D   OBBoxRenderObjClass constructor initialization
RVA 0x00982118   Animatable3DObjClass transform override
```

These are render-object constructors or overrides, not the virtual draw-module
submission. The approximately 70 sites described in `docs/fps60.md` therefore
cannot be recovered by counting raw `+0x54` instructions. The full
draw-module-only callsite inventory remains `OPEN`; the table above records
the callsites whose receiver and cadence were statically established.

## 4. Object -> Drawable transform synchronization

### Object-side publication

`Thing::setPosition`, `setPositionZ`, and `setOrientation` update the Object's
matrix/cached position and invoke the old-matrix transform-change virtual.
The source implementation of `Object::reactToTransformChange` is at
`GameLogic/Object/Object.cpp:1992-2014`:

```cpp
if (m_drawable)
    m_drawable->setTransformMatrix(this->getTransformMatrix());
```

Retail evidence closes the important offsets and call:

```text
Object + 0x80       -> m_drawable
Object + 0x08       -> current Object/Thing Matrix3D
react body 0x001CDC30
  -> push Object + 0x08
  -> ILT 0x000361CE
  -> transform-copy body 0x00132200
  -> receiver virtual transform-change slot +0x14
```

The body at RVA `0x001CDC30` also updates the Drawable's frame/transform
bookkeeping before the copy and then continues with partition/contain checks.
The source and retail field flow make the Object-to-Drawable edge `PROVEN`.
The ledger row currently reports only 24 bytes for this address even though
the retail body continues through the shown transform-copy call and much
more. That size/boundary anomaly is `OPEN` and should not be silently used to
claim a complete matched Object body.

The transform-copy body at RVA `0x00132200` copies all 12 Matrix3D floats to
receiver `+0x08`, refreshes cached position at `+0x38/+0x3C/+0x40`, refreshes
angle at `+0x44`, clears `+0x5C`, and calls the old-argument transform-change
virtual at `+0x14`. The current source reconstruction is
`Common/Thing/Rva00132200ThingTransform.cpp`.

Do not merge it with the separately matched body at RVA `0x00132350` behind
ILT `0x00023D49`. That body has the no-old-arguments path: it copies the
matrix/caches, compares old and new position/angle, and calls a no-argument
virtual at `+0x18` only when those values changed. Both bodies are real
transform plumbing, but their callback contracts differ.

### Logic writers that converge on the bridge

The static source search found direct Object transform writes in the normal
movement and exceptional logic families, including:

* `Locomotor.cpp` and `PhysicsUpdate.cpp` for movement/physics;
* `ToppleUpdate.cpp`, `StructureToppleUpdate.cpp`,
  `Rva002B1610ToppleUpdate.cpp`, and `HelicopterSlowDeathUpdate.cpp` for
  topple/death and rubble movement;
* `ChinookAIUpdate.cpp` and contain/rider code for carried/rider positions;
* `DumbProjectileBehavior.cpp`, `RailroadGuideAIUpdate.cpp`, `Weapon.cpp`,
  and `ObjectCreationList.cpp` for projectile/creation paths;
* other object update/contain callers that use `setPosition`,
  `setOrientation`, or `setTransformMatrix`.

These are not independent render-object writers. When the Object owns a
Drawable, they converge on the same Object transform-change callback and then
the same Drawable/model path. This is the static result for death/topple and
ordinary rider/contain movement.

For garrisoned units, `Object.cpp` explicitly notes that the unit can be
removed from partition visibility while contained. That changes region and
visibility behavior, not the existence of the Object-to-Drawable transform
copy. No separate garrison-root `RenderObjClass::Set_Transform` was found.
Likewise, the source contains mounted/rider and horse-like containment paths,
but no independent mounted root transform consumer was closed; the safe grade
is `PLAUSIBLE` through the normal Object/Drawable route.

### Drawable instance transform and physics transform

The exact BFME instance setter body is RVA `0x00411840`, size 581. Its static
layout is:

| Drawable offset | Field/use |
|---:|---|
| `+0x168` | previous-instance Matrix3D |
| `+0x198` | current instance Matrix3D |
| `+0x1FC` | expiration date |
| `+0x304` | frame stamp |
| `+0x3AF` | instance-identity flag |

It saves the current instance to history, writes the supplied matrix or
identity, optionally preserves the new value as previous, stamps
`TheGameEngine` plus client frame, and sets expiration to `0xFFFFFFFF`. Static
callers include `SwayClientUpdate`, `JetAIUpdate`, and
`StructureCollapseUpdate`. This is an additional visual transform, not a
replacement for Object publication and not a direct RenderObj write.

`Drawable::draw` at `Drawable.cpp:4972-4987` composes the final module input:

```text
getTransformMatrix()
  -> postMul(getInstanceMatrix()) if instance is not identity
  -> applyPhysicsXform()
  -> doDrawModule() for every module in Drawable+0x150
```

`Drawable::getTransformMatrix` returns the bound Object matrix when
`m_object` exists (`Drawable.cpp:6475-6483`), otherwise the Drawable/Thing
matrix. `applyPhysicsXform` reads the Object physics/locomotor chain and
modifies only the local Matrix3D passed to modules. It applies total Z,
pitch, roll, and yaw subject to dead/physics/tactical/script-freeze gates
(`Drawable.cpp:1540-1578`). Thus topple, death wobble, vehicle suspension,
aircraft movement, instance offsets, and the Object root all converge before
W3DModelDraw's final `Set_Transform`.

### Phase-2 history is not publication

The phase-2 logic loop gates the history call on `Object+0x168 !=
GameLogic+0x3C`. ILT RVA `0x0002BB43` is pinned under the lexical name
`?bfmeRecordTransform@Object@@QAEXI@Z`, but it reaches the exact 217-byte body
at RVA `0x001C0BE0`, whose behavior is clearly a Drawable history recorder:

```text
Drawable +0x138  recorded Matrix3D
Drawable +0x178  recorded frame / previous-position area
Drawable +0x184  recorded-transform-valid flag
```

The body copies the current/recorded translation into previous-position,
copies the current transform into recorded history, stamps the frame, marks
history valid, and clears the interpolation-cache-dirty flag. It does not
call `RenderObjClass::Set_Transform`. Therefore it is a useful old/new sample
source but not the Object-to-render-object bridge. The lexical `Object` name
on the ILT is an identity debt.

## 5. Other render-object writers and special cases

The following direct writers are outside the ordinary Drawable draw-module
root and must not be counted as ordinary model `doDrawModule` submissions:

| Source path | Operation | Classification |
|---|---|---|
| `W3DRenderObjectSnapshotUpdate.cpp:214` | clone parent RenderObj, copy parent transform, then attach user data | snapshot/clone initialization |
| `W3DGhostObject.cpp:271,339,398` | copy ghost render-object and subobject transforms | fog/deleted-object snapshot path |
| `W3DBridgeBuffer.cpp:3713,3770` | place bridge towers from bridge/map coordinates | map-owned direct render objects |
| `Rva00720BB0LookupDispatch.cpp:164` and following | create tree topple/push-aside render objects, set rotation, add to scene | tree/topple special render path |
| `W3DModelDraw.cpp:3305` | set transform after model-state/render-object recreation | event/setup path |
| `W3DModelDraw.cpp:711,741,2757,2763` | temporary identity/restore writes | query/particle bookkeeping, not persistent root |

The snapshot and ghost paths explain why a global “all Set_Transform calls are
unit roots” rule would be wrong. They may matter to visual parity, but they do
not establish an alternate Object-to-Drawable path for ordinary units.

For contained units, riders, mounted heroes, and garrisoned models, the source
evidence closes the base Object/Drawable route and the draw-module/subobject
state machinery, but it does not close a separate specialized root writer.
`W3DModelDraw`'s `handleClientTurretPositioning`, bone/particle recalculation,
recoil, and model-state paths are the likely subobject consumers; their exact
retail call boundaries remain `OPEN` except for the normal `doDrawModule`
body.

## 6. Consequence for interpolation seam selection

The static evidence supports these conclusions:

1. Sampling/writing only Drawable position, Drawable `+0x104`, or a list node
   cannot move the picture. The ordinary model picture is driven by the
   render object at W3DModelDraw/module `+0x34` and its `Set_Transform` call.
2. An Object-side sample is upstream of instance and physics transforms. It
   is insufficient if the intended visual result includes formation/sway,
   vehicle physics, topple, or model attachment adjustment.
3. The ordinary model transform is submitted per draw by
   `W3DModelDraw::doDrawModule`; a hook before the W3DView drawable callback
   can be overwritten by that submission. The exact final writer is RVA
   `0x0077B680`.
4. In the current source order, `W3DDisplay::draw` calls `updateViews()` before
   `drawViews()`, and the W3DView update callback is where `Drawable::draw` and
   the normal model submission occur. `Display::drawViews` is consequently a
   later scene-traversal seam suitable for a temporary render-object override,
   not an upstream model-write seam. Its View slot-name conflict and callback
   literal must still be resolved before treating the retail vtable route as
   completely proven.
5. The consumer's offsets are materially corrected: draw modules are
   Drawable `+0x150`, the getter is module vslot `+0x9C`, the returned
   interface is module `+0x0C`, and render object `+0x28` is relative to that
   interface (`module+0x34`).

## 7. Remaining OPEN items

* Identify the retail callback at VA `0x00B3AD50` and prove whether it reaches
  `Drawable::draw` or is a stale/misattributed literal.
* Reconcile the exact `Display::drawViews` `+0x178` call with the W3DView
  owner table and the secondary update/draw slots, including the extra BFME
  SubsystemInterface entries.
* Recover the complete draw-module-only subset of the approximately 70
  `Set_Transform` sites. A raw `+0x54` count is not sufficient because the
  slot is shared by unrelated classes.
* Recover independent retail identities/boundaries for W3DDefault draw and
  transform-change paths, W3DModelDraw `reactToTransformChange` and
  `setModelState`, and the temporary particle/bone writes.
* Correct the ledger size/boundary anomaly for `Object::reactToTransformChange`
  only after its full retail function boundary and identity are independently
  rechecked.
* Audit the separate snapshot/ghost, bridge, tree-topple, attached-effect,
  rider/mounted, and garrison/subobject render paths if they are required for
  complete 1:1 visual parity.

No source, ledger, build, executable, or runtime state was changed by this
audit.
