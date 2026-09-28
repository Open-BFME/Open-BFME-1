// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "basetype.h"
// RVA 0x006C1280: 210-byte six-argument thiscall ending ret 0x18.
// Opaque owner: the precise BFME event-method identity is not established.
// The 80-byte record and animation table offsets are direct retail witnesses.
// Projection mirrors the landed W3DRadar::radarToPixel at 0x006C0ED0.
// Client slot 26 returns the unsigned frame; the animation draw ILT
// 0x00030DB9 routes to the landed 0x005BAAB0 four-int thiscall.

class Rva005BA9E0Anim2D
{
public:
    void draw(int, int, int, int);
};

class Rva006C1280Client
{
public:
#define SLOT(N) virtual void slot##N();
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6)
    SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
    SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18)
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25)
#undef SLOT
    virtual unsigned getFrame();
};

extern Rva006C1280Client *TheGameClient;

struct Rva006C1280Event
{
    int type;
    unsigned field04, frame;
    char pad0c[0x34];
    ICoord2D radarLoc;
    char pad48[8];
};

class Rva006C1280
{
public:
    char pad00[0x28];
    Rva006C1280Event events[64];
    char pad1428[0x88];
    Rva005BA9E0Anim2D *images[16];

    void method(int, int, int, int, int, int);

    void radarToPixel(const ICoord2D *radar, ICoord2D *pixel,
        int x, int y, int w, int h)
    {
        if (!radar || !pixel)
            return;
        pixel->x = radar->x * w / 128 + x;
        pixel->y = (127 - radar->y) * h / 128 + y;
    }
};

void Rva006C1280::method(int x, int y, int w, int h, int i, int unused)
{
    Rva006C1280Event *event = &events[i];
    int type = event->type;
    unsigned frame = TheGameClient->getFrame();
    int size = (int)((1.0f - (float)(frame - event->frame) / 45.0f) *
        (w * (2.0f / 3.0f)));
    if (size < 16)
        size = 16;

    ICoord2D pixel;
    radarToPixel(&event->radarLoc, &pixel, x, y, w, h);
    int px = pixel.x - size / 2;
    int py = pixel.y - size / 2;
    images[type]->draw(px, py, size, size);
}
