# writeLANGameInfo 0x0068E090 (1037 B) — fresh rewrite, session 491

Bank: `targets/game/reverse/attempts/0x0068e090.cpp` (replaces the 2026-09-10
0.62-author bank, which probed 1403 B / 883 diffs and had the bounds test
inverted: `end && ...` where retail writes when `!end || (p <= end && p + n <= end)`).

New probe: 1008 B vs 1037, 721 non-reloc diffs, shape 0.707, frame `sub esp,0x10`
and EH layout already retail's. model=claude-opus-5-5, /DNDEBUG /MD /EHsc with
`-Igame/Libraries/Source/WWVegas/WWLib` (canonical string_base.h/ascii_string.h;
TheNullChr resolves to 0x0107388B, the wide empty string to the
BFMEEmptyUnicodeString data row 0x0107388C).

## Retail structure (verified from the listing)

- `if (!buffer) return; memset(buffer,0,size); if (!game) return;` (inline rep stos)
- `AsciiString mapName; mapName = _Rva00621170MapPathHelperConcat(game->getMap(), true);`
  (states 0/1/2, set@StringBase<char>, two temp releases)
- `cursor = rva68d730(buffer, mapName.str(), end)`; then ntohs(+0x48) word,
  htonl(+0x40), htonl(+0x44), htonl(+0x4C) dwords.
- 8-slot loop, **unsigned** index (`jb`): human 'P' + 26-byte copy of
  `UnicodeString(slot->getName().str(), 12)` (scoped: released before the IP),
  htonl ip(+0x30), ntohs port(+0x34), flags byte `(+8!=0)|((+9!=0)<<1)`, bytes
  +0x0C,+0x14,+0x10,+0x18,+0x38; AI: E/M/H from state 2/3/other, then +0x0C,+0x14,+0x10,+0x18;
  else state 0 'O', 1 'C', otherwise (and null slot) 'X'.

## Measured levers

- Word writer: volatile-union spill (Rva0068D5A0EmitPort shape) reproduces the
  `mov [esp+N],eax ... mov ax,[esp+N]` store. `const T&` template loses it.
- `int __stdcall ntohs(unsigned short)` plus `template<T> writeNetWord(char*, T, char*)`
  gives retail's straight `push eax` for the Int header field AND the
  `xor eax,eax; mov ax,[edi+0x34]` port load (int param -> movzx; u_short return -> movzx).
- if-block vs early returns, function-scope index, cursor reusing `buffer`,
  extra block around the map assignment: all byte-identical (no effect).

## Remaining wall (register / frame-slot allocation)

- /FAsc: ours gives the dead `buffer` arg slot (+12) to `mapName`; retail gives
  it to {helper-result temp, header word temp, loop index} and puts mapName at
  the lowest frame slot. Same five slot groups otherwise.
- Retail keeps `game` in EBX across the header and loop (reloaded from the arg
  only at the end of the human arm) and the cursor in ESI, so each inlined
  write in the human arm rotates the cursor register (esi->ebx->esi->ecx->eax),
  giving the `jbe; mov out,in; jmp` failure tails. Ours spills `game` and keeps
  the cursor in one register. Retail also keeps the entry zero in EDI for the
  first `cmp ebp,edi` limit test.
- Untested ideas: change reference weights so the index group outweighs
  mapName (e.g. mapName as a block local after the header writes is NOT
  possible: retail constructs it before getMap); different helper spellings
  for the human arm only.
