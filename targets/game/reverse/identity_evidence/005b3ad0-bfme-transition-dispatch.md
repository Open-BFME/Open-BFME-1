# Dispatcher identity and boundary at RVA 0x005B3AD0

The matched caller in `game/GameEngine/Source/GameClient/MessageStream/HotKeyTranslator_translateGameMessage_Thunk.cpp` runs `HotKeyTranslator::translateGameMessage` at RVA 0x005B3F50 and calls `g_bfmeTransitionMD->dispatch`. The pin table in `symbols.csv` maps ILT 0x00048351 to `BfmeTransitionMD::dispatch`.

The `functions.csv` row for `HotKeyManager::executeHotKey` starts at 0x005B3B2A, which is +0x5A inside the dispatcher. Retail control falls through to that address after the dispatcher's exception-handling prologue. The code there reads the original key argument from `[esp+0x90]` after the prologue reserves its frame. The dispatcher returns with `ret 8` at +0x2AC, followed by INT3 padding at +0x2AF, so its full body spans 687 bytes from 0x005B3AD0.
