# 0x006A9200 bank rewrite: names replaced

The 2026-09-28 bank of 0x006A9200 is a whole-body rewrite on the
MilesAudioManager layout. It replaces four names from the earlier stash.
None of those names had evidence behind it:

- `BfmeThingTED::bfmeOneTED`: the stash took this name from the ILT pin at
  0x0003E045, which the matched caller BfmeConv1310.cpp declares on its own
  placeholder class. The owner is MilesAudioManager: two other callers,
  `setHardwareAccelerated` (0x006A9910) and `rva006B86D0`, are matched
  MilesAudioManager methods, and the body uses the manager's +0x94/+0x9BC/
  +0x9C8..+0x9D0/+0x9D4 members. No symbol names the method, so it keeps the
  address token as `MilesAudioManager::rva006A9200`.
- `releasePlayingAudio`: the callee at ILT 0x0002669D is pinned in
  targets/game/reverse/symbols.csv as
  `?rva006A59F0@MilesAudioManager@@QAEXPAVPlayingAudio@@@Z`. The rewrite uses
  that callee contract rather than a Zero Hour guess.
- `m_soundType` on AudioEventRTS+0x28: nothing witnesses this name.
  `tools/name_oracle.py --class AudioEventRTS --offset 0x28` reports the
  offset unwitnessed, and its Zero Hour hint there is `m_timeOfDay`. The
  rewrite keeps an offset name, `m_28`.
- `m_pointer` on the reference class: the rewrite uses the PlayingAudioRef
  class of the matched sibling MilesAudioManagerStopAudio.cpp, whose member
  is spelled `m_ptr`.
