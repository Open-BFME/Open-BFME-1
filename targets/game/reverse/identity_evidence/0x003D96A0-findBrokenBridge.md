# Correct identity at RVA 0x003D96A0

The matched `AISkirmishPlayer::checkBridges` caller invokes `Pathfinder::findBrokenBridge` through ILT jump stub `0x0001DFE8`. The pin list in `targets/game/reverse/symbols.csv` maps that stub to `0x003D96A0`.

The old `clientSafeQuickDoesPathExistForUI` lift starts at `0x003D96A3`, three bytes into the retail body. Retail starts at `0x003D96A0` with `sub esp, 0x14`, returns at `0x003D9817`, and reaches INT3 padding at `0x003D981A`. The old source emits the next 375 bytes with `__emit`, and `tools/callers_of.py 0x003D96A3` finds no named caller.

The new C++ body matches all 378 bytes from the entry at `0x003D96A0`. The old row therefore claimed an inner byte range as a separate function.
