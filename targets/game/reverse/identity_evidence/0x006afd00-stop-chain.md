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

## Landing (2026-09-28, opus-5.5)

- 0x006ADD50 went exact once the +0x624 affect mask became a plain
  `unsigned int` and its bit clear went through a reference alias
  (`unsigned int &bits = flags624; ... bits &= ~bit;`), the spelling the matched
  sibling MilesAudioManagerRva006B86D0.cpp already uses for +0x61C/+0x624.
  The banked `volatile` member reproduced the test-in-memory/reload shape but
  cost one scratch-rotation step (22 bytes).
- The whole chain now lives in
  game/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerStopChain.cpp.
- 0x006ABFD0 and 0x006AE250 are re-homed there from
  game/GameEngine/Source/GameClient/Rva006ABFD0AudioLoop.cpp. Their old
  owners `Rva006ABFD0::go`/`goLoop` (with `Rva006ABFD0Slot`/`Rva006ABFD0Event`
  stand-ins) are the same bodies read through a slot view: the slot's first
  dword is the PlayingAudioRef pointer, +0x0C the PlayingAudio type, +0x14 the
  AudioEventRTS ref and +0x18 the file handle, all on the MilesAudioManager
  layout above; the callee `add` at 0x006ABDA0 is the landed
  `MilesAudioManager::rva006ABDA0`. The event helpers the old TU reached as
  `Rva006ABFD0Event::advance/advanceNextPlayPortion/clamp/hasMoreLoops` are
  AudioEventRTS methods (bfmeGenerateFilename 0x000B4840,
  advanceNextPlayPortion 0x000B3320, 0x000B2860, hasMoreLoops 0x000B28B0),
  so those placeholder pins retire. `Rva006ABFD0File::release` stays: it is
  still called by Rva006A5080ReleaseSlot.cpp.
