// ?rva00699B40RefreshChannel@@YAXH@Z
// partial score=0.984 date=2026-09-24
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
#include "../../Code/GameEngine/Source/Common/Rva00699180Volume.cpp"

extern void *TheAudioClientUpdate;

void rva00699B40RefreshChannel(int b)
{
    if (TheAudioClientUpdate == 0)
        return;

    for (int offset = 0; offset < 0x54C; offset += 0x1C4) {
        Rva00699180Owner *owner = (Rva00699180Owner *)((char *)TheAudioClientUpdate + 0xB8 + offset);
        for (int a = 0; a < 6; ++a) {
            owner->refreshPair(a, b);
        }
    }
}
