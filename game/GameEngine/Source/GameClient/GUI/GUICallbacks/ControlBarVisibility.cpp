// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/scriptenginelayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define ASCIISTRING_H
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "PreRTS.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/ControlBar.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"

inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template <> inline const char *StringBase<char>::str() const {
    return m_data ? m_data->data : "";
}

class BFMEWindowManagerVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *parent, int id ) = 0;
};

class BFMEViewVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void setHeight( int height ) = 0;
};

class BFMEDisplayVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual int getHeight() = 0;
};

class AptPalantir
{
public:
	void hide( bool immediate );
};

class BannerUI
{
public:
	void hide( bool immediate );
};

extern void hideReplayControls();
extern ControlBar *TheControlBar;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern void *TheTacticalView;
extern void *TheDisplay;
extern AptPalantir *TheAptPalantir;
extern BannerUI *TheBannerUI;

void HideControlBar( bool immediate )
{
	hideReplayControls();
	if( TheControlBar )
		TheControlBar->hideSpecialPowerShortcut();

	if( TheWindowManager )
	{
		int id;
		{
			AsciiString name( "ControlBar.wnd:ControlBarParent" );
			id = TheNameKeyGenerator->nameToKey( name.str() );
		}
		GameWindow *window = reinterpret_cast<BFMEWindowManagerVTable *>( TheWindowManager )->winGetWindowFromId( 0, id );
		if( window )
		{
			reinterpret_cast<BFMEViewVTable *>( TheTacticalView )->setHeight(
				reinterpret_cast<BFMEDisplayVTable *>( TheDisplay )->getHeight() );
		}

		if( immediate )
		{
			if( window )
				window->winHide( true );
			if( TheControlBar )
				TheControlBar->hideSpecialPowerShortcut();
		}
		else if( TheControlBar )
		{
			if( TheControlBar->m_animateWindowManager )
				TheControlBar->m_animateWindowManager->reverseAnimateWindow();
			TheControlBar->animateSpecialPowerShortcut( false );
		}

		if( TheControlBar )
			TheControlBar->hidePurchaseScience();
	}

	if( TheAptPalantir )
		TheAptPalantir->hide( true );
	if( TheBannerUI )
		TheBannerUI->hide( true );
}

// The BFME mode transition is separately matched at 0049E5A0. Its member
// is absent from the upstream ControlBar declaration, so this narrow view
// retains the address until the shared header can carry its declaration.
class Rva0049E5A0View {
public:
    int transition();
    int mode() const { return word2EC; }
    char opaque0[0x2EC];
    int word2EC;
};
// Vtable010F6F2C slot10 -> ILT0002848E -> reset0045DAB0.
// BFME inserted loadIniFilesFromLegend before postProcessLoad.
class Rva004C0E10AnimationView {
public:
    virtual void slot0();
    virtual void slot4();
    virtual void slot8();
    virtual void slotC();
    virtual void reset();
};
class Glo012F4B98Type;
extern Glo012F4B98Type *Glo012F4B98;
extern void showReplayControls();
// name_oracle witnesses ControlBar::m_UIDirty at +24.
struct Rva004C0E10DirtyView { char opaque0[0x24]; bool m_UIDirty; };

// Retail 004C0E10 and named ScriptActions callers agree with ShowControlBar.
// Mode +2EC is BFME-specific; the original header's member at that offset
// is unrelated. Only mode 2 marks the control-bar UI dirty.
void ShowControlBar(bool immediate)
{
    HideControlBar(true);
    if (reinterpret_cast<Rva0049E5A0View *>(TheControlBar)->mode() == 0)
        reinterpret_cast<Rva0049E5A0View *>(TheControlBar)->transition();
    switch (reinterpret_cast<Rva0049E5A0View *>(TheControlBar)->mode()) {
    case 1:
        if (Glo012F4B98)
            reinterpret_cast<AptPalantir *>(Glo012F4B98)->hide(false);
        if (TheBannerUI)
            TheBannerUI->hide(false);
        break;
    case 2:
        showReplayControls();
        if (TheControlBar)
            TheControlBar->showSpecialPowerShortcut();
        if (TheWindowManager) {
            int id;
            {
                AsciiString name("ControlBar.wnd:ControlBarParent");
                id = TheNameKeyGenerator->nameToKey(name.str());
            }
            GameWindow *window = reinterpret_cast<BFMEWindowManagerVTable *>(TheWindowManager)->winGetWindowFromId(0, id);
            if (window) {
                TheControlBar->switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
                reinterpret_cast<BFMEViewVTable *>(TheTacticalView)->setHeight(
                    (int)((unsigned int)reinterpret_cast<BFMEDisplayVTable *>(TheDisplay)->getHeight() * 0.80f));
                if (TheControlBar->m_animateWindowManager && !immediate) {
                    reinterpret_cast<Rva004C0E10AnimationView *>(TheControlBar->m_animateWindowManager)->reset();
                    TheControlBar->m_animateWindowManager->registerGameWindow(
                        window, WIN_ANIMATION_SLIDE_BOTTOM, true, 500, 0);
                    TheControlBar->animateSpecialPowerShortcut(true);
                }
                window->winHide(false);
            }
        }
        if (TheControlBar)
            reinterpret_cast<Rva004C0E10DirtyView *>(TheControlBar)->m_UIDirty = true;
        break;
    }
}
