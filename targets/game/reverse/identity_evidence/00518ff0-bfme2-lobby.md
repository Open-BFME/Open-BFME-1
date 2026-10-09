# Lobby tab setup donor audit

The assigned Open BFME 2 donor Code/Libraries/Source/Apt/AptActionInterpreterConstantHandlers.cpp at game.dat 0x00700090 prepares an action interpreter and pushes a debug call-stack entry. It does not implement this lobby tab-list algorithm. Its similarity classification is refuted by the complete source and target decode.

The target is a 282-byte thiscall setup(int) body ending in ret 4. The matched caller at 0x0051A5A0 and existing setup pin support the retained Rva0051A5A0Host name. GameWindowManager declarations give registerTabList, clearTabList and winSetFocus slots 0x9C, 0xA0 and 0xB0. Complete push_front and push_back helpers read one four-byte argument and write only node+8 as payload. The 12-byte allocation is not the type evidence. The named canonical list argument and those field writes support GameWindow pointers. Native cleanup jumps through 0x0045F960 to the 66-byte list-base destructor at 0x0045F360.

The preferred bank measures 278 bytes with 196 differences at +0x16. Returning the second window by value supplies the native temporary but emits 288 bytes with 191 differences. Keeping the first member reference live as well emits 283 bytes with 197 differences. Neither restores native ESI receiver and EDI first-field address. EH search removes useful native bookkeeping in its smaller candidates; those are not accepted as progress.

The strict gate fails on bytes and the unbound list<GameWindow*> _M_create_node helper. The owner has paused STL pins, so no pin or ledger row was added. The unchanged preferred bank and all trial sources, decoded extents and raw logs remain under build/r7-apt-worker. Reopening requires evidence for native field liveness or the sanctioned STL header transition.

The exact unbound STL symbol is ?_M_create_node@?@PAVGameWindow@@V?@PAVGameWindow@@@_STL@@@_STL@@IAEPAU?@PAVGameWindow@@@2@ABQAVGameWindow@@@Z.
