// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame
// stlport
// StealthUpdate's secondary-interface wrapper and BFME FX transitions.
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <bitset>
#include "GameEngine/Source/GameLogic/Object/object.h"
#include "GameEngine/Source/GameClient/FXListRetail.h"

#include "GameEngine/Include/Common/Module.h"
#include "GameEngine/Include/GameLogic/Module/UpdateModule.h"
#include "Common/BitFlags.h"
class BfmeXCQE { public: char bfmeKindCQE(); };
class Gen_00411DD0 { public: void bfmeSet(bool); };
class StealthUpdateModuleData {
public:
    char m_pad000[0x40];
    FXList *m_becomeStealthedFX;
    FXList *m_exitStealthFX;
    FXList *m_becomeStealthedOneRingFX;
    FXList *m_exitStealthOneRingFX;
};
class StealthUpdate : public UpdateModule {
public:
    virtual UpdateSleepTime update();
    UpdateSleepTime rva002AD670();
protected:
    void changeVisualDisguise();
private:
    unsigned m_stealthAllowedFrame;
    unsigned m_detectionExpiresFrame;
    unsigned m_nextBlackMarketCheckFrame;
    Bool m_enabled;
    Bool m_restoring2D;
    Bool m_rva002ADFB0_02E;
    Bool m_rva002ADFB0_02F;
    Bool m_rva002ADFB0_030;
    char m_pad031[3];
    int m_disguiseAsPlayerIndex;
    const ThingTemplate *m_disguiseAsTemplate;
    unsigned m_disguiseTransitionFrames;
    Bool m_disguiseHalfpointReached;
    Bool m_transitioningToDisguise;
    Bool m_disguised;
    Bool m_xferRestoreDisguise;
};

// ?update@StealthUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime StealthUpdate::update()
{
    if (m_xferRestoreDisguise == true) {
        Drawable *draw = getObject()->getDrawable();
        Bool wasHidden = false;
        if (draw && ((BfmeXCQE *)draw)->bfmeKindCQE())
            wasHidden = true;
        changeVisualDisguise();
        draw = getObject()->getDrawable();
        if (wasHidden && draw)
            ((Gen_00411DD0 *)draw)->bfmeSet(true);
    }
    UpdateSleepTime result = rva002AD670();
    Object *self = getObject();
    if (m_rva002ADFB0_02E != ((const BitFlags<86> *)self->m_status)->test(15)) {
        if (!m_rva002ADFB0_030) {
            if (m_rva002ADFB0_02E) {
                if (m_rva002ADFB0_02F)
                    FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_exitStealthOneRingFX, self, 0);
                else
                    FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_exitStealthFX, self, 0);
            } else {
                if (m_restoring2D)
                    FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_becomeStealthedOneRingFX, self, 0);
                else
                    FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_becomeStealthedFX, self, 0);
            }
        }
        m_rva002ADFB0_02E = ((const BitFlags<86> *)self->m_status)->test(15);
        m_rva002ADFB0_02F = m_restoring2D;
    } else if (m_rva002ADFB0_02F != m_restoring2D) {
        if (((const BitFlags<86> *)self->m_status)->test(15)) {
            if (m_rva002ADFB0_02F) {
                FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_exitStealthOneRingFX, self, 0);
                FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_becomeStealthedFX, getObject(), 0);
            } else {
                FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_exitStealthFX, self, 0);
                FXList::doFXObj(((const StealthUpdateModuleData *)getModuleData())->m_becomeStealthedOneRingFX, getObject(), 0);
            }
        }
        m_rva002ADFB0_02F = m_restoring2D;
    }
    m_rva002ADFB0_030 = false;
    return result;
}
