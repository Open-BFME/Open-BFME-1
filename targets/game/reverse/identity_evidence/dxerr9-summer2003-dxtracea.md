# DXErr9 Summer 2003 `_DXTraceA@20` (0x00AFD388, 374 B)

Source: `game/Libraries/Source/DirectX/dxtracea.cpp`. Lane w48 DXTRACE round 2,
claude-opus-5-5, 2026-11-17.

## Identity and extent (BFME 1 target evidence)

- The vendored archive `inputs/vendor/dxerr9/dxerr9.lib` (Summer 2003, see its
  PROVENANCE) defines the public symbol `_DXTraceA@20` in member `obj\i386\dxerr9.obj`
  as one 374-byte NODUP `.text` section with 22 relocations. That member section was
  this row's matched owner, equal to retail at 0x00AFD388 outside relocation operands.
- ABI: `ret 0x14`, five stack dwords read at `[ebp+8..0x18]` (unbiased) as file name,
  line, HRESULT, message and a full-word BOOL; returns the HRESULT argument.
- Frame 0x123C through `__chkstk`; buffer counts pushed: 0x80 (line), 0x100 (error),
  0xBB8 (output), 0x104 (popup file name), 0x400 (popup message).
- Literals, read from the retail image: `%ld` 0x0112F770, `%s(%s): ` 0x011BA158,
  `%s (0x%0.8x)` 0x011BA148, ` (hr=%s)` 0x011BA13C, `\n` 0x01080294, empty string
  0x0107301C, `File: %s\nLine: %s\nError Code: %s\nCalling: %s\nDo you want to debug the
  application?` 0x011BA0E8, `Unexpected error encountered` 0x011BA0C4.
- Calls (`tools/callees.py 0x00AFD388 374`): `?StringCchPrintfA@@YAJPADIPBDZZ` 0x00AFD1C1
  x5, `?StringCopyWorkerA@@YGJPADIPBD@Z` 0x00A2A893 x4, `_DXGetErrorString9A@4`
  0x00AD548E, `__chkstk` 0x009F6C60; imports through IAT slots 0x01358EA8
  (OutputDebugStringA, cached in ESI), 0x0135903C (MessageBoxA), 0x01358D08 (DebugBreak).

## Source provenance

- Readable structure: Microsoft DXUT `Core/dxerr.cpp` (MIT, `license.dxut.txt`), as in
  the 2026-11-12 bank (`attempt_support/dxerr9-summer2003/tracea-blocked.md`). Its later
  length check, `GetForegroundWindow` and literals are not Summer 2003 behaviour and are
  not used.
- BFME 2 donor `0630f0ef47d0` `Code/Libraries/Source/DirectX/dxtracea.cpp` (read only)
  supplied the unit name; its August 2005 body and DDK compiler settings were not used.

## Compiler context

The member's `@comp.id` is 13.00.9178; this unit compiles with BFME 1's MSVC 13.10.3077
`/O1 /G6 /MT /DNDEBUG`, the flags of the other DirectX units. 13.10 does not bias this
frame from the plain body (369 B). The unit therefore carries a frame lever: a
never-written `long frameBiasSlot[33]` that 13.10 packs with the line buffer into one
132-byte slot, the popup file buffer declared 256 bytes so the other buffers keep their
retail addresses (the slot's lowest four bytes complete its 260), and the return value
read as `frameBiasSlot[37]`, which is the HRESULT argument slot. Measured rule, probes and
the closest variants: `attempt_support/dxerr9-summer2003/tracea-bias-model-20261117.md`.
The lever is a code-generation device, not a claim about the original source (DXUT,
like any plain reading of retail, returns `hr` and declares a 260-byte file buffer).
