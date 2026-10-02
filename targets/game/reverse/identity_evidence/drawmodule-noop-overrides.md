# DrawModule empty shadow/geometry overrides

Retail image: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`,
SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses are RVAs unless labelled VA; evidence was decoded with pefile and
capstone. The 16 registered primary tables were enumerated mechanically as
recorded in [the interface census](drawmodule-interface-accessors.md).

## W3DDebrisDraw: three distinct one-byte overrides

The independent registration at `006C0046` names W3DDebrisDraw and factory
`006BEF40`. That factory calls ILT `0002E98D` -> constructor `007505C0`,
which seats VA `01121EC0` at `[esi]` at instruction `007505DD`. Primary slot 2
routes through `00010041` to `00750640`, returning literal VA `0111D2DC`,
`W3DDebrisDraw`. Thus the owner is established independently of these no-ops.

| Slot | Pointer RVA | ILT RVA | Body RVA | Public virtual method |
|---|---|---|---|---|
| 11 | `00D21EEC` | `00028B19` | `00750650` | `void releaseShadows()` |
| 12 | `00D21EF0` | `00021FA3` | `00750660` | `void allocateShadows()` |
| 36 | `00D21F50` | `0000D229` | `00750670` | `void reactToGeometryChange()` |

Each body is exactly `C3`, followed by INT3 padding. An executable-section E9
scan finds exactly the one listed ILT per body, and a bytewise whole-image
pointer scan finds its stub VA exactly once, at the listed table entry. These
are concrete class overrides, not inherited/shared bodies.

The full lexical/type witness is the unmodified Zero Hour header
`GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DDebrisDraw.h`:
its public section explicitly defines inline empty overrides for all three
names (lines 63-68), with no arguments, no const qualifier and void return.
Their exact manglings are respectively
`?releaseShadows@W3DDebrisDraw@@UAEXXZ`,
`?allocateShadows@W3DDebrisDraw@@UAEXXZ`, and
`?reactToGeometryChange@W3DDebrisDraw@@UAEXXZ`.

Slot alignment is local and corroborated by both neighbouring functional
entries and the independently established getter block:

- Retail slot 9 -> `007508A0` is the matched `W3DDebrisDraw::doDrawModule`.
  The Zero Hour DrawModule and W3DDebrisDraw declarations put doDrawModule,
  setShadowsEnabled, releaseShadows, allocateShadows in that order. BFME
  slots 9-12 retain this four-method block; slot 10 -> `00750550` is the
  guarded shadow enable setter. The primary DrawModule base table has purecall
  entries at 9-12, agreeing with its four abstract declarations.
- The Zero Hour tail `reactToTransformChange`, `reactToGeometryChange`,
  `isLaser`, then interface acquisition maps to BFME slots 35-38 onward.
  BFME slot 35 -> `00750870` is the render-object transform update; slot 36
  is abstract in DrawModule's table and the public empty override above in
  the Debris table. Slot 37 inherits the DrawModule Bool-false body `007500D0`.
  The const/non-const ObjectDrawInterface getters at 38/39 and the Debris
  overrides at 40/41 are independently proven by the linked evidence note.
  No inference from address adjacency names any method.

Replace the existing one-byte address-placeholder rows, retaining their
extents. Compile the unmodified upstream inline bodies in
`W3DDebrisDrawDefaultVirtuals.cpp` with explicit emission anchors. Delete the
orphaned standalone placeholder files and only the relevant definition in the
shared no-op TU. No guessed members, header edits, pins, or baseline expansion
are required.


## W3DLaserDraw: the same three override slots

The constructor/registration chain is independently proven in the linked
interface census: registry `006C0112`, factory `006BF150`, ctor `00757E70`,
primary table VA `01122A00` stored at `00757EAC`. Primary slot 2 goes through
ILT `00045629` to `00757B40`, returning VA `0111D298`, literal W3DLaserDraw.
Thus this class owns the following unique entries:

| Slot | Pointer RVA | ILT RVA | Body RVA | Public virtual method |
|---|---|---|---|---|
| 11 | `00D22A2C` | `00038A3C` | `00757B50` | void releaseShadows() |
| 12 | `00D22A30` | `00022C5F` | `00757B60` | void allocateShadows() |
| 36 | `00D22A90` | `000150F5` | `00757BA0` | void reactToGeometryChange() |

Each stub VA occurs exactly once in a bytewise whole-image dword scan, at its
listed slot. Each target is exactly C3 followed by CC. These are distinct
class overrides, not shared/inherited functions. The same locally proven
slot blocks above apply: the Laser table has its already-matched doDrawModule
in slot 9 and the proven typed getter block in slots 38-45.

The unmodified ZH W3DLaserDraw.h public section explicitly defines empty
releaseShadows, allocateShadows and reactToGeometryChange (lines 82-87), each
non-const, void, without arguments. It supplies the exact names and ABI:
`?releaseShadows@W3DLaserDraw@@UAEXXZ`,
`?allocateShadows@W3DLaserDraw@@UAEXXZ`, and
`?reactToGeometryChange@W3DLaserDraw@@UAEXXZ`. The new TU includes that header
and emits those definitions through qualified-call anchors. Remove only the
three replaced definitions from their shared placeholder TUs; all unrelated
bodies stay in place. Extents remain one byte and no callee pins change.
