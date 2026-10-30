# OnlineProfile rank-label tables at VA 0x012B7AE0 / 0x012B7B08

The matched 957-byte callback `?rankTooltip00554510@@YGXPBD@Z`
(`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineProfileRankTooltip00554510.cpp`)
indexes two narrow-string pointer tables defined in the same TU. Both keep the
name already spelled by the matched consumer; no original EA identifier is
established.

## Retail extents

- `?RankLabels00554510Good@@3PAPBDA`, retail `.data` VA `0x012B7AE0`, 40 bytes
  (ten dwords). Slot 0 is `0x00000000`; slots 1..9 point at `Peasant`, `Page`,
  `Squire`, `Knight`, `RoyalGuard`, `CaptainOfTheGuard`, `HighLord`, `Prince`,
  `King`. The extent is bounded by the adjacent Evil table beginning at
  `0x012B7B08` (0x28 later).
- `?RankLabels00554510Evil@@3PAPBDA`, retail `.data` VA `0x012B7B08`, 44 bytes
  (eleven dwords). The payload is `Wizard`, `Scum`, `Vermin`, `Beast`,
  `Goblin`, `Orc`, `MountainTroll`, `Berserker`, `DarkWizard`, `RingWraith`,
  `DarkLord`. The extent is bounded by the adjacent eight-pointer
  image-path table beginning at `0x012B7B38`.

The Evil payload is byte-identical to the independent eleven-entry table at
`0x012B8018` (data_rows row for `?g_012B8018@@3PAPBDA`).

## Consumer facts

The callback's object carries DIR32 references to exactly these bases:
Good at `+0x255` (base `0x012B7AE0`) and Evil at `+0x23a` (base `0x012B7B08`).
The Gondor/Rohan branches scan `rank=1..10` against
`TheRankPointValues->m_ranks[1..9]` and then read `Good[rank]`; at the maximum
rank 10 that read is out of the ten-slot Good extent and lands on the Evil
table's first slot (`Wizard`) in the retail layout. The body is byte-matched,
so the OOB read is preserved as retail behavior and not corrected.

## Shared literal pool

Every pointee is a pooled MSVC 7.1 compiler literal (external `??_C@...`
symbols, one `.rdata` section each); the arrays carry DIR32 (0x6)
relocations to them. All twenty literals are the same pointees the sibling
rank tables at `0x012B7DAC`, `0x012B7DD4` and `0x012B8018` reference; their
`symbols.csv` pins (e.g. `??_C@_07OBCPDMEM@Peasant?$AA@` at `0x00C7FE98`,
home `0x0107FE98`) bind them to the retail addresses, and the rebuilt object's
relocation targets resolve through those pins to exactly the retail pointee
VAs (build/rank_obj_verify.py).

## Donor corroboration

The open-bfme-2 donor `Code/GameEngine/Source/GameNetwork/RankPointValue.cpp`
defines good/evil rank-label arrays with the same label contents (its good
array is `NoRank, Peasant, ..., King, Wizard`; its evil array is the
eleven-entry set beginning at `NoRank`). The donor layout differs (static
arrays, NoRank slot); the content agreement corroborates the label meaning
only.
