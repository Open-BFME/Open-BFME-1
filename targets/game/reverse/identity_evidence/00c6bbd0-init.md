# Replace ?d_00c6bbd0@@YAXXZ scaffold with ?Rva00C6BBD0Init@@YAXXZ (object-symbol=_$E1)

Retail 0x00C6BBD0 (27B): `push 0x011051E0; mov ecx,0x012F4978; call j_00012c42; push 0x010701C0; call _atexit; pop ecx; ret`.
Push literal is "GuiFX.apt" (retail .rdata bytes); DIR32 0x012F4978 = ?g_guiFxFile@@3VAsciiString@@A,
defined as `AsciiString g_guiFxFile("GuiFX.apt");` in
game/GameEngine/Source/GameClient/GUI/AptGuiFXRegisterCallbacks.cpp (only definition in tree;
all other TUs extern-declare it); j_00012c42 reaches AsciiString(const char*), 0x010701C0 its dtor
forwarder. Defining the global in that TU emits COFF _$E1 (probe EXACT, 27/27B). The ledger name
keeps the address token; object-symbol names the emitted COFF body the verifier compares.
