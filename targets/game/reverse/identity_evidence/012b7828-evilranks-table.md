# Evil rank-label table at VA 0x012B7828

The decorated identity `?g_rva012B7828EvilRanks@@3PAPBDA` (C++
`const char *g_rva012B7828EvilRanks[11]`) owns 44 bytes at VA 0x012B7828
in retail `.data`: eleven dwords pointing at `Wizard`, `Scum`, `Vermin`,
`Beast`, `Goblin`, `Orc`, `MountainTroll`, `Berserker`, `DarkWizard`,
`RingWraith`, `DarkLord` (read via `reloc_ledger.Image.read`).

- Defined in
  `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/Rva005307B0ChatPlayerTooltip.cpp`,
  indexed by `AptOnlineCustomMatch::MpOwnerUpdatePlayerTooltip` through
  `g_rva012B7828EvilRanks[rank]` with rank in [0, 10].
- Payload is identical, in order, to the landed Evil table at VA
  0x012B7B08 (`?RankLabels00554510Evil@@3PAPBDA`) and to the table at VA
  0x012B8018. Every pointee is a pooled MSVC 7.1 compiler literal
  (`??_C@...` symbols); the existing `symbols.csv` pins bind them to the
  retail pointee VAs, so the rebuilt object's relocations resolve to
  exactly the retail targets.
- The name is address-derived; no original EA identifier is established.
  The label content agrees with the BFME 2 donor's evil rank table
  (`open-bfme-2 Code/GameEngine/Source/GameNetwork/RankPointValue.cpp`).

## Extent and all users

`sizeof` 44 bytes at VA 0x012B7828 as proven by the data gate. The next
retail dwords are zero. Sole DIR32 consumer is
`MpOwnerUpdatePlayerTooltip` in Rva005307B0ChatPlayerTooltip.cpp.
