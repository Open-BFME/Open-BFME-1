# Separate base-check fallback data

Checked 2026-10-29 at BFME 1 control 98199b2d. The linking picker reserved
?g_010E1F40@@3MB; its matched caller at RVA 0x00328680 and the datum's RVA
0x00CE1F40 were separately claimed before adding the definition.

## BFME 1 facts

The matched 281-byte ScriptConditions::evaluatePlayerHasNOrFewerBases reads
VA 0x010E1F40 when TheWritableGlobalData is null, converts that float to an
integer and compares it with the game frame. Retail .rdata holds exactly
00 00 C8 41: the four-byte float 25.0. No existing data row owns that range.
This identifies the compiled fallback, not the later runtime configuration.

The new data-only Common/Data/Rva010E1F40.cpp defines the existing decorated
external name once. Keeping the definition separate leaves the caller's
observed memory load intact. The original TU/name of the constant is not
independently recovered; its address-derived name is retained.

add_data_match.py proves compiler sizeof=4, a four-byte allocation extent,
all four initializer bytes, no relocations and nonoverlap before writing the
row. It is the normal data-row admission path, including its address-global
admission handling. No pin, alias, header or function row is added.

## Donor evidence

Reviewed BFME 2 b5a7b829, Code/GameEngine/Source/GameLogic/ScriptEngine/
ScriptConditions.cpp at evaluatePlayerHasNOrFewerBases (RVA 0x003E58F0).
Its null-global branch also selects 25.0f before the frame check. Its extent
is 192 bytes, kind index 177 and GlobalData field +0x110C; those are donor
facts. BFME 1's existing body uses its own masks, +0x11F8 view and arithmetic.
No donor layout, constant address or function body is imported. The native
BFME 1 bytes independently establish this datum's value and placement.

## Verification and limit

Provider and consumer pass the normal build together: one four-byte data row,
one 281-byte function row, one float reference and eleven recorded DIR32
references. The caller source is unchanged.

Before: census ea2916a82d reports the missing decorated global and 0 of the
caller's 278 authored nonpadding bytes linked. After: the bounded current
preview reports UNKNOWN after 55 seconds for provider and caller. The new
provider is at its current link-order place, but no full selection verdict
or new linked-byte figure is established. Carry both units into the next
normal census; no increase in LINKED is claimed here.
