# RVA 0074E620: complete value-argument body

The former 41-byte `std::vector<unsigned char>::resize(unsigned int,
const unsigned char&)` claim in PartitionManager.cpp is independently
contradicted by retail argument handling, not merely unproven.

Decode the unpacked 1.03 PE from RVA 0074E620. The old end at 0074E649
omits two returns and the grow path. The complete 86-byte body ends with
`ret 8` at 0074E673; 0074E676..0074E67F are INT3 alignment.
At 0074E661, `lea esi,[esp+10h]` takes the address of incoming argument 2;
it does not load a reference. The helper called at 0074E66C goes through
ILT 00047041 to 0074DA00. That helper loads argument 3 then dereferences
its first byte (0074DA20/0074DA24), confirming byte-value storage here.

Decode the caller from its entry 0074F1F0. Calls at 0074F29B, 0074F2A6,
0074F2B1, 0074F2BC, 0074F2C7, 0074F2D5, 0074F2F8 and 0074F306 all use
ILT 0001656D -> 0074E620. They push literal 0 (seven sites) or 0xFF
(last site), followed by the count. These values cannot be valid byte
references. A full .text E8 scan finds these eight direct call sites only;
their parent is a generated dump, not a named-caller identity witness.

Ghidra function creation at VA 00B4E620 independently yields 86 bytes.
Its decompiler sees the stack-address helper argument but loses the dead
copy arm; retail bytes, not that draft, establish the complete extent.

The new address-derived owner claims no original container or method name.
Its native STLport vector storage and erase/insert operations reproduce
all 86 bytes with the witnessed unsigned-byte value argument. The retained
callee is the existing typed `_M_fill_insert` at 0074DA00, whose three
arguments, byte read and RET12 agree; the other call is the PE import
MSVCR71.dll!memmove at IAT VA 0135945C. No new pin is required.
The old PartitionManager.cpp remains unchanged, preserving its other
emissions; only its false const-reference identity is retired.
