// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetPushButton.h"
#include "W3DDevice/GameClient/W3DGadget.h"

class BfmeObjEBN;
char bfmeGoEBNb(BfmeObjEBN *object);
void d_00794790(GameWindow *window, WinInstanceData *instData);
void W3DGadgetPushButtonImageDrawOne(GameWindow *window, WinInstanceData *instData);
void W3DGadgetPushButtonImageDrawThree(GameWindow *window, WinInstanceData *instData);

static inline const Image *BfmeMiddleEnabledImage(GameWindow *window)
{
    return *(const Image **)((char *)window + 0x84);
}

static inline Int BfmeImageOffsetX(WinInstanceData *data)
{
    return *(Int *)((char *)data + 0x17c);
}

static inline Int BfmeImageOffsetY(WinInstanceData *data)
{
    return *(Int *)((char *)data + 0x180);
}

void W3DGadgetPushButtonImageDraw(GameWindow *window, WinInstanceData *instData)
{
    if (bfmeGoEBNb((BfmeObjEBN *)window)) {
        d_00794790(window, instData);
        return;
    }

    if (BfmeMiddleEnabledImage(window)) {
        if (BitTest(instData->getState(), WIN_STATUS_USE_OVERLAY_STATES)) {
            ICoord2D size, start;
            window->winGetScreenPosition(&start.x, &start.y);
            window->winGetSize(&size.x, &size.y);
            start.x += BfmeImageOffsetX(instData);
            start.y += BfmeImageOffsetY(instData);
            W3DGadgetPushButtonImageDrawOne(window, instData);
        } else {
            W3DGadgetPushButtonImageDrawThree(window, instData);
        }
    } else {
        W3DGadgetPushButtonImageDrawOne(window, instData);
    }
}
