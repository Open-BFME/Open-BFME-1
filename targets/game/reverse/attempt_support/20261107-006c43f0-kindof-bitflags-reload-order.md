# 0x006C43F0 radar object-list renderer: EXACT via BitFlags kind tests (2026-11-07)

Landed as `?renderObjectListRva006C43F0@W3DRadar@@IAEXPBVRadarObject@@PAVW3DRadarResetTexture@@H@Z`, 1296 B, in `game/GameEngineDevice/Source/W3DDevice/Common/System/W3DRadar_renderObjectList.cpp`. It replaces the MASM row `W3DRadar_renderObjectList.asm`. Identity and naming evidence: `targets/game/reverse/identity_evidence/0x006c43f0-radar-render-object-list.md`.

## Starting point
The bank (`targets/game/reverse/attempts/0x006c43f0.cpp`, score 0.9969) was 1296 B with 4 non-relocation diffs at +0x394.

After the first circle loop exits, retail reloads `longest` (`mov edi,[esp+24h]`) before `yDoubled` (`mov ebx,[esp+30h]`). The bank reloaded them in the reverse order.

More than 200 earlier trials changed nothing (see re_attempts.log). They covered:
- declaration order and loop forms
- types and scopes
- flags and permutations
- rotation sweeps and named temporaries

## Method
1. A private disassembler classified only the three instructions after the loop-1 back edge. That made it possible to sort even variants that change size.
2. A cut-down function holding only the circle block already had retail's order. The order therefore depends on context elsewhere in the body.
3. Deletion bisection: removing any one of these flipped the order:
   - the whitening branch
   - the four-pixel branch
   - the `!disguised` skip block
   - only the `getRadarPriority()` term
4. Seven re-spellings of the priority test changed nothing, and neither did up to 12 identity-inline wrappers on `obj`.

## Fix
Write the two ThingTemplate kind tests (bits 119 and 89 of the 192-bit mask at +0xC8) as the inline `BitFlags<192>::test -> bitset::test` chain instead of open-coded masks. Any of these is EXACT:
- applying it to either test alone
- a free inline wrapper
- a cast view
- calling `m_kindof.test` directly

## Landing notes
- The third parameter is a packed Color. A `bool` with the recorded `Rva006C0890(Color, Color)` callee costs 325 diffs (movzx). The old `_N` decoration was therefore wrong. `ilt_oracle` contradicts every renderObjectList decoration tried, so the row carries its address.
- The four rva helpers are kept as static, visible TU copies. Their ledger rows stay in their own TUs.
- 0x012ED600 is referenced as `TheNameKeyGenerator`, pinned at the same address as `TheBfmeGenAE`.
- Helper and COMDAT copies were probed against their own rows: all retail-identical (0x006C42B0, 0x006C2A20, 0x006C2DD0, 0x006C1D00, 0x006C43A0, 0x00087A80, 0x00083400, 0x00098E50, 0x006C1BB0, 0x000C3C30).
