# 0x000F4F30 Team::updateState: the create-gate callee is not Team::isIdle

The retired bank (`targets/game/reverse/attempts/0x000f4f30.cpp`) ported the
Zero Hour create block and called `isIdle()` where retail calls ILT
0x00008A71 -> body 0x000F4E20. That body is not Team::isIdle:

* Team::isIdle is already landed at 0x000EDB30
  (`game/GameEngine/Source/Common/RTS/Rva000EDB30TeamIsIdle.cpp`), proven by
  the matched AIPlayer::checkReadyTeams call through ILT 0x0003A143; it walks
  the members and asks each AIUpdateInterface slot 96 (+0x180) isIdle.
* 0x000F4E20 (214 bytes) never calls AI slot 96. It returns true at once when
  the byte at Team+0xE6 is clear, then walks the members testing Object+0x90
  bit 4, the final ThingTemplate +0xD4 bit 0x1000, and the contain module's
  slot 26 result through its slots 84 (+0x150), 39 (+0x9C) and 38 (+0x98).

Its semantic name is not proven, so the landed source
(`game/GameEngine/Source/Common/RTS/Team_updateState.cpp`) keeps the
address-derived `Team::rva000F4E20`, pinned in symbols.csv.
