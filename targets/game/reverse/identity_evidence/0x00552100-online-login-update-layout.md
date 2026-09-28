# BfmeAptScreenOnlineLogin::_bfme_update (0x00552100): record layouts

The old bank (targets/game/reverse/attempts/0x00552100.cpp, score 0.29) modelled
GameSpyGroupRoom with a hole after `m_name` and so put `m_numPlaying` at +0x1C.
It also named screen+0xA8 `m_name` (a `char[4]` this body never reads). The
byte-exact landing (OnlineLoginUpdate.cpp) refutes the group-room layout:

- The GROUPROOM arm builds `GameSpyGroupRoom room` at esp+0x2C (constructor ILT
  0x0001DCC3). At +0x1DF it calls `StringBase<unsigned short>::set` on
  `room + 4` with the `UnicodeString(L"TEST")` temporary, so `m_translatedName`
  is at +4 and no hole follows `m_name` in this record.
- The stores that follow put resp.groupRoom.id at +8, numWaiting at +0xC,
  maxWaiting at +0x10, numGames at +0x14, numPlaying at +0x18, and the BFME
  sixth groupRoom dword (resp+0x108) at +0x1C just before the by-value copy
  (ILT 0x00035F03) into GameSpyInfo::addGroupRoom. The +0x1C field is therefore
  a BFME tail dword, kept under the address-derived name `m_bfme1C`.
- screen+0xA8 is never accessed by this body; the landing leaves it unnamed
  padding (`m_unmodelledA8`) rather than keep an unwitnessed `m_name`.

probe: 1969/1969 bytes, EXACT (modulo relocation slots).
