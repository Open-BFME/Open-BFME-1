# TeamTemplateInfo constructor, RVA 0x000EFEB0

The complete 2,992-byte body is `TeamTemplateInfo::TeamTemplateInfo(Dict*)`.
The already-native `TeamPrototype` constructor at 0x000F3E40 calls this constructor
for its embedded 0x144-byte member. The original ZH Team.cpp constructor has the
same seven unit specifications, waypoint lookup, and team-property reads. Those
independent witnesses establish identity before byte comparison.

## BFME layout

The retail stores prove seven 12-byte TCreateUnitsInfo elements at +4, count +0x58,
home position +0x5C, presence +0x68, and scriptOnCreate +0x6C. BFME inserts the
string read with the literal-backed `teamEventsList` StaticNameKey at +0x70;
scriptOnIdle is +0x74 and initialIdleFrames +0x78. The latter receives five times
the integer read using `teamInitialIdleSeconds`; no frame-rate claim is implied.
The 32 generic script strings occupy +0xC4..+0x144. These changes are witnessed
in this retail body; ZH alone has sixteen generic scripts and no events-list field.

All 51 StaticNameKey operands were decoded through their string pointers before
using their source names. The property strings and destination offsets establish
the corresponding semantic member names. The native string comparison exposed by
AsciiString::compare reproduces the retail waypoint comparison inline.

## Virtual table and callbacks

The installed vtable is VA 0x01085E70. Its four entries route through ILTs to
0x000F0D70 (scalar deleting destructor), 0x000F0D50 (loadPostProcess),
0x000F0D60 (literal TeamTemplateInfo name), and 0x000EC810 (xfer). The last body
passes version 1 through Xfer slot +0x28 and the productionPriority address +0x9C
through slot +0x78, agreeing with the original TeamTemplateInfo::xfer.
The current shared snapshot.h reverses name/load relative to these witnessed
slots, so the translation unit uses an address-qualified local ABI base.

The vector helper is the existing `??_L@YGXPAXIHP6EX0@Z1@Z` at 0x009F6EE4.
Its two calls use the independently decoded element counts and strides:

| Array | Count/stride | Constructor callback | Destructor callback |
|---|---|---|---|
| TCreateUnitsInfo at +4 | 7 / 12 | ILT 0x0003D7F3 -> 0x000ED560, 10B | ILT 0x00030251 -> 0x000ED570, 8B |
| AsciiString at +0xC4 | 32 / 4 | ILT 0x00017BD9 -> 0x00062030, 9B | ILT 0x0000D828 -> 0x0005EE90, 5B |

All four emitted callbacks match the complete retail instruction bodies. The
TCreateUnitsInfo constructor zeros its string at +8; its destructor adds eight to
this and tail-calls StringBase<char>::releaseBuffer. The existing ledger calls
0x000ED560 BridgeFXInfo; this conversion does not add a second callback claim or
pin. The constructor's array layout and original TCreateUnitsInfo definition
provide independent evidence that this older callback name merits correction.

## Scoped dependency pin

The only missing REL32 identity was canonical
`?getName@Waypoint@@QBE?AVAsciiString@@XZ`, pinned to body 0x000EE6D0.
Existing native camera look-toward callers already use the same const method with
a BfmeWaypointNameString return alias and reach ILT 0x0001026C. The 32-byte body
copies the string at this+8 into its hidden result using StringBase<char>'s copy
constructor at 0x00887B60, returns that result in EAX, and uses ret 4. Thus both
Waypoint identity and the native AsciiString return ABI are independently proven;
the new caller's desired byte shape is not the identity argument.

## Validation

The full constructor is exact under strict REL32 resolution with zero unresolved
symbols. add_match's scoped gate passes 1/1, with one literal and four empty-string
references verified. The callback bodies were checked separately, including their
StringBase releaseBuffer tail calls. Pin consistency passes with no new baseline.
No shared header or generated source was changed.
