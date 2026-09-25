// ?update@Rva0076BF20AnimationUpdate@@QAEXXZ
// partial score=0.3525 date=2026-09-24
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Address-qualified owner: the retail body has ECX state but no proven class name.
#include "hanim.h"

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;
extern float g_01076C24;

struct Engine0076BF20 {
    unsigned char unknown00[0x30];
    int mode30;
    unsigned int unknown34;
    float value38;
};
class GameEngine;
extern GameEngine *TheGameEngine;

class Rva0076BF20ObjectBuildRate;
struct ClientObject0076BF20 {
    unsigned char unknown00[0xFC];
    Rva0076BF20ObjectBuildRate *animationStateFC;
};

class Rva0076BF20AnimationUpdate {
public:
    unsigned char unknown00[8];
    ClientObject0076BF20 *object08;
    unsigned char unknown0C[0xD0];
    HAnimClass *animationDC;
    float currentFrameE0;
    float previousFrameE4;
    unsigned char unknownE8[0x68];
    unsigned char enabled150;
    unsigned char unknown151[0xBB];
    float animationValue20C;

    void update();
};

// The indirect target is retail slot +0x10 on the animation's own class.
// Its sole direct predecessor is ILT 0x00028A29, whose body tail-jumps to
// 0x001C3460; that body consumes ECX and returns its float in ST(0).
class Rva0076BF20ObjectBuildRate {
public:
    float member1C3460();
    unsigned char unknown00[0x220];
    float value220;
};
#pragma comment(linker, "/alternatename:?member1C3460@Rva0076BF20ObjectBuildRate@@QAEMXZ=?j_00028a29@@YAXXZ")

void Rva0076BF20AnimationUpdate::update()
{
    if ((enabled150 & 0x10) == 0)
        return;
    if (!animationDC)
        return;
    if (!object08->animationStateFC)
        return;

    if (((Engine0076BF20 *)TheGameEngine)->mode30 == 1)
        animationValue20C = object08->animationStateFC->value220;

    if (animationValue20C == 0.0f) {
        previousFrameE4 = 0.0f;
        currentFrameE0 = 0.0f;
        return;
    }

    Rva0076BF20ObjectBuildRate *buildRate =
        reinterpret_cast<Rva0076BF20ObjectBuildRate *>(
            object08->animationStateFC);
    float nextFrame = buildRate->member1C3460() * ((Engine0076BF20 *)TheGameEngine)->value38
        + animationValue20C * g_01076C24;

    if (g_bfmeDefaultBU < nextFrame)
        nextFrame = g_bfmeDefaultBU;

    int lastFrame = animationDC->Get_Num_Frames() - 1;
    float lastFrameAsFloat = static_cast<float>(lastFrame);
    float frameLimit = lastFrameAsFloat * nextFrame;
    if (lastFrameAsFloat < frameLimit)
        frameLimit = lastFrameAsFloat;

    if (frameLimit > currentFrameE0) {
        float oldFrame = currentFrameE0;
        currentFrameE0 = frameLimit;
        previousFrameE4 = oldFrame;
    }
}
