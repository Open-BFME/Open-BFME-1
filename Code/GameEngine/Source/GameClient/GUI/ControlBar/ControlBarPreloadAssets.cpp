// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?preloadAssets@ControlBar@@QAEXW4TimeOfDay@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp
#include "PreRTS.h"

enum TimeOfDay { TIME_OF_DAY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeManager
{
public:
	void bfme_preloadAssets_impl();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
    void bfme_preloadAssets_wrapper();

private:
	char m_pad000[0x30];
	ControlBarSchemeManager *m_controlBarSchemeManager;
};

// ?bfme_preloadAssets_wrapper@ControlBar@@ absent-from-retail
void ControlBar::bfme_preloadAssets_wrapper()
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->bfme_preloadAssets_impl();
}
