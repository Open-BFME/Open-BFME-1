# Donor extent check

The BFME 1 target begins at RVA 0x008FD930 after five INT3 bytes following the preceding return. Its final return is at RVA 0x008FDE88 and INT3 padding begins at 0x008FDE89. The complete extent is 1369 bytes. Open BFME 2 donor Code/Libraries/Source/WWVegas/WW3D2/ww3d.cpp at game.dat RVA 0x001174F0 has a 1312-byte extent, so the required equal-size premise is refuted.

The donor's D3D9 surface view supplies virtual slots 0x30 and 0x34 and a 32-byte descriptor. The BFME 1 retail uses those same slots. Targa::YFlip is now matched at RVA 0x009E0360, addressing the earlier missing-callee blocker. A complete source experiment adopting the donor surface view and /arch:SSE /G7 emits 1312 bytes against 1369 retail bytes with 1059 non-relocation differences, first at +0x24. The frame matches 0x3F8, but the first switch uses sub eax,1 instead of retail dec eax and its branch destinations differ. The raw probe also reports 31 relocation sites displaced from retail operands. This is a compiler-shape measurement, not a validated linked recovery.

Raw decode, callee inventory, complete candidate, probe output and receipts are preserved under build/donor-port/008fd930-*. The extent conclusion would be refuted by a decoded path returning beyond 0x008FDE88 or entering the trailing padding. No source or ledger replacement is claimed.
