# Retail's CommandLineParam table names the command-line handlers

Source: `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`,
image base 0x00400000. Addresses below are RVAs unless written as VAs.

## The table

`.data` 0x00EA6F40 holds twelve `{const char *flag, FuncPtr handler}` pairs and
ends with a zero pair at 0x00EA6FA0. The only code that reads it is
`parseCommandLine` (0x00063BA0, 474 bytes, matched): it loads the table base
at 0x00063BEB and 0x00063C29 and the handler slot (0x00EA6F44) at 0x00063C4D.
Each handler pointer is a 5-byte `E9` incremental-link thunk; the body is the
thunk's jump target.

| entry | flag string | thunk | body | ledger name before | Zero Hour's handler for this flag |
|---|---|---|---|---|---|
| 0x00EA6F40 | 0x00C7520C `-noshellmap` | 0x000428FC | 0x00060880 | `?Rva00060880_parse@@YAHQAPADH@Z` | `parseNoShellMap` |
| 0x00EA6F48 | 0x00C75204 `-mod` | 0x00040070 | 0x000624F0 | `?parseMod@@YAHQAPADH@Z` | `parseMod` |
| 0x00EA6F50 | 0x00C751F8 `-noaudio` | 0x00019CEF | 0x00060A60 | `?Rva00060A60_parse@@YAHQAPADH@Z` | `parseNoAudio` |
| 0x00EA6F58 | 0x00C751F0 `-xres` | 0x00043C3E | 0x00060BC0 | `?parseXRes@@YAHQAPADH@Z` | `parseXRes` |
| 0x00EA6F60 | 0x00C751E8 `-yres` | 0x00026CC4 | 0x00060C10 | `?Rva00060C10_parse@@YAHQAPADH@Z` | `parseYRes` |
| 0x00EA6F68 | 0x00C73910 `-win` | 0x00001F2D | 0x000609C0 | `?Rva000609C0_parse@@YAHQAPADH@Z` | `parseWin` |
| 0x00EA6F70 | 0x00C751D8 `-scriptDebug2` | 0x00030562 | 0x00060CD0 | `?Rva00060CD0_parse@@YAHQAPADH@Z` | none |
| 0x00EA6F78 | 0x00C751C4 `-scriptDebugLite` | 0x00009DA4 | 0x00060D00 | `?Rva00060D00_parse@@YAHQAPADH@Z` | none |
| 0x00EA6F80 | 0x00C751B4 `-fullVersion` | 0x00009C73 | 0x00060B40 | `?parseFullVersion@@YAHQAPADH@Z` | `parseFullVersion` |
| 0x00EA6F88 | 0x00C7519C `-preferLocalFiles` | 0x0002089C | 0x00061DE0 | `?rva00061DE0Set@@YAHXZ` | none |
| 0x00EA6F90 | 0x00C75190 `-Watchdog` | 0x00017490 | 0x00060970 | `?Rva00060970_parse@@YAHQAPADH@Z` | none |
| 0x00EA6F98 | 0x00C75180 `-noWatchdog` | 0x0001FF9B | 0x00060980 | `?Rva00060980_parse@@YAHQAPADH@Z` | none |

