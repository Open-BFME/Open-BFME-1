# GameInfo option parser at 00621C40

## Identity and extent

The existing matched `RecorderReadReplayHeader.cpp` caller passes its embedded
GameInfo, a by-value AsciiString and a true boolean to this body through ILT
0000FC59. `SkirmishBattleHonorsConstructor.cpp` and the independently matched
`LANAPIHandleJoinAcceptRva0068CF00.cpp` use the same three-argument parser. The
Zero Hour `GameInfo.cpp` parser supplies the matching token/slot algorithm;
BFME's extra boolean preserves existing human names when incoming names are
empty. These callers support the existing semantic name and cdecl/bool ABI.

The complete range is 00621C40..00622F22 (4834 bytes): executable instructions
end with RET at +12B7; five switch destinations occupy +12B8..12CB and the
22-byte C-through-X lookup occupies +12CC..12E1. The old Ghidra extent 4777
stops inside the epilogue and is not a valid replacement extent. No boundary
change or neighbouring claim is made.

## Behavior and independently witnessed layouts

The previous bank retained six Zero Hour option paths absent from retail.
BFME accepts M, MC, MS, SD and S; it requires all five. M contains a THREE-digit
hex map mask followed by the map name. Existing authored `GameInfoGrabHexInt3.cpp`
and map-path helper00621350 independently establish that format and conversion.
The parser constructs eight 0x44-byte GameSlots and eight four-byte UnicodeStrings.
A false third argument saves all eight old names before parsing; an empty parsed
human name is then replaced by that slot's saved name.

`GameSlot::setState` at0061F210 independently proves that its third argument is an
8-byte connection record: at+172..182 it copies argument word0 to this+30 and
word4 to this+34, then pops12. In this parser word0 is the parsed IP and word4
contains the port and native padding. It is not a NAT-plus-port record. The NAT
behavior is separately validated in0..128 and stored at GameSlot+38. The native
copy constructor0006E600, reset0061EC70 and LANGameSlot copy/assignment owners
independently establish the UnicodeString at+28, AsciiString at+2C and total44.
The older reference GameInfo shim conflates IP/NAT, so the correction is scoped
to this source rather than changing unrelated compiled views.

The setState body keeps virtual reset at slot0 for a human, updates color/start/
faction/team defaults, fetches the existing GUI:Open/EasyAI/MediumAI/HardAI/Closed
labels through GameText slot28, and copies the native connection struct. Keeping
that record as one C++ struct was the final shape lever: splitting its two words
prevented the retail register allocation and cleanup sharing.

## Calls and data

Before reconstruction `tools/callees.py 0x00621C40 4834` identified all29 direct
retail targets. The final strict resolver verifies132 direct call sites with zero
unresolved names and zero byte differences. No new symbols pins are required.
The11 isEmpty calls explicitly select the canonical StringBase<char> method,
matching ILT0000C752 to0005E4C0 rather than an unproven AsciiString wrapper.

The existing map helper00621350 returns AsciiString by hidden pointer and takes
(const AsciiString&,bool); the converted single-line wide-string helper006617D0
returns native STLport basic_string<unsigned short> and its43-byte destructor
004D5170 is reached through existing ILT0003BE17. The canonical string forwarding
constructors/destructors preserve their actual StringBase calls and unwind order.
The complete native slot-copy constructor0006E600 and setSlot0061F630 preserve
GameSlot's by-value44-byte contract.

Non-string DIR32 observations are independently consistent with existing owners:
GameSlot array constructor/destructor ILTs00013E58/0000B988; UnicodeString array
constructor/destructor ILTs00041C95/0003B304; TheGameText VA012F147C (existing
GameText interface callers); MultiplayerSettings VA012ED5FC (existing settings
callers); PlayerTemplateStore VA012ED750 (existing preferred-faction callers);
empty UnicodeString VA01336E54 (existing WOL callback owners). CRT IAT cells are
strtol013594DC, sscanf01359494, atoi01359384 and free013593D4. There is no newly
introduced vtable symbol or numeric call target.

## Verification

Native source uses canonical ascii_string.h/unicode_string.h, normal C++ loops,
switches and native strings. No asm, volatile shaping, raw frame references or
new pins. Scratch receipts: build/four-hour-gameinfo/strict-final.txt (4834 bytes;
132 direct calls; zero unresolved and zero differences), probe7.txt (231 object
relocations; exact full range), dir32-data.json, retail.asm, setstate.asm and fresh
read-only Ghidra exports. Normal add_match/build and commit/push hooks are required
for publication. Session model GPT-6; reconstruction reached strict exact in
approximately11 minutes from01:16 UTC, starting from the existing bank.
