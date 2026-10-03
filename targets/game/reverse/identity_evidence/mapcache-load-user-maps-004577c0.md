# MapCache::loadUserMaps: complete EH body

Retail-1.03-unpacked; RVAs below (image base 0x00400000). Independently
inspected with Ghidra 12.1.2 via pyghidra-mcp and raw retail bytes.

- Matched MapCache::updateCache (0x00457E70) and getDefaultMap (0x00457FB0)
  call ILT 0x00028FF1, whose E9 displacement reaches 0x004577C0. Their
  source calls loadUserMaps. The ZH MapUtil.cpp algorithm agrees throughout.
- The parent establishes EBP and FS:[0], saves EBX/ESI/EDI, and allocates
  0x994 stack bytes. Its handler RVA 0x00C242DB loads FuncInfo 0x0121448C
  (VA), magic 0x19930520, maxState 15, and one TryBlockMap at VA 0x01214478.
- That TryBlockMap is {tryLow=5, tryHigh=5, catchHigh=6, nCatches=1,
  pHandlerArray=0x01214468}. The catch-all HandlerType contains a null type
  and its handler VA 0x008578E0 at VA 0x01214474. Ghidra reports this DATA
  xref as the only incoming reference to the alleged getter.
- 0x004578DE is EB 0B, a jump to 0x004578EB, not the end of a function.
  The six bytes at 0x004578E0 are B8 E6 78 85 00 C3: the empty catch funclet
  returns its continuation VA 0x008578E6. At that continuation, 8B 7D DC
  reloads EDI from the parent's EBP frame and 33 DB restores zero in EBX.
- 0x004578EB destroys the parent's local AsciiString and INI, then continues
  the same map traversal. Ghidra's separate decompilation requires unaff_EBP,
  unaff_EDI and unaff_EBX, independently ruling out a callable helper.
- Both return paths restore FS:[0], EDI/ESI/EBX and EBP. The last RET is at
  0x00457D0D, followed by INT3 padding. Thus [0x004577C0,0x00457D0E) is
  1358 bytes; the old 288-byte inventory prefix is not a standalone body.

## Callee contracts

The bank already matches all 1358 instruction bytes; prior addMap blockage
is resolved by its verified body at 0x004570F0 (ILT 0x00012FC1, ret 0x10).
No new candidate pins are needed. The existing byte-valued map operator[]
at 0x004545A0 is reached via its retained char ABI: it initializes the byte
at node+0x14. Char versus bool identity remains explicitly unproven there.
The erased tree at 0x00077340 recursively visits node+0x0C, destroys the
AsciiString key at +0x10, and frees 0x18-byte nodes before following +8.
The caller passes the root on the stack and its tree in ECX. A typed view
calls its existing address-named ILT 0x0000DB2A without adding an alias pin.

The recovered source keeps the known m_seen offset +0x0C. A 1358-byte
explain_mismatch check resolves every relocation and reports exact bytes.
The false constant-getter row is retired, and the named five-byte ILT is
retained as MapCacheLoadUserMapsThunk::loadUserMaps so the real method name
belongs to its complete implementation.
