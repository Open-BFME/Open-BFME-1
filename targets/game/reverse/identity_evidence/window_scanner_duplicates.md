# Retire duplicate scanner claims at RVA 0x004844F0 and 0x00484510

The retained identities are the existing `scanInt(const char *, Int &)` and
`scanUnsignedInt(const char *, UnsignedInt &)` claims in the native
`GameWindowManagerScript.cpp`. Both bodies are 17 bytes. The shipped upstream
source declares these static wrappers in that order, following scanBool and
scanShort and preceding resetWindowStack and resetWindowDefaults. Each calls
sscanf with the literal "%d" and the address of its output reference.

The independently compiled native TU reproduces this six-function sequence:

| Native helper | Retail RVA | Size | Native COFF section |
|---|---|---|---|
| scanBool | 0x00484470 | 44 | 710 |
| scanShort | 0x004844B0 | 41 | 713 |
| scanInt | 0x004844F0 | 17 | 715 |
| scanUnsignedInt | 0x00484510 | 17 | 717 |
| resetWindowStack | 0x00484530 | 63 | 719 |
| resetWindowDefaults | 0x00484580 | 38 | 721 |

All six bodies reproduce retail instructions outside their recorded address
relocations. The typed, differently shaped surrounding helpers anchor the
source sequence. The two scanners have identical machine bytes; byte equality
alone cannot distinguish them. Source provenance and this unchanged emission
order support the already existing typed claims. This repair adds no identity
or name and does not swap their addresses.

The actual 17-byte body is `push eax; push 0x0107C7B4; push ecx; call
[0x01359494]; add esp, 0xC; ret`. Retail 0x0107C7B4 contains "%d"; IAT slot
0x01359494 imports MSVCR71.dll!sscanf. The native compiler's private static
helper ABI supplies the source in ECX and output pointer in EAX. The public
source signature is not a promise that an external caller can use ordinary
cdecl stack arguments to enter this optimized private body.

Native callers in the source use these typed wrappers for numeric GUI fields.
Current compiled matched callers inline them; this native object contains no
code REL32 reference to the out-of-line scanner symbols. In particular the
matched parseScreenRect reconstruction explicitly records six inline sscanf
calls. No direct matched-caller symbol proof is asserted here.

The opaque `?dup_004844f0@@YAXXZ` and `?dup_00484510@@YAXXZ` claims instead
come from two orphaned void/no-argument inline-assembly wrappers in Common.
They hardcode the format address and read ECX/EAX without typed parameters;
they reproduce the instruction sequence but provide no independent identity.
No source or pin refers to either duplicate symbol beyond its own definition
and ledger row. Their definition files and exactly their two ledger rows are
retired, with durable deletion tombstones. The existing native scanner source,
its two named rows, and every sibling row remain unchanged.

The native TU's scoped gate passes all 30/30 rows, 105 string literals plus
11 empty references, and 41 DIR32 operands. This retirement removes two
false identity claims and 34 duplicate claimed bytes; it creates no new
matched-byte or authored-byte credit. No identity baseline or guard is relaxed.

Before retirement, the official scoped gate also compiles the two exact
opaque source files and passes 32/32 rows across all three TUs, 105 string
literals plus 11 empty references, and 43 DIR32 operands. Thus the opaque
wrappers are byte-true copies; their extra identities are the error.
`multi_name.different` arises from different COFF relocation topology:
the native scanner has DIR32 fields at +2 (the typed "%d" literal) and +9
(the sscanf IAT), while each opaque copy has only +9 and hardcodes the format
VA into +2. The masked bodies consequently differ, although both resolve to
the same retail 17 bytes. No instruction mismatch or scanner byte repair is
claimed. Keeping the independently sourced native identity and retiring the
unsupported duplicate claim resolves the conflict without changing this guard.
