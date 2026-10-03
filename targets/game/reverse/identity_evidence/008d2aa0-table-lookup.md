# Opaque method at RVA 008D2AA0

Retail table VA 011362C8 slot 10 (cell VA 011362F0) contains VA 00CD2AA0.
The existing matched Rva89A6E0Derived constructor at 0089A6E0 stores this
table at 0089A745. Ghidra and baseline confirm both cells and all 56 body
bytes through RET8 at 008D2AD5, followed by INT3. The body leaves its ECX
receiver and first stack argument unused, uses the second stack argument,
and returns EAX. The owner and method remain opaque; no Apt semantic name
is inferred from lookup behavior.

`callees.py 0x008D2AA0 56` reports two calls to 0089CEF0. The ledger's
`?d_0089cef0@@YAXXZ` is a dump name with no real signature; its inferred ABI
is thiscall, one stack slot, EAX result. Independent full 520-byte baseline
decoding confirms ECX saved in EDI; the incoming stack slot is dereferenced
as a pointer to a key word; normal results come from entry +4, with low bit
cleared, and the miss result is zero. All return paths pop four bytes
(0089D0A0/0089D0BA/0089D0E9/0089D0F5). Ghidra corroborates the prologue and
return paths. Existing `BfmeTab1024::bfmeFind1024(int)` is the matching 32-bit
ABI view already used by native Rva00899C20NodePredicate.cpp; pin_consistency
reports its sole address 0089CEF0 consistent. No new alias or callee pin is
introduced, and its inherited label is not asserted to be a recovered name.

The four caller relocations are two calls to this same body and loads of
VA 0133846C (`g_bfmeMap1024`) and VA 013387D8 (`g_Va013387D8`). Both are
already recorded in dir32_addresses.csv, and both table receivers add eight.
The fallback occurs for a zero primary result or clear bit 15 in result +4.
Narrowing the complemented shifted flags to unsigned char preserves retail's
SHR/NOT CL/TEST CL sequence; a direct boolean bit test instead emits TEST CH.
Strict native-source verification must independently check all four references.
