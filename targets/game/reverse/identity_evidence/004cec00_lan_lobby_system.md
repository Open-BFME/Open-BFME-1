# LAN lobby system callback at RVA 0x004CEC00

The old `?setStartingCash@LANPreferences@@` claim is misidentified.

Independent retail identity evidence (retail-1.03-unpacked):
- The FunctionLexicon row at VA 0x012A9504 contains the name pointer 0x010876F0 (the NUL-terminated literal `LanLobbyMenuSystem`) and function pointer 0x00441CC2.
- That ILT entry has bytes `E9 39 CF 48 00`, a jump to VA 0x008CEC00 (RVA 0x004CEC00).
- The body switches over window messages and references `LAN:ErrorNoGameSelected` and `Menus/NetworkDirectConnect.wnd`, agreeing with the Zero Hour LanLobbyMenuSystem in GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/LanLobbyMenu.cpp.
- Zero Hour LANPreferences::setStartingCash instead formats a Money value and writes the StartingCash preference. This body does neither.

The replacement uses the existing callback declaration and C++ body in LanLobbyMenu.cpp, with BFME message IDs, witnessed LAN virtual slots, the six-byte zeroed network-address argument (retail +0x193 and +0x654), and native StringBase accessors. The 1686-byte extent ends in RET at +0x695.

Model: gpt-6-astra-medium.
