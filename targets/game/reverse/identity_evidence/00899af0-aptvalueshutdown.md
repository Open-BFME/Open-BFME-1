# 0x00899AF0: AptValueShutdown(int)

## BFME 1 target evidence

- Extent: 297 bytes, `push esi` at 0x00899AF0 through the only `ret` at +0x128,
  then int3 padding (Ghidra FUN_00c99af0 agrees).
- Sole caller: the matched Apt shutdown `dup_00894A90` (0x00894A90,
  `game/Libraries/Source/Apt/AptShutdown00894A90.cpp`) calls it at 0x00894B0A,
  right after its three pool deletes, and pushes its own int argument. The body
  never reads that argument (cdecl `ret`).
- Body: resets the Apt stack (`Gen_008C6BC0::bfmeReset` on 0x01338748); if the
  lazily built table at 0x01337A28 exists, calls its close helper 0x0089C880,
  destroys it through 0x008976E0 and frees 0x10 bytes, then clears the pointer;
  calls virtual slot 2 on seven singletons, frees the 0x3C0-byte block at
  0x01337A04, then calls slot 2 on eight more singletons and zeroes each. Every
  global is one the matched start-up routine `Rva0089BBF0InitGlobals` stores.

## Donor evidence (Open BFME 2 45afcff3a6b2)

- `Code/Libraries/Source/Apt/AptShutdownRva006CFAB0.cpp` is the donor of the
  BFME 1 caller. After the same three pool deletes it calls
  `AptValueShutdown(arg)`, forwarding its int argument.
- `Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp` (BFME 2 0x006DC7C0,
  name from an original MAP file per its header) has the same shape: close and
  pool-delete the native hash, clear it, release value singletons, free the
  rendering-context block of 0x3C0 bytes between them, clear the rest. BFME 2
  calls DestroyGCPointers/Release per singleton; BFME 1's older Apt makes one
  virtual call per singleton and clears only the last eight.

## Inference

Caller position, the forwarded unused int, and the matching teardown sequence
(including the 0x3C0 free) identify the BFME 1 body as the same function. The
singleton classes keep their address-derived names; only the function name is
taken from the donor.
