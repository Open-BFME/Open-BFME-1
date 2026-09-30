# W3DShrubBuffer xfer native-header bank: five name-guard pairings

This evidence concerns the bank at RVA `0x00721380`, extent 1557 bytes.
Retail ends with `ret 4` at `0x00721992`, ending at `0x00721995`.
The new bank is **not an exact conversion**: probe measured 1553/1557 bytes,
33 relocations and 166 differing nonrelocation bytes; official `re_log` measured
quality 0.8882. Instruction-normalized shape 0.994 is not its byte score.
No new function identity or alias pin is justified by that near match.

## Exact snapshots covered

Both paths are `targets/game/reverse/attempts/0x00721380.cpp`.
The before snapshot is HEAD, SHA-256
`f29946e7fdfbc31356fa45d6335aff6823d240c92b3accc03fd438e7836aaf3e`.
The after snapshot is the index, SHA-256
`f09487e1e12ba347b164a69d418ca53cc5c43a69885956f49e6ea383ca5814c2`.
These hash the complete UTF-8 source bytes, including line endings and comments.
They are also the source hashes of the corresponding immutable attempt history.

## BfmeParticleSystemXferHandle -> Rva0010C3E0

Retail caller `0x007217DA` has bytes `E8 C2 74 8E FF`, calling ILT
`0x00008CA1`. The ILT has `E9 3A 37 10 00`, jumping to body `0x0010C3E0`.
Independent decoding of all 25 bytes of that body gives:

```
0010C3E0  mov edx,[esp+8]
0010C3E4  mov ecx,[esp+4]
0010C3E8  mov eax,[ecx]
0010C3EA  push 4
0010C3EC  push edx
0010C3ED  push 01089218h
0010C3F2  call [eax+90h]
0010C3F8  ret
```

Thus the two input arguments remain caller-cleaned; the first is a receiver
pointer and the second is a context pointer. The body forwards them to virtual
slot `0x90` with its own distinct table and width 4. It does not independently
prove a particle-system class or a named handle-transfer API.
`game/GameEngine/Source/Common/MidVirtualSlot90Forwarders.cpp` already implements
this independently matched body as
`void Rva0010C3E0(MidVirtualSlot90Receiver *, void *)`.
The after bank calls that existing identity through an explicit receiver-view
cast. It does not add a second name at `0x0010C3E0`. The old descriptive helper
was an unsupported local declaration, not a proven identity to preserve.
`pin_consistency --symbol` currently finds no pin for the body symbol; this bank
creates none and makes no claim that the eventual caller is linked.

## ModuleData -> Rva00721380ModuleDataView

This is a false type pairing. The after bank includes native
`game/GameEngine/Include/Common/Module.h` and continues to use `ModuleData *`
for stored data pointers. It does not rename the native type.
The old local class invented nine preceding virtual slots and `slot09()`.
The native header supplies `ModuleData : Snapshot` and its actual declared
`getAsW3DTreeDrawModuleData()` method. Compiling the direct native-method
alternative in `build/shrub_native_721380/module.cpp` produces `FF 52 18` at
function offset `+0x185`. Retail instead has `FF 52 24` at that offset
(`0x00721505`), following `mov ecx,[ebp+8]` and `mov edx,[ecx]`.
Consequently that available native method layout cannot express this retail
slot. The separate address-derived view describes only the observed `+0x24`
pointer-returning virtual ABI. It is not a renamed native ModuleData, a proven
EA subclass, or a claim that the observed slot has the native method's name.

## ModuleInfo -> Rva00721380ModuleInfoView

The old declaration used a two-pointer view but called it `ModuleInfo`.
The actual upstream class in
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h`
contains `std::vector<Nugget> m_info`, not this complete two-pointer object.
The bank needs only the independently observed prefix: retail offsets `+0x15B`
and `+0x161` read ThingTemplate-relative `+0x2A0` and `+0x2A4`, subtract the two
pointers and divide by 20; `+0x17C` reads the first record's pointer at `+8`.
The upstream Nugget's two AsciiString fields, data pointer, integer and three
boolean fields explain the matching 20-byte record prefix, but that does not
prove the full retail class or original member identity. The new distinct
opaque view describes those observed reads only. It does not claim to replace
or redefine upstream ModuleInfo or its STL specialization.

## XferVersion -> Rva00721380Version

The old XferVersion was a local two-byte helper, initialized `(1,2)`; no named
caller or EA definition proved that helper identity. The after bank includes
native `game/GameEngine/Source/Common/System/xfer.h`. That header supplies
`Xfer::Version` with `unsigned char data[2]` and the version operator overload.
The new address-derived helper derives from that native version type and
initializes those two bytes. Retail stores 1 and 2 at `+0x53` and `+0x58`, then
calls Xfer virtual offset `+0x28` at `+0x5D`. The native version type remains
provided by its header. The new constructor helper is not asserted to be an EA
class or an original version API; its address-derived name marks that limit.

## getModuleInfo2A0 -> rva00721380Modules

The old accessor was invented inline source returning a padded ThingTemplate
member at `+0x2A0`; the suffix itself recorded the measured offset, not an
original method identity. There is no retail call to such an accessor.
The after bank forward-declares ThingTemplate and uses a free address-derived
view accessor at the same observed offset. Upstream ThingTemplate.h names
behavior, draw and client-update module accessors, but this caller's two pointer
loads alone do not identify which native member occupies the BFME offset.
The new helper therefore makes no guessed member/method claim. It preserves
the reads while avoiding a local redeclaration of native ThingTemplate.

## Remaining adoption blocker

Native flat Coord3D is trivial in both the available WWLib BaseType header and
WWMath coord.h. The older exact scratch bank instead declared an inline
nontrivial copy constructor on its own Coord3D. That difference retains a saved
outgoing ESP temporary in the older body; removing the redeclaration loses four
bytes and changes stack homes. Native return-helper, derived-position and
explicit empty-AsciiString alternatives did not recover the retail shape.
The old exact scratch is evidence only; it is not landable source. This bank
preserves native headers and records the mismatch without an ABI alias.
