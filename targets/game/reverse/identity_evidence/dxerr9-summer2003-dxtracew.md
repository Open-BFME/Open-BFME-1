# Summer2003 DXErr9: DXTraceW source reconstruction

`_DXTraceW@20`, RVA 0x00AFD20F, 377 B (functions.csv row previously sourced from the
vendored `inputs/vendor/dxerr9/dxerr9.lib` member `obj\i386\dxerr9.obj`).

## BFME 1 target facts (archive and retail image)

- The original archive (sha256 `07f40f6799edceffb1d9532a5a42d1e8177bbf5a60f5e1b0c9975b9c2cfcb1b5`)
  defines the public `_DXTraceW@20` alone in `.text` section 8198 (377 B, COMDAT NODUP,
  23 relocations, associative `.debug$F` 8208). Outside its 23 relocation operands the section
  equals retail at 0x00AFD20F; the next byte (0x00AFD388) starts `_DXTraceA@20`.
- ABI: `ret 0x14`, stdcall, five 32-bit arguments: narrow file name, line, HRESULT, wide
  message, BOOL popup flag. The frame is 0x2374 bytes allocated through `__chkstk`
  (0x009F6C60): wide line[128] at ebp-0x100, narrow file[260] at ebp-0x204, wide
  error[256] at ebp-0x404, wide message[1024] at ebp-0xC04, wide buffer[3000] at ebp-0x2374.
  No GS cookie, no EH, no frame bias (`push ebp; mov ebp,esp`).
- The Summer2003 entry point keeps the file name narrow: the popup copies it with
  `StringCopyWorkerA` (0x00A2A893, the D3DX-owned copy retail selected) and shows it with
  `%S`, while the debug-output line formats it with `%s`, as the shipped literal says.
- Calls, by relocation: 5x `StringCchPrintfW` (0x00AFD1E8), 2x `StringCopyWorkerA`,
  2x `StringCopyWorkerW` (0x00AD5401), `DXGetErrorString9W` (0x00AE6855), `__chkstk`;
  imports `OutputDebugStringW` (IAT 0x01358EAC, cached in esi), `MessageBoxW`
  (0x01359040, NULL owner, flags 0x14, IDYES 6 -> `DebugBreak` 0x01358D08).
- Literals read from retail: L"%ld" 0x011BA0BC, L"%s(%s): " 0x011BA0A8,
  L"%s (0x%0.8x)" 0x011BA08C, L" (hr=%s)" 0x011BA078, L"\n" 0x01084C10,
  L"File: %S\nLine: %s\nError Code: %s\nCalling: %s\nDo you want to debug the application?"
  0x011B9FD0, L"Unexpected error encountered" 0x011B9F94, L"" 0x01088AF4, "" 0x0107301C.

## Compiler evidence

- Native object: `.debug$S` names `D:\BUILDS\NT32_FRE\multimedia\directx\misc\dxerr9\daytona\obj\i386\dxerr9.obj`
  and an S_COMPILE record of 13.00.9176 (front end) / 13.00.9178 (back end); `@comp.id`
  0x001D23DA (prodid 0x1D = Utc13_CPP, build 9178). Not the project's 13.10.3077.
- Even so, MSVC 13.10.3077 `/O1 /G6 /MT /DNDEBUG` (the flags of the four lookup TUs and
  strsafe.cpp) reproduces all 377 bytes: tools/probe.py EXACT, and a private compile emits the
  same 23 relocation symbols as the native section (9 literal DIR32, 11 REL32, 3 import
  DIR32). `/Oxs` and `/O1 /Oi` are also exact; `/O2` and `/Ox` give 418 B.
- Normal admission (`add_match.py --replace-existing`, same name/RVA/extent): 1/1 matched,
  7 literals + 2 empty-string refs verified, 3 DIR32 references checked.
  `tools/import_binding.py check` PASS for this TU (strict link imports only what retail
  imports, from the same DLLs).
- Contrast for the sibling `_DXTraceA@20` (not part of this landing): `/O1`, `/Oxs` and
  `/O1 /Oi` leave the banked tracea-blocked.cpp.txt at 369 B with no `lea ebp,[esp-0x64]`
  bias; growing only its 128-byte line buffer past disp8 reach makes 13.10 emit the native
  biased frame. Records: the DXTrace lane's
  `targets/game/reverse/attempt_support/dxerr9-summer2003/tracea-bias-heuristic-20261117.md`
  (which also banked a DXTraceW candidate, `tracew-candidate.cpp.txt`, exact like this one)
  and `member-retirement-plan-20261117.md` beside it.

## Donor and structure

The readable structure follows Microsoft DXUT `Core/dxerr.cpp` (MIT; see
`game/Libraries/Source/DirectX/license.dxut.txt`) and the BFME 1 DXTraceA bank
(`targets/game/reverse/attempt_support/dxerr9-summer2003/tracea-blocked.cpp.txt`).
BFME 2 `Code/Libraries/Source/DirectX/dxtracew.cpp` at 0630f0ef47d0a818bb2e97583b43cfb1ecd35491
is an August2005 variant (message length check, `GetForegroundWindow`, `%S(%s): `, `hr=%s`,
/O1 /G7 /hotpatch /Oy- /GS): a structural lead only; none of its differing literals or calls
are used.
