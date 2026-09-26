// ?_bfme_acceptLocale@BfmeAptScreenOnlineLogin@@QAEXPBD@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// AptOnline::Login::AcceptLocale callback.  The registration in the retail
// OnlineLogin constructor at 0x005538A0 stores this method under that exact
// action name and the 0x0001EC77 ILT reaches retail 0x005533F0.

#include "PreRTS.h"

#include "Common/GameSpyMiscPreferences.h"

class GameWindow;

void GadgetListBoxGetSelected( GameWindow *window, int *selected );
void *GadgetListBoxGetItemData( GameWindow *window, int row, int column );

class WindowManager
{
public:
	void add( void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3 );
};

// This is the existing 0x00049E1D ICF route used by the OnlineLogin
// singleton's tail action.  The retail global slot is read as
// TheBfmeOnlineLogin; the matched destructor proves that singleton type, while
// constructor 0x005538A0 remains a retail/banked boundary rather than a landed
// constructor claim.  Retail 0x00552C40 consumes one BYTE argument, and its
// two OnlineLogin writers at 0x00553520 and 0x005536F0 call ILT 0x00049E1D
// with 0/1 before storing the same bool state at this+0x9F.
extern WindowManager *g_theWindowManager;

struct BfmeOnlineLoginContext
{
	unsigned char m_unmodelled[ 0x250 ];
	void *m_window;
};

class BfmeAptScreenOnlineLogin
{
public:
	// OnlineLogin's registered callbacks receive one const-char pointer
	// argument; this callback ignores it, as do the matched link callbacks.
	void _bfme_acceptLocale( const char *argument );
	void rva00552C40( bool argument );

private:
	const void *m_vftable; // constructor 0x005538A0 installs 0x01107F58
	unsigned char m_unmodelled04[ 0x30 ];
	BfmeOnlineLoginContext *m_context; // retail [this+0x34]
	unsigned char m_unmodelled38[ 0x50 ];
	GameWindow *m_localeList; // retail [this+0x88]
	unsigned char m_unmodelled8C[ 0x13 ];
	bool m_closeLocaleArgument; // retail [this+0x9F]
	unsigned char m_unmodelledA0[ 4 ];
	int m_locale; // retail [this+0xA4]
};

void BfmeAptScreenOnlineLogin::_bfme_acceptLocale( const char * )
{
	int selected = -1;
	GadgetListBoxGetSelected( m_localeList, &selected );
	if( selected >= 0 )
	{
		m_locale = (int)GadgetListBoxGetItemData( m_localeList, selected, 0 );
		GameSpyMiscPreferences preferences;
		preferences.setLocale( m_locale );
		preferences.write();
	}
	else
	{
		*(unsigned char *)0x012F4AB0 = 1;
	}

	g_theWindowManager->add( m_context->m_window,
		"CallChild", 1, (void *)"DoCloseLocale", 0, 0, 0, 0 );

	(*(BfmeAptScreenOnlineLogin **)0x012F4AAC)->rva00552C40( m_closeLocaleArgument );
}
