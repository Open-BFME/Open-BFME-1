// ?W3DGadgetProgressBarImageDrawA@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.995 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetProgressBar.h"
#include "W3DDevice/GameClient/W3DGadget.h"

static inline const Image *BfmeProgressImage(GameWindow *window, Int offset)
{
    return *(const Image **)((char *)window + offset);
}

void W3DGadgetProgressBarImageDrawA(GameWindow *window, WinInstanceData *instData)
{
    ICoord2D origin, size;
    const Image *barCenter, *barRight, *left, *right, *center;
    Int progress = (Int)window->winGetUserData();
    Int i;

    window->winGetScreenPosition(&origin.x, &origin.y);
    window->winGetSize(&size.x, &size.y);

    barCenter = BfmeProgressImage(window, 0x90);
    barRight = BfmeProgressImage(window, 0x84);
    left = BfmeProgressImage(window, 0x48);
    right = BfmeProgressImage(window, 0x54);
    center = BfmeProgressImage(window, 0x60);

    if (!barCenter || !barRight || !left || !right || !center)
        return;

    Int width = barCenter->getImageWidth();
    progress *= size.x;
    Int drawWidth = progress / 100;
    Int pieces = drawWidth / width;
    Int x = origin.x;
    for (i = 0; i < pieces; ++i) {
        TheWindowManager->winDrawImage(barCenter,
                                       x, origin.y,
                                       x + width, origin.y + size.y);
        x += width;
    }
}
