// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME5: retail 0x01337818. A loader-zero byte flag in the node walk:
// 0x008D2810 (BfmeNode1236::bfmeActivate1236) tests bit 1, the 0x008BDBB0
// emit pass tests bit 2.
unsigned char g_bfmeExtra1282Flags = 0;
