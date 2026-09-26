// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/lanapi /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define BFME_ASCIISTRING_CSTR_CTOR_NOINLINE
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "PreRTS.h"

#define _LANAPI_H_
static const Int g_lanPlayerNameLength = 12;
#define BFME_HOST_DIRECT_CONNECT

inline unsigned short bfmeUnicodeStringLength( const UnicodeString &value )
{
	const unsigned short *data = *(const unsigned short *const *)&value;
	return data ? data[2] : 0;
}

inline UnicodeString::UnicodeString( const WideChar *stringSrc )
{
	((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase( stringSrc );
}

class LANAPI
{
public:
	LANAPI();

	virtual void vfn00( void );
	virtual void vfn01( void );
	virtual void vfn02( void );
	virtual void vfn03( void );
	virtual void vfn04( void );
	virtual void vfn05( void );
	virtual void vfn06( void );
	virtual void vfn07( void );
	virtual void vfn08( void );
	virtual void vfn09( void );
	virtual void vfn10( void );
	virtual void vfn11( void );
	virtual void vfn12( void );
	virtual void vfn13( void );
	virtual void vfn14( void );
	virtual void vfn15( void );
	virtual void vfn16( void );
	virtual void vfn17( void );
	virtual void vfn18( void );
	virtual void vfn19( void );
	virtual void vfn20( void );
	virtual void vfn21( void );
	virtual void RequestGameCreate( UnicodeString gameName, Bool isDirectConnect );
	virtual void vfn23( void );
	virtual void RequestSetName( UnicodeString newName );
	virtual void vfn25( void );
	virtual void vfn26( void );
	virtual void vfn27( void );
	virtual void vfn28( void );
	virtual void vfn29( void );
	virtual void vfn30( void );
	virtual void vfn31( void );
	virtual void vfn32( void );
	virtual void vfn33( void );
	virtual void vfn34( void );
	virtual void vfn35( void );
	virtual void vfn36( void );
	virtual void vfn37( void );
	virtual void vfn38( void );
	virtual void vfn39( void );
	virtual void vfn40( void );
	virtual void vfn41( void );
	virtual void vfn42( void );
	virtual void vfn43( void );
	virtual void vfn44( void );
	virtual void vfn45( void );
	virtual void vfn46( void );
	virtual void vfn47( void );
	virtual void vfn48( void );
	virtual void vfn49( void );
	virtual void vfn50( void );
	virtual void vfn51( void );
	virtual void vfn52( void );
	virtual void vfn53( void );
	virtual void vfn54( void );
	virtual UnsignedInt *GetLocalIP( void );

	void init( void );
	void reset( void );
	void RequestGameJoinDirectConnect( UnsignedInt ipaddress );
	void SetLocalIP( UnsignedInt localIP );
	void RequestLobbyLeave( Bool forced );

	char storage[0x64];
};

#include "NetworkDirectConnect.cpp"
