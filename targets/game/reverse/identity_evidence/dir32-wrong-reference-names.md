# References renamed because retail's operand names something else

The DIR32 consistency gate (build.py `verify_dir32_consistency`) found each of
these: one symbol that resolved to two retail addresses. The byte check masks
DIR32 operands, so each of these rows still "matched". In every case below, the
bytes retail pushes or loads identify a different object from the descriptive
name the source used. Each side now has its own name.

## Bink MMX rounding table (Rva009C6390/66F0/6780BinkMmx.cpp)

- The MMX paths `paddw`/`paddsw` from VA 0x012D88D0, a 64-bit table.
  Twelve rows already call it `Rva012D88D0Round`, in Rva009C6620BinkMmx.cpp and
  others.
- `g_bfmeBinkRound` is the SSE table at 0x012D8C00; all 12 SSE rows resolve
  it there.
- The MMX files keep the address-derived name that already covers 0x012D88D0.

## LAN lobby tooltip (LanLobbyMenu_init.cpp)

- `LanLobbyMenuInit` (0x004CF440) installs VA 0x008CE850 as the players-listbox
  tooltip, at +0x5D2.
- The descriptive `playerTooltip` is WOLLobbyMenu's own function at 0x004FA800
  (a matched row, which WOLLobbyMenuInit installs). LanGameOptionsMenu's is a
  third, TU-static body at 0x004CB220.
- The LAN lobby body at 0x004CE850 is still the unconverted dump `d_004ce850`,
  so the reference names that dump rather than pointing at WOL's function.

## OptionGroup parse table (OptionGroup.cpp)

`parseOptionGroup` (0x000945A0) stores four parse procs. They are not INI's
scalar parsers, which live at 0x00851EE0/0x00852E00/0x00852A60/0x00852B20.
Each is an ILT thunk to the named-definition parser beside the function:

| Entry | Retail VA | Thunk target | Matched row |
|---|---|---|---|
| Bool (+0x54) | 0x0042FAB8 | 0x000940F0 | `?parseDefinition@Rva000940F0@@SAXPAVINI@@PAX1PBX@Z` |
| Int (+0x6C) | 0x0042FA45 | 0x000941D0 | `?parseDefinition@Rva000941D0@@SAXPAVINI@@PAX1PBX@Z` |
| String (+0x84) | 0x004097EB | 0x00094300 | `?parseDefinition@Rva00094300@@SAXPAVINI@@PAX1PBX@Z` |
| Real (+0x9C) | 0x00425496 | 0x00094470 | `?parseDefinition@Rva00094470@@SAXPAVINI@@PAX1PBX@Z` |

Each of these parsers reads a name token and then a value. That is what an
OptionGroup body holds.
