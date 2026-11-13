# Cameo movie player global binding

BFME1's data ledger owns the pointer at VA 0x0130B190 as
`?TheVideoPlayer@@3PAVVideoPlayerInterface@@A` in
`game/GameEngine/Source/GameClient/VideoPlayer.cpp`.
The 273-byte cameo body at RVA 0x00441AF0 reads that address but
declared the global with a different pointee type, yielding the
undefined `?TheVideoPlayer@@3PAVVideoPlayer@@A` symbol.

Declare the existing owner type and cast the pointer to this unit's
retail-proven video interface view at the virtual call. The private
comparison keeps all 273 bytes and every other relocation. Its one
video pointer relocation now names the data ledger's actual provider.
The normal provider/consumer build passes all nine function rows
and the pointer's four-byte data row. The established interface view
keeps BFME1's open-call slot at +0x30.

BFME2 donor reviewed at f6c3838e7b:
`Code/GameEngine/Source/GameClient/InGameUIPlayCameoMovie.cpp`
already declares the VideoPlayerInterface global. BFME2's open slot
is different, so its layout is not imported. The BFME1 address, data
row, ABI and bytes independently establish this repair.

Reference refresh on 2026-11-13 moves the tracked donor pointer from
76f0baefa6 to official master f6c3838e7b. The prior local checkout was
2bac16a657. The updated donor checkout is clean. Relevant video and
ASCII dependency changes were inspected, and the BFME1 provider and
consumer were verified before and after the source repair with the
same native build inputs. The donor remains an evidence reference.
