# 0x0055B200 BfmeAptScreenOnlineQuickMatch::_bfme_sendStartQuickMatchRequest

Extent: 1552 bytes. The primary `ret` is at +0x5EC. Two tail blocks for the
`m_slot78 == 2` and default arms run through +0x60F, and INT3 padding follows.

## Identity

- Caller: the matched OnlineQuickMatch update slot at 0x0055B9A0
  (`BfmeAptScreenOnlineQuickMatchUpdate.cpp`) calls this body through the ILT
  thunk 0x00006D8E, which is pinned in symbols.csv.
- File literal: the `GetGameClientRandomValue` call passes 0x01108E28,
  `F:\bfme\Code\gameengine\Source\GameClient\Gui\GUICallbacks\Apt\AptOnlineQuickMatch.cpp`,
  with line 0x2C0.
- Algorithm: this is the APT port of the matched QuickMatch menu request at
  0x00509B30 (`WOLQuickMatchMenuRequest.cpp`). Both bodies share the following,
  in the same order:
  - a type-0x10 PeerRequest (0x194 bytes);
  - unused UnicodeString/AsciiString locals;
  - maxPing from the ping combo;
  - `findPlayerStatsByID` followed by `CalculateRank`;
  - the ladder lookup and the random-faction side pick;
  - `OptionPreferences::getFirewallBehavior` into QM.NAT;
  - strncpy of the ping string, then botID/roomID and the three GlobalData CRC words;
  - `addRequest`, then the LadderPreferences recent-ladder update.

## Field corrections against the earlier Zero Hour-derived bank

- `this+0x78` is not the firewall behaviour. The retail body stores
  `getFirewallBehavior()` only into the request (+0x130). It writes `this+0x78`
  from a switch on the computed player count: 2 gives 1, 4 gives 2, anything
  else gives 0. It then reloads the value to choose the ladder-rank globals
  0x012B9660/0x012F73D0 (1) or 0x012B9664/0x012F73D4 (2). The matched
  constructor (`OnlineQuickMatchConstructor.cpp`) zeroes the field as `m_slot78`.
- `this+0x5C` is a 4-byte object. The body passes its address as `this` to
  `BfmeC1040::bfmeGo1040C` and `BfmeThingCCH::bfmeGoCCH`, the same way the matched
  `rva005585B0SaveOptions` passes it. The earlier bank's 0x40 + 0x1C split before it
  is kept (m_beforePreferences 0x40 + m_preferences 0x1C).
- The PlayerTemplate view is the matched sibling's 0x124-byte
  `Rva000E1410PlayerTemplate`, with its side at +8. Retail divides the vector span by
  0x124 (magic 0xE070381D, sar 8). The Zero Hour header's `getPlayerTemplateCount`
  would divide by the Zero Hour size.
