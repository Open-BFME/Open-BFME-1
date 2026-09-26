// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/nat /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
// stlport

#include "PreRTS.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/PeerThread.h"

// BFME's PlayerInfo has three StringBase<char>-backed strings: the full
// nickname, its display form without the GameSpy suffix, and the locale.  The
// Zero Hour header has only two strings, so this non-constructing layout view
// keeps the retail-only shape local while retaining the real string base.
// Retail's PlayerInfo constructor 0x008F1280 initializes StringBase fields at
// +0/+4/+8, its copy constructor 0x008F1120 copies those same three bases, and
// its destructor 0x008F10B0 releases them in reverse order.  The caller owns
// that lifetime; this helper only assigns into the three already-live bases.
class BFMEPlayerInfoString : private StringBase<char>
{
public:
	BFMEPlayerInfoString &operator=( const char *text )
	{
		StringBase<char>::set( text, text ? strlen( text ) : 0 );
		return *this;
	}
};

class BFMEPlayerInfoLayout
{
public:
	BFMEPlayerInfoString m_name;
	BFMEPlayerInfoString m_baseName;
	BFMEPlayerInfoString m_locale;
	Int m_wins;
	Int m_losses;
	Int m_profileID;
	Int m_flags;
	Int m_rankPoints;
	Int m_bfmeBookkeeping[ 3 ];
	Int m_side;
	Int m_preorder;
};

typedef char BFMEPlayerInfoStringSize[
	sizeof( BFMEPlayerInfoString ) == 4 ? 1 : -1 ];
typedef char BFMEPlayerInfoLayoutSize[
	sizeof( BFMEPlayerInfoLayout ) == 0x34 ? 1 : -1 ];

static void fillPlayerInfo( const PeerResponse *resp, PlayerInfo *info )
{
	BFMEPlayerInfoLayout *bfmeInfo =
		reinterpret_cast<BFMEPlayerInfoLayout *>( info );
	char baseName[ 256 ] = { 0 };
	strncpy( baseName, resp->nick.c_str(), 255 );
	char *suffix = strrchr( baseName, '-' );
	if( suffix )
		*suffix = 0;

	const char *nick = resp->nick.c_str();
	bfmeInfo->m_name = nick;
	bfmeInfo->m_baseName = baseName;
	bfmeInfo->m_profileID = resp->player.profileID;
	bfmeInfo->m_flags = resp->player.flags;
	bfmeInfo->m_wins = resp->player.wins;
	bfmeInfo->m_losses = resp->player.losses;
	const char *locale = resp->locale.c_str();
	bfmeInfo->m_locale = locale;
	bfmeInfo->m_rankPoints = resp->player.rankPoints;
	bfmeInfo->m_side = resp->player.side;
	bfmeInfo->m_preorder = resp->player.preorder;
}

// The retail helper is TU-local and all five calls come from
// WOLLobbyMenuUpdate.  This unclaimed compile anchor preserves MSVC 7.1's
// internal-linkage EBX/ESI argument convention in the split reconstruction.
void WOLLobbyMenuFillPlayerInfoAnchor(
	const PeerResponse *resp, PlayerInfo *info )
{
	fillPlayerInfo( resp, info );
}
