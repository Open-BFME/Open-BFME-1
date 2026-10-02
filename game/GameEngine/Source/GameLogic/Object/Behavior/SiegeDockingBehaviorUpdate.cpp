// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameLogic/Module/UpdateModule.h"

// Update-interface receiver at complete-object +0x10. Existing field view
// and helper identities are retained; see identity_evidence/update-slot0.md.
class BfmeHostERP
{
public:
    void bfmeSweepERP();
};

class BfmeThingCFD
{
public:
    unsigned char m_bfmeHead[0x20];
    bool m_bfmeFlag;
};

class SiegeDockingBehavior
{
public:
    void initializeBones00206CB0();
    virtual UpdateSleepTime update();
};

UpdateSleepTime SiegeDockingBehavior::update()
{
    BfmeThingCFD *state = reinterpret_cast<BfmeThingCFD *>(this);
    if (!state->m_bfmeFlag)
    {
        reinterpret_cast<SiegeDockingBehavior *>((char *)this - 0x10)->initializeBones00206CB0();
        state->m_bfmeFlag = true;
        return UPDATE_SLEEP(5);
    }
    reinterpret_cast<BfmeHostERP *>((char *)this - 0x10)->bfmeSweepERP();
    return UPDATE_SLEEP(5);
}
