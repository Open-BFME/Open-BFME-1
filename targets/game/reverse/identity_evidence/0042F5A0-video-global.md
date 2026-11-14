# GameClient initialization: VideoPlayer global binding

The ordinary provider in `game/GameEngine/Source/GameClient/VideoPlayer.cpp`
owns the four-byte datum at VA 0x0130B190 as
`?TheVideoPlayer@@3PAVVideoPlayerInterface@@A`. The initialization unit instead
declared the global and its virtual factory result as `VideoPlayer *`.
Its local `VideoPlayer` view added no members to `SubsystemInterface`;
initialization only assigns the factory result, calls inherited `init`, and
sets the subsystem name. Renaming that empty view and the two pointer
declarations to `VideoPlayerInterface` makes the consumer reference the
existing provider. It creates no new object or data definition.

Donor evidence: BFME 2 reference revision f6c3838e7b,
`Code/GameEngine/Source/GameClient/GameClientDrawableTOC.cpp`, declares
`VideoPlayerInterface *createVideoPlayer()` and
`VideoPlayerInterface *TheVideoPlayer` and performs the same initialization.
The donor is statement/type evidence only. BFME 1's own existing provider,
recorded data address and matched caller establish this repair independently.
The already repaired cameo and window movie consumers use the same provider.
No remaining whole-word `VideoPlayer` declaration of `TheVideoPlayer` was
found in the BFME 1 source sweep.

A private before/after object comparison preserves all 2,666 bytes and 196
relocations in the complete initialization body; only references to the old
global spelling become references to the provider's existing spelling.
The native build of the initializer and provider verifies all 9 function rows,
the one data row, 20 string references, 71 DIR32 references and complete
body boundaries. The prior reconstruction record documents its twenty
unwind states; this type-only change preserves the generated instructions.

The census preview at 2026-11-14 12:41 / 1a248a7b47 still reports LINKED 0
bytes for this unit, with independent CloudSystem, animation-sound,
translator and selected-COMDAT blockers. This is a source/global-binding
repair, not evidence of additional linked bytes, a complete link, runtime
behavior, or a crash/memory fix.
