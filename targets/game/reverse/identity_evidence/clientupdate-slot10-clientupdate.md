# ClientUpdateModule slot 10: BeaconClientUpdate::clientUpdate

This is an identity finding, not a C++ conversion. The ledger's 259-byte
`?d_00603640@@YAXXZ` dump remains unchanged. Its proven semantic identity is
`?clientUpdate@BeaconClientUpdate@@UAEXXZ`.

All addresses are RVAs unless called VAs. Evidence comes from pefile/capstone
on `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

## Registered owner and unique route

`module_registry.tsv` registers BeaconClientUpdate at `00130800`, using
literal `00C8F7A0`, instance factory `00121B70`, constructor `006030C0`, and
object size `0x14`. Direct retail checks:

- Factory `00121B70` pushes allocation size `0x14` at `00121B86`, then calls
  ILT `00046B1E` at `00121BAB`; that stub jumps to `006030C0`.
- Constructor `006030C0` calls DrawableModule through ILT `00002874` and
  installs primary table VA `01115248` at instruction `006030D4`.
- Its primary slot 2 goes through ILT `000084EF` to `00603100`. That body
  returns VA `0108F7A0`, the exact literal `BeaconClientUpdate`.
- Primary slot 10, pointer RVA `00D15270`, contains ILT VA `004369C6`.
  ILT RVA `000369C6` jumps to body `00603640`.
- An executable-section E9 scan finds exactly this one stub targeting the
  body. A bytewise whole-image dword scan finds its VA exactly once, at the
  slot-10 pointer above. This is an owner-specific override, not a shared base
  callback assigned to an arbitrary derived class.

## Complete registered family and slot meaning

Enumerating the three registered ClientUpdate classes gives:

| Owner | Constructor | Primary-vptr store | Table VA | Slot-10 ILT | Slot-10 body |
|---|---|---|---|---|---|
| AnimatedParticleSysBoneClientUpdate | `00602ED0` | `00602EE4` | `01115210` | `0000D0B2` | `00603020` |
| BeaconClientUpdate | `006030C0` | `006030D4` | `01115248` | `000369C6` | `00603640` |
| SwayClientUpdate | `006044E0` | `0060450E` | `011154F0` | `00046B4B` | `00604840` |

All three share the Module/DrawableModule slots 5-8. Slot 10 in the first and
third tables is already independently matched as `clientUpdate`: the 61-byte
AnimatedParticleSysBone callback walks draw interfaces and updates particle
bones; the 573-byte Sway callback implements the Zero Hour sway update twin.
Their registered constructors identify the owners independently of their
callback names. BFME's preceding slot 9 is not named by this finding.

The lexical/type witnesses are unmodified Zero Hour headers under
`GeneralsMD/Code/GameEngine/Include/`:

- `Common/ClientUpdateModule.h:54-60`: public abstract
  `virtual void clientUpdate() = 0`.
- `GameClient/Module/BeaconClientUpdate.h:63-69`: public
  `virtual void clientUpdate(void)` override.
- `GameClient/Module/AnimatedParticleSysBoneClientUpdate.h:53` and
  `GameClient/Module/SwayClientUpdate.h:56`: the corresponding overrides.

The concrete Beacon twin is
`GeneralsMD/Code/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdate.cpp:162-184`.
Retail agrees in the distinguishing sequence: obtain the drawable and return
if absent; create a particle system if the ID at +0x0C is zero; gate a radar
pulse on visibility and frame count; calculate pulse duration from module
configuration, call the radar event route with event 6, and update the last
pulse frame at +0x10. The call through ILT `00008B8E` occurs at `006036EA`.
BFME has additional smart-holder cleanup and an extra hidden-drawable branch;
this note does not assert that a literal port of the ZH body is byte-exact.

The header establishes public, non-const, virtual, void, no-argument ABI:
`?clientUpdate@BeaconClientUpdate@@UAEXXZ`. Retail receives this in ECX, saves
it in EBX, and both normal exits use plain `ret`, consistent with that ABI.

## Boundary and future conversion

The body starts with its SEH prologue at `00603640`. One exit returns at
`0060370C`; the alternate epilogue restores FS:[0] and returns at `00603742`.
The first INT3 is at `00603743`. Thus the complete extent is exactly 259 bytes,
not the shorter prefix through the first return.

`tools/callees.py 0x00603640 259` reports seven direct targets. In particular,
`006032F0` is reached directly at `00603673` with a local-result address in
ESI; the normal stack-only inference is insufficient to reconstruct that
helper ABI. Any future conversion should independently establish this helper
and its smart-holder destruction at ILT `00013994` -> `001DA440`, then use the
canonical callee names. No new pin, guessed member, naked lift, source body,
or matched-byte claim is introduced here.
