// ?init@W3DGameWindowManager@@UAEXXZ
// partial score=0.35 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "W3DDevice/GameClient/W3DGameWindowManager.h"

struct W3DGameWindowManagerInitLayout
{
    unsigned char pad[0x524];
    ICoord2D first[4];
    ICoord2D second[4];
    ICoord2D third[4];
};

void W3DGameWindowManager::init(void)
{
    GameWindowManager::init();

    W3DGameWindowManagerInitLayout *layout =
        reinterpret_cast<W3DGameWindowManagerInitLayout *>(this);

    ICoord2D *p;
    for (p = layout->first; p != layout->second; ++p)
        *p = ICoord2D();
    for (p = layout->second; p != layout->third; ++p)
        *p = ICoord2D();
    for (p = layout->third; p != layout->third + 4; ++p)
        *p = ICoord2D();
}
