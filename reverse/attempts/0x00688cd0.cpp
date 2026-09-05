// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// partial score=0.35 date=2026-09-05
//
// LANAPI::OnHasMap, 0x00688CD0, 709 bytes -- DRAFT / PARTIAL, not landed.
//
// Identity: matches ZH LANAPI::OnHasMap(UnsignedInt playerIP, Bool status)
// (reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp,
// right before OnGameStartTimer, our landed neighbour at 0x00689050). Callee
// list confirms it: getMap@GameInfo x2 (0x42f28e), findMap@MapCache x1
// (0x419880), WouldMapTransfer x1 (0x4393fb), UnicodeString::format x3
// (0xc89190), StringBase<WCHAR> ctor x3 (0xc88de0). `ret 8` matches two
// stack args (UnsignedInt, Bool).
//
// Reused from the already-landed LANAPIOnGameStartTimer.cpp: LANAPI's BFME
// vtable has OnChat at slot 35 (+0x8c) and getLocalIP as a virtual at slot
// 55 (+0xdc), not the m_localIP member the reference class uses. This body
// needs two more slots off that table: AmIHost() at +0xb8 (slot 46, disasm
// `call [eax+0xb8]` first instruction) and the vfn used at +0x40's target
// (m_currentGame, a plain member here, not virtual).
//
// NOT YET MATCHED. Loop at +0x39 walks m_currentGame+0x88 in 0x68-byte
// strides comparing BOTH a dword (IP) and a word at +4 against the caller's
// [edi]/[edi+4] -- ZH's `getIP(i) == playerIP` is a single dword compare, so
// BFME's LANGameInfo slot struct likely packs a port right after the IP and
// this body checks both; not reproduced below. The tail (GlobalData flag at
// 0x012F4998+0x26c, TheWritableGlobalData->m_pendingFile-shaped writes, two
// MessageBoxInterface-looking calls through 0x12f147c) is sketched from the
// ZH shape only and is very likely wrong; nothing past the loop should be
// treated as identified. Banking this as a compiling skeleton with the
// identity writeup above, not as a byte-match attempt.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef char Bool;
typedef unsigned short WCHAR;
typedef unsigned char UnsignedByte;
enum { TRUE = 1, FALSE = 0 };

template <typename T> class StringBase
{
friend class UnicodeString;
private:
	StringBase( void );
	StringBase( const StringBase<T> &that );
	StringBase( const T *text );
	void releaseBuffer( void );
public:
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( void ) { m_data = 0; }
	const char *str( void ) const { return (const char *)m_data; }
private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString( void ) { m_data = 0; }
	UnicodeString( const WCHAR *text )
	{
		((StringBase<WCHAR> *)this)->StringBase<WCHAR>::StringBase( text );
	}
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<WCHAR> *)this)->StringBase<WCHAR>::StringBase(
			*(const StringBase<WCHAR> *)&that );
	}
	~UnicodeString( void );

	void format( UnicodeString fmt, ... );
	void format( const char *fmt, ... );

private:
	void *m_data;
};

class GameTextInterface
{
public:
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
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapMetaData
{
public:
	UnsignedByte m_unreconstructed_00[8];
	AsciiString m_displayName;			// +0x08, guessed
};

class MapCache
{
public:
	MapMetaData *findMap( AsciiString name );
};

extern MapCache *TheMapCache;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	void setMapAvailability( Bool avail );
};

class GameInfo
{
public:
	UnsignedInt getIP( Int index );
	GameSlot *getLANSlot( Int index );
	AsciiString getMap( void );

	UnsignedByte m_unreconstructed_00[0x88];
	UnsignedByte m_slots[8][0x68];			// +0x88, stride guessed from disasm
};

Bool WouldMapTransfer( AsciiString mapName );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
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
	virtual void vfn22( void );
	virtual void vfn23( void );
	virtual void vfn24( void );
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
	virtual void OnChat( UnicodeString player, UnsignedInt ip, UnicodeString message, Int chatType );
	virtual void vfn36( void );
	virtual void OnGameStartTimer( Int seconds );
	virtual void vfn38( void );
	virtual void vfn39( void );
	virtual void vfn40( void );
	virtual void vfn41( void );
	virtual void vfn42( void );
	virtual void vfn43( void );
	virtual void vfn44( void );
	virtual void vfn45( void );
	virtual Bool AmIHost( void );
	virtual void OnHasMap( UnsignedInt playerIP, Bool status );
	virtual void vfn47( void );
	virtual void vfn48( void );
	virtual void vfn49( void );
	virtual void vfn50( void );
	virtual void vfn51( void );
	virtual void vfn52( void );
	virtual void vfn53( void );
	virtual UnsignedInt getLocalIP( void );

	void lanUpdateSlotList( void );

	UnsignedByte m_unreconstructed_04[0x40 - 4];
	GameInfo *m_currentGame;			// +0x40, confirmed by disasm ([esi+0x40])
};

// ?OnHasMap@LANAPI@@UAEXIH@Z -- DRAFT, not verified against retail bytes.
void LANAPI::OnHasMap( UnsignedInt playerIP, Bool status )
{
	if (!AmIHost())
		return;

	Int i;
	for (i = 0; i < 8; ++i)
	{
		if (m_currentGame->getIP(i) == playerIP)
		{
			m_currentGame->getLANSlot(i)->setMapAvailability(status);
			break;
		}
	}
	if (i == 8)
		return;

	UnicodeString mapDisplayName;
	MapMetaData *mapData = TheMapCache->findMap(m_currentGame->getMap());
	Bool willTransfer = TRUE;
	if (mapData != 0)
	{
		mapDisplayName.format(mapData->m_displayName.str());
	}
	else
	{
		mapDisplayName.format(m_currentGame->getMap().str());
		willTransfer = WouldMapTransfer(m_currentGame->getMap());
	}

	if (!status)
	{
		UnicodeString text;
		if (willTransfer)
			text.format(TheGameText->fetch("GUI:PlayerNoMapWillTransfer"));
		else
			text.format(TheGameText->fetch("GUI:PlayerNoMap"));
		OnChat(UnicodeString((const WCHAR *)L"SYSTEM"), getLocalIP(), text, 2);
	}

	lanUpdateSlotList();
}