Zero Hour's `params[]` in
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/CommandLine.cpp`
pairs `-noshellmap`, `-mod`, `-noaudio`, `-xres`, `-yres`, `-win` and
`-fullVersion` with the handlers in the last column. Retail's table is the
independent witness that the body is the handler for that flag, so those
bodies take EA's names. The five BFME-only flags have no EA handler name
anywhere in the evidence (ZH spells some handlers unlike their flag:
`-fullscreen` is `parseNoWin`, `-fps` is `parseFPSLimit`), so they keep
address-derived names.

## 0x00061050 is parseDumpAssetUsage, not parseWin

The ledger claimed `?parseWin@@YAHQAPADH@Z` at 0x00061050 (19 bytes), from the
ZH-layout `CommandLine.cpp`, whose `m_windowed` is at +0x20. Retail:

    00061050  a1 c8 d5 2e 01   mov eax,[TheWritableGlobalData 0x012ED5C8]
    00061055  85 c0 74 04      test eax,eax / je
    00061059  c6 40 20 01      mov byte [eax+0x20],1
    0006105d  b8 01 00 00 00   mov eax,1
    00061062  c3               ret

- The `-win` entry points at 0x000609C0, which stores 1 to +0x29. Retail's INI
  field table for GlobalData (0x00C77018) gives +0x29 the key `Windowed`
  (its first entry), +0x2C `XResolution` and +0x30 `YResolution`.
- The same INI table's entry at 0x00C770C8 is `{"DumpAssetUsage" (0x00C7C504),
  INI::parseBool (VA 0x00C52E00 = RVA 0x00852E00), 0, 0x20}`: +0x20 is `m_dumpAssetUsage`.
- 0x00061050 is the only retail body with the
  `a1 c8d52e01 85c0 7404 c64020 01` store. Zero Hour's
  `parseDumpAssetUsage` is exactly `if (TheWritableGlobalData)
  m_dumpAssetUsage = true; return 1;`, and it is the only ZH code that assigns that
  member true (besides the INI `parseBool` field).
- ZH defines it between `parseNoFPSLimit` and `parseJumpToFrame`; retail has
  the `parseNoFPSLimit` shape at 0x00061020 and the `parseJumpToFrame` shape at
  0x00061070 on either side of it.
- Its only reference is its own ILT thunk 0x00028A3D. ZH lists
  `-dumpAssetUsage` only under `_DEBUG || _INTERNAL`, so a release table has no
  entry for it.

## BFME1 WorldBuilder's full table

`inputs/baselines/bfme1/workshop-vanilla-1.03/files/worldbuilder.exe` is an
internal build of the same engine. Its CommandLineParam table at RVA
0x00FBB788 has 145 entries, the debug flags included, and its handlers write
the game's GlobalData offsets (`-win` +0x29, `-yres` +0x30, `-seed` +0xAB0,
`-playStats` +0xCCC, as the game's bodies do). Three entries settle the
debug-only handlers the release table omits:

| WorldBuilder entry | handler | store | game body with that store |
|---|---|---|---|
| `-dumpAssetUsage` | 0x0055722B | byte +0x20 = 1, return 1 | 0x00061050 (the only one) |
| `-netMinPlayers` | 0x00557072 | +0xB0C = atoi(args[1]), return 2 | 0x00060F40 (the only one) |
| `-panoramicSlices` | 0x00556B4A | +0xECC = atoi(args[1]), return 2 | 0x00060C60 |

So 0x00061050 is `parseDumpAssetUsage`. ZH pairs `-netMinPlayers` with
`parseNetMinPlayers`, which is therefore 0x00060F40, not 0x00060C60.

## 0x00060C60 is not parseNetMinPlayers

The ledger claimed `?parseNetMinPlayers@@YAHQAPADH@Z` at 0x00060C60 (51 bytes)
on the note "m_netMinPlayers at GlobalData+0xecc". The body stores
`atoi(args[1])` to GlobalData+0xECC when `num > 1` and returns 2.

- No retail table entry points at it; its only reference is its ILT thunk
  0x0001A9E7. The game image has no `-netMinPlayers` or `NetMinPlayers` string.
- WorldBuilder's `-netMinPlayers` handler stores to +0xB0C (above). The +0xECC
  store belongs to `-panoramicSlices`, a BFME flag with no Zero Hour handler,
  so nothing gives its EA function name.
- Retail's INI field table has no key at +0xECC, and `tools/name_oracle.py
  --class GlobalData --offset 0xecc` has no witness.
- In ZH, `parseNetMinPlayers` follows `parseSeed` and `parseIncrAGPBuf`; in the
  game, 0x00060F40 follows the +0xAB0 seed store (0x00060EE0) and a flag setter
  (0x00060F20). 0x00060C60 instead directly follows `parseYRes` (0x00060C10).

The body keeps its address: `?Rva00060C60_parse@@YAHQAPADH@Z`.
