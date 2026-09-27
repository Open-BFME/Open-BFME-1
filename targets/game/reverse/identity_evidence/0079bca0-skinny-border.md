# drawSkinnyBorder native conversion

2026-09-27, GPT-6. RVA `0079BCA0`, 2304 bytes.

## Identity and extent

The original EA W3DControlBar.cpp counterpart has the same four integer
arguments, eight `FrameT`, `FrameB`, `FrameL`, `FrameR`, and `FrameCorner*`
image names, five-pixel repeated edges, two-pixel remainder handling, and
four corners. W3DDrawMapPreview calls it after the map and resource icons.
The complete retail body ends in `ret` at offset `8FF`; INT3 follows.
The sole lifted definition is removed from W3DControlBar.cpp, and its existing
ledger row now points to W3DSkinnyBorder.cpp. There is no alias or extra claim.

## Contracts

All eight temporary strings use the canonical AsciiString/StringBase headers.
The aligned direct calls are the char-pointer constructor `00888BC0`,
ImageCollection::findImageByName through ILT `0001D606` to `005D2CF0`, and
StringBase::releaseBuffer `00887940`. The complete 84-byte lookup body reads
the string reference, adds eight to its buffer, performs the named lookup,
returns its stored Image pointer or null, and uses `ret 4`. The singleton
pins are the existing ImageCollection at VA `012F6924` and Display at
VA `012F1270`. No pin or shared header changes are needed.

The BFME display operation is an inline integer-coordinate wrapper around
slots `B0`, `D4`, and `DC`. Slot `D4` takes the Image pointer, four floats,
color, and mode; the wrapper converts the four integers after slot `B0`.
The independently installed W3DDisplay table at VA `0111EDD0` selects:

* `B0`: ILT `000096F6` to `006E9B70`, a complete no-argument tail wrapper
  loading receiver+`164` before jumping to `00934820`.
* `D4`: ILT `0002743A` to `006F21B0`; its complete body consumes seven
  arguments and returns with `ret 1C`. It interprets the four coordinates
  as floating point, clips them, and reads the Image UV rectangle.
* `DC`: ILT `00008265` to `006E9B80`, a complete no-argument tail wrapper
  loading receiver+`164` before jumping to `00934940`.

The landed ShellMenuScheme::draw at `00580BD0` independently uses the same
three virtual contracts. Its own wrapper takes float coordinates, while
this caller retains integers until inside the bracket. The shared Display
header still has the older integer virtual declaration. A scoped,
address-derived view models these slots without changing that header or
asserting names for the unnamed target methods.

## Verification

The native body is 2304/2304 bytes exact, with 60 relocation operands.
The strict source gate passed 1/1 and independently verified all eight
literal targets. The old W3DControlBar source passed 22/22 after removing
the lifted body. Its 13 existing funclet claims remain owned by the same
reference context and were byte-verified despite compiler-label renumbering;
they belong to the other existing callbacks, not this new body. No funclet
ownership or additional progress is claimed.
