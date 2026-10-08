// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?preloadAssets@ControlBar@@QAEXW4TimeOfDay@@@Z: game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
#include "PreRTS.h"

// Retail tail-jumps through ILT 0x00027566 to 0x00170460, the matched
// Rva00170460AIStateMachine::clear (Rva00170460AIStateMachine_clear.cpp).
class Rva00170460AIStateMachine
{
public:
	virtual void clear();
};

enum TimeOfDay { TIME_OF_DAY_INVALID = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeManager : public Rva00170460AIStateMachine
{
};

#define bfme_preloadAssets_impl() Rva00170460AIStateMachine::clear()

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
    void bfme_preloadAssets_wrapper();

private:
	char m_pad000[0x30];
	ControlBarSchemeManager *m_controlBarSchemeManager;
};

void ControlBar::bfme_preloadAssets_wrapper()
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->bfme_preloadAssets_impl();
}
