# 0x005770E0 (708 B): BfmeAptScreenScoreScreen::_bfme_populateMultiPlayer names

Matched from `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptScoreScreenPopulateMultiPlayer.cpp`.
Two names in the earlier bank (`targets/game/reverse/attempts/0x005770e0.cpp`, score 0.43) were
replaced. The replacements follow the retail call sites.

- `_bfme_addPlayerTable` -> `Rva00576C20`. The body calls ILT 0x0001355C, which jumps to
  0x00576C20. The ledger already has that body matched as
  `?Rva00576C20@BfmeAptScreenScoreScreen@@QAEXPAVPlayer@@PAVGameSlot@@H@Z`
  (`Rva00576C20.cpp`). No pin or ledger row names it `_bfme_addPlayerTable`, so the bank's spelling
  would not have resolved to the retail target.
- `BfmeScoreEntry::m_object` -> `m_slot`. The entry's first dword is the `GameSlot *` returned by
  `GameInfo::getSlot` (ILT 0x0001EC18 -> 0x0061E8B0). The body stores it at +0 of the entry and
  later passes it as the `GameSlot *` argument of the matched row helper above. The bank typed it
  as an unrelated `BfmeScoreObject *` with a field at +0x18 that the body never reads.
