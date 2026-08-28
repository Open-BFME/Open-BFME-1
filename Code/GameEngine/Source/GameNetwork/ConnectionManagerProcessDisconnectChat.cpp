// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// ConnectionManager::processDisconnectChat, 0x006655C0, 255 bytes.
//
// Identity is not a guess: the message pointer is handed to
// ConnectionManager::getPlayerName (already pinned at ILT 0x00012A62) with
// `this` in ecx, and the body then formats "[name] text" and posts it to a
// DisconnectMenu global -- which is exactly the reference's
// processDisconnectChat and nothing else in the class.
//
// A previous attempt got all 255 bytes and all control flow right and stopped
// on two reversed pairs: retail saves the temporary's address into the EH
// record BEFORE loading `this` (`mov [esp+N],esp` then `mov ecx,esp`) and we
// emitted them the other way round. That was logged as EH-frame store
// scheduling, i.e. a compiler blocker. It is NOT. It is inline visibility: with
// the constructor declared but not defined, MSVC emits a plain out-of-line call
// and schedules the two stores its own way; with the constructor DEFINED inline
// as a forwarder to a private base constructor -- which is how the real
// AsciiString/UnicodeString pair is actually built -- the `this` load comes out
// of the inlined body and lands after the EH store, matching retail. Both
// temporaries here (the by-value format string and the copy handed to showChat)
// needed it.
//
// The other BFME-vs-reference difference is in the signature: BFME's
// UnicodeString::format takes the format string BY VALUE as a UnicodeString,
// not as a const WCHAR *, which is why a UnicodeString temporary is constructed
// into the argument slot at all.
//
// Both the name and the text are unnamed temporaries, not the reference's two
// named locals: retail evaluates msg->getText() first, then getPlayerName(),
// which is right-to-left argument order inside the format call, and destroys
// them in the reverse order immediately after it. The reference's
// `if (playerID == m_localSlot) ... else if (isPlayerConnected...)` chain is
// gone from BFME entirely -- getPlayerName does that work now.
//
// Declared locally at retail offsets rather than through a header: nothing
// outside this file needs the layout, and a header change would run the full
// gate.

typedef int Int;
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

	const WCHAR *str( void ) const
	{
		return m_data ? (const WCHAR *)((const char *)m_data + 8) : L"";
	}

	void format( UnicodeString fmt, ... );

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
class NetDisconnectChatCommandMsg
{
public:
	UnicodeString getText( void );
	Int getPlayerID( void ) { return m_playerID; }

private:
	void *m_vptr;									// this+0x00
	Int m_timestamp;								// this+0x04
	Int m_executionFrame;							// this+0x08
	Int m_playerID;									// this+0x0C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisconnectMenu.h
class DisconnectMenu
{
public:
	void showChat( UnicodeString text );
};

extern DisconnectMenu *TheDisconnectMenu;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	UnicodeString getPlayerName( Int playerID );

private:
	void processDisconnectChat( NetDisconnectChatCommandMsg *msg );
};

void ConnectionManager::processDisconnectChat( NetDisconnectChatCommandMsg *msg )
{
	if ( TheDisconnectMenu != 0 )
	{
		UnicodeString unitext;

		unitext.format( UnicodeString( L"[%ls] %ls" ),
			getPlayerName( msg->getPlayerID() ).str(),
			msg->getText().str() );

		TheDisconnectMenu->showChat( unitext );
	}
}
