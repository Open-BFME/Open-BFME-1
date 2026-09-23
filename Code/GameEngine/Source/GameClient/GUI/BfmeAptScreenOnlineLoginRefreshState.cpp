// ?_bfme_refreshLoginState@BfmeAptScreenOnlineLogin@@QAEXXZ
//
// OnlineLoginSyncGadgets.cpp calls this body through ILT 0x000371FF from
// _bfme_syncLoginGadgets, which proves the method name.  Constructor 0x005538A0
// places the preferences object at screen offset +0x3C.  The matched constructor
// in GameSpyLoginPreferences_ctor_Thunk.cpp places its three login maps.
// UserPreferences.h defines the base map at +4 and filename at +0x10.  The five
// gadget pointers occupy screen offsets +0x74 through +0x84.
//
// Retail calls 0x0054FF80 with this screen in ECX and two AsciiString
// references on the stack. The helper ends with ret 8, which proves a thiscall
// signature. No evidence names its receiver class, so this source uses
// Rva0054FF80::call for an opaque receiver view.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stringbaseunicode /Ireference/shims/campaignmanagerascii /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include <stddef.h>
#include "Common/AsciiString.h"

#include "Common/UnicodeString.h"

class GameWindow;
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );
bool GetStringFromRegistry( AsciiString path, AsciiString key,
	AsciiString &value );

struct PreferenceNode
{
	unsigned char m_unmodelled[ 0x14 ];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find( const AsciiString &key ) const throw();
	PreferenceNode *end() const { return m_end; }

private:
	PreferenceNode *m_end;
	unsigned char m_unmodelled04[ 8 ];
};

// Constructor 0x005538A0 places this object at screen offset +0x3C.  Its
// UserPreferences base has a 12-byte map at +4 and an AsciiString filename at
// +0x10.  The three login maps start at +0x14, +0x20, and +0x2C.
class GameSpyLoginPreferences
{
public:
	const void *m_vftable;
	PreferenceMap m_preferences;
	AsciiString m_filename;
	unsigned char m_gameSpyMaps[ 0x24 ];
};

class Rva0054FF80
{
public:
	void call( AsciiString &lastEmail, AsciiString &lastName );
};

class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_refreshLoginState();

private:
	const void *m_vftable;
	unsigned char m_unmodelled04[ 0x30 ];
	void *m_context;
	unsigned char m_unmodelled38[ 4 ];
	GameSpyLoginPreferences m_loginPreferences;
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
	GameWindow *m_control80;
	GameWindow *m_control84;
	unsigned char m_unmodelled88[ 0x0D ];
	bool m_needsRefresh;
};

void BfmeAptScreenOnlineLogin::_bfme_refreshLoginState()
{
	if( m_control7C == 0 || m_control74 == 0 || m_control78 == 0 ||
		m_control80 == 0 )
		return;

	GadgetTextEntrySetText( m_control7C, UnicodeString::TheEmptyString );

	AsciiString lastEmail;
	PreferenceNode *it = m_loginPreferences.m_preferences.find(
		AsciiString( "lastEmail" ) );
	if( it != m_loginPreferences.m_preferences.end() )
	{
		const AsciiString *emailValue = &it->m_value;
		lastEmail = *emailValue;
	}
	else
	{
		GetStringFromRegistry(
			AsciiString( (const char *)0x0107301C ),
			AsciiString( "MemberName" ), lastEmail );
	}

	AsciiString lastName;
	it = m_loginPreferences.m_preferences.find( AsciiString( "lastName" ) );
	if( it != m_loginPreferences.m_preferences.end() )
	{
		const AsciiString *nameValue = &it->m_value;
		lastName = *nameValue;
	}

	((Rva0054FF80 *)this)->call( lastEmail, lastName );
	m_needsRefresh = false;
}
