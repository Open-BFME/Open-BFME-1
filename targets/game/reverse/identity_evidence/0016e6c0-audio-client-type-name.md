# 0x0016E6C0 startMoveSound: helper type name BfmeStartMoveSoundAudio -> Rva005A00B0AudioClient

The banked attempt targets/game/reverse/attempts/0x0016e6c0.cpp declared a TU-local
struct `BfmeStartMoveSoundAudio` for the object behind `TheAudioClientUpdate`, through
which the body calls vtable slots +0x44 (addAudioEvent) and +0x4C (removeAudioEvent).
That name was a local label invented for one unlanded stash; no evidence named the class.

The landed source uses `Rva005A00B0AudioClient`, the address-derived name this
repository already gives the same object: 27 source files on origin/master declare
`Rva005A00B0AudioClient` for `TheAudioClientUpdate` with the same vtable (0x0111C0C0)
and the same +0x44/+0x4C slot pair (e.g. Rva0051BCE0ShellMusicTrigger.cpp,
MilesAudioManagerIsCurrentlyPlaying.cpp). The change converges on the established
identity; it does not replace a proven name with a placeholder.
