// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// LANAPI::OnGameStartTimer, 0x00689050, 222 bytes.
//
// Two prior verdicts closed this row. The first blamed the LANAPI vtable and
// was right about it; the second fixed the vtable, reached 222 of 222 bytes,
// and closed the row on "EH-frame store scheduling" -- retail saving the
// temporary into the EH record BEFORE loading `this` (`mov [esp+N],esp` then
// `mov ecx,esp`) where the build emitted the pair reversed. That second
// diagnosis is wrong, and the flag sweep behind it could never have found the
// real cause because it is not a flag question: it is INLINE VISIBILITY of the
// constructor. With UnicodeString's converting and copy constructors merely
// DECLARED, MSVC emits a plain out-of-line call and orders the two stores its
// own way; with them DEFINED INLINE as forwarders to a private
// StringBase<WCHAR> base constructor -- the shape the real string classes
// actually have -- the `this` load comes out of the inlined body and lands
// after the EH store, exactly as retail. Both temporaries built for the OnChat
// call needed it; the earlier fetch() site is genuinely out of line and keeps
// retail's other order.
//
// The vtable facts from the earlier passes are kept and hold: LANAPI's retail
// vtable has 56 slots, BFME has five more virtuals before OnChat than Zero Hour
// so OnChat is slot 35 (0x8c) not 0x78, and the local IP is read through a
// virtual at slot 55 (0xdc) rather than as the m_localIP member the reference
// uses. Declared locally at retail slots rather than through the shim header:
// nothing outside this file needs the layout, and a header change runs the
// full gate.
//
// The other BFME-vs-reference difference is the same one processDisconnectChat
// found: UnicodeString::format takes its format string BY VALUE as a
// UnicodeString, which is what puts an EH-registered temporary at the fetch
// call at all.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef char Bool;
typedef unsigned short WCHAR;

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
	virtual void vfn46( void );
	virtual void vfn47( void );
	virtual void vfn48( void );
	virtual void vfn49( void );
	virtual void vfn50( void );
	virtual void vfn51( void );
	virtual void vfn52( void );
	virtual void vfn53( void );
	virtual void vfn54( void );
	virtual UnsignedInt getLocalIP( void );
};

void LANAPI::OnGameStartTimer( Int seconds )
{
	UnicodeString text;
	if (seconds == 1)
		text.format(TheGameText->fetch("LAN:GameStartTimerSingular"), seconds);
	else
		text.format(TheGameText->fetch("LAN:GameStartTimerPlural"), seconds);
	OnChat(UnicodeString(L"SYSTEM"), getLocalIP(), text, 2);
}
