# `map<string, int>::operator[]` at 0x0064E690 (not `map<AsciiString, Coord3D>`)

Retail 0x0064E690 (229 B) is STLport `map<basic_string<char>, int>::operator[]`.
The ledger's `map<AsciiString, Coord3D>::operator[]` claim at the same address
is wrong; every typed callee and both matched callers prove the native
`string`/`int` contract.

## Callee contracts (retail image, slot -> body, verified 2026-09-30)

The body makes six direct calls; the first three fix the key/value types:

- `0x00027381 -> 0x00645870`: `_M_lower_bound` of
  `Rb_tree<basic_string<char>, pair<const basic_string<char>, int>>`
  (matched row in `PingThread.cpp`, 132 B).
- `0x00015898 -> 0x006451D0`: `operator<(const basic_string&, const
  basic_string&)` (matched row in `PingThread.cpp`, 98 B). An
  `AsciiString` key would call the `StringBase` comparison instead.
- `0x0001CB11 -> 0x004FB1B0`: `basic_string<char>::basic_string(const
  basic_string&)` (matched row in `stlport_narrow_string_copy_ctor.cpp`,
  86 B). An `AsciiString` key would copy through `StringBase<char>`.
- `0x0003AFEE -> 0x0064CBD0`: hinted `insert_unique`; the native
  `string`/`int` instantiation compiles to retail's exact 628 bytes
  (`tools/probe.py` EXACT modulo relocs, 22 relocs).
- `0x00881EB0 operator delete`, `0x0082E5F0 node deallocate`: type-neutral.

Value width corroborates: the miss path zeroes one dword (`mov [esp+0x18],
ebx` after `xor ebx,ebx`) -- one `int`, not three `float`s -- and both
`&node->second` returns use `+0x1C` (12-byte `basic_string` key at `+0x10`
plus 4-byte `int`), not the `+0x14` a 4-byte `AsciiString` key would give.

## Caller contracts (matched rows)

- `0x0064E7B0 PeerThreadClass::trackStatsForPlayer` (matched,
  `PeerThreadTrackStatsForPlayer.cpp`) declares `PlayerStatMap =
  std::map<std::string, Int>` members at `+0x94`/`+0xA0` and calls ILT
  `0x00017ADF -> 0x0064E690` twice, once per map.
- `0x006615B0 Pinger::addResponse` (matched, `PingThread.cpp`) declares
  `std::map<std::string, Int> m_pingMap` at `+0x74` and calls ILT
  `0x00017ADF -> 0x0064E690`; its source line `m_pingMap[resp.hostname] =
  resp.avgPing` names the instantiation, and `PingResponse::hostname` is
  `std::string` per upstream `PingThread.h`.

## Boundary

`[0x0064E690, 0x0064E775)`, 229 B: Ghidra end `ret 4` at `+0xE2` plus the
found-path `ret 4` tails; `int3` padding follows. The replacement preserves
this proven extent.
