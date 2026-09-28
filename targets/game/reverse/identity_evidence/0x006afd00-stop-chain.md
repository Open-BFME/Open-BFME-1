# MilesAudioManager stop chain banks (0x006ABDA0..0x006AFD00)

The banks for 0x006ADD50 and 0x006AFD00 were replaced on 2026-09-28 by one
chain TU that defines all five MilesAudioManager bodies in retail address
order (0x006ABDA0, 0x006ABFD0, 0x006ADD50, 0x006AE250, 0x006AFD00).

- 0x006ABDA0 is landed as `MilesAudioManager::rva006ABDA0` (source
  game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerStopChain.cpp).
  The old 0x006ADD50 bank called it `advance` and the old 0x006AFD00 bank had
  no such call; the name tool pairs `advance`/`erase` with it only by position.
- The owner of every body is MilesAudioManager: the bodies read the
  constructor-witnessed members (+0x0C AudioSettings, +0x4C request list,
  +0x50 request set, +0x94 vectors, +0x624 flag word, +0x9C8..+0x9D0 lists,
  +0x9D4 deques, +0xAD0 refs, +0xB00 worker; MilesAudioManagerConstructor.cpp).
  The old banks' `StopAudioHandle006AFD00`/`AudioStreamAdvance006ADD50` owners,
  `table_50` blob and `Ref006AFD00` class were stand-ins for those members;
  the refcounted handle is `PlayingAudioRef` (matched stopAudio sibling) and the
  +0x18/+0x0C file handle is the one whose destructor is the matched
  `Rva006910F0Handle::~Rva006910F0Handle` (0x00691130), which the old banks
  reached as `go`.
- 0x006AFD00 in the chain TU probes EXACT (1027/1027 modulo relocations) once
  0x006ADD50 is visible; 0x006ADD50 is 22 scratch-rotation bytes off.
