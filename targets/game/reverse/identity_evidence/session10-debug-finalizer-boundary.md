# Preserve the assertion finalizer code-and-table boundary

The 948-byte row at RVA 0088B530, ?finishAssert0088B530@Debug@@QAE_NH@Z, was flagged by the whole-ledger linear decoder because its last table bytes decode as ENTER reaching into padding. The actual instruction stream is 917 bytes ending after CALL [013592C4] at 0088B8BF..0088B8C4. The PE import directory identifies that address as MSVCR71.dll!_exit, which does not return. The ordinary return path ends with RET 4 at 0088B7A7..0088B7A9 and is wholly inside the claimed span.

A three-byte LEA ECX,[ECX] alignment instruction at 0088B8C5 precedes the owned switch table at 0088B8C8..0088B8E3. CMP EAX,6 at 0088B6FB and JA default at 0088B70B bound the seven-entry table used by JMP [EAX*4+00C8B8C8] at 0088B70D. Its seven VA targets are 00C8B777,00C8B714,00C8B71E,00C8B77E,00C8B73B,00C8B77E,00C8B7AA. All target decoded instructions in the 917-byte stream; every direct branch also targets an instruction inside that stream. INT3 padding starts at 0088B8E4 and the next body starts at 0088B8F0. No other matched row intersects the 948-byte span.

Local retail PE/Capstone and Ghidra read_memory at VA00C8B8A0 independently agree. The complete existing native source passes the ordinary scoped build and the reviewed complete-string, float-constant and DIR32-reference checks. This is a boundary clearance, not a new identity claim: preserve its source, inherited name, ledger extent and separately documented debugger-trap codegen rationale.

Rule: docs/matching.md requires exact byte verification. A table interpreted as instructions is not evidence of executable truncation. The extent candidate is CLEARED; no baseline or detector changes.
