# GetImageInfo includes its CHOKE cleanup label

The original MSVC 7.1 libc.lib pdblkup.obj places
`?GetImageInfo@@YAPAUImageInfo@@K@Z` at section offset 0, `$CHOKE$18875`
at offset 771, and the function's `.ef` marker at offset 849. The latter
label is an internal cleanup block, not a separately framed function.

Retail RVA 0x009F808E begins the ordinary EBP frame (814h local bytes,
then saved registers). Branches at 0x009F8236, 0x009F82F0, 0x009F832F
and 0x009F8352 enter the cleanup at 0x009F8391. Normal lookup branches
at 0x009F80B8 and 0x009F8388 enter its shared return sequence at
0x009F83D4. That sequence restores the original frame and saved
registers and returns at 0x009F83DE. The next function starts at
0x009F83DF. Thus the complete extent is 849 bytes, with no padding.

The local retail PE and Ghidra memory at VA 0x00DF83C7 agree through
the return. The unchanged original archive matches all 605 concrete
non-relocation bytes over 849 bytes. Existing archive verification masks
relocations; that equality is not independent proof of their bindings.

Retire the 78-byte `$CHOKE$18875` row and tombstone it, then extend the
parent from 771 to 849 bytes. This preserves the original archive's real
function identity and member provenance without claiming a new conversion
or a new identity. It follows the same internal-label correction already
recorded for `$esperror$18513` inside `__RTC_CheckEsp` in deleted_rows.csv.
AGENTS.md requires one real body per address and byte verification of the
complete extent; a local label is not an independent function.
