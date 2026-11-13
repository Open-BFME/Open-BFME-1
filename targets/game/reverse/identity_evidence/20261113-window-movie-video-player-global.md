# Window movie player global binding

The matched 253-byte WindowVideoManager::playMovie body at RVA
0x004991D0 reads the video player at VA 0x0130B190. Its existing
local call view already specifies the witnessed virtual slot and
native AsciiString argument ABI. The declaration of TheVideoPlayer
used the unrelated VideoPlayer pointee name, leaving the external
symbol undefined.

BFME1's data ledger owns that four-byte pointer in VideoPlayer.cpp
as VideoPlayerInterface*. Change the forward declaration and global
declaration to that owner type. The existing cast to the receiver
view at the virtual call stays valid. The private object comparison
preserves all 11 ledger rows in this unit and changes only the one
video-player data relocation in playMovie. The provider/consumer
build verifies 19 function rows and the data row.

This follows the verified cameo binding in commit 4f0a4bd61d.
The BFME2 reference at f6c3838e7b was inspected at
Code/GameEngine/Source/GameClient/GUI/window_video_manager.cpp.
Its video open/attach sequence is the already recorded donor lead;
BFME1's pointer ownership and bytes establish this repair. No
BFME2 address or virtual layout is transplanted.

The census d1c221c3d8 reports zero linked bytes for this unit.
Independent container COMDATs, a duplicate playMovie provider and
the manager vtable remain separate blockers.
