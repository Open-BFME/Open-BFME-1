// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?RequestAccept@LANAPI@@UAEXXZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp
// Open-BFME5: LANAPI::RequestAccept, retail 0x00686110, converted out of a
// machine byte dump. The reference body ports unchanged.
//
// The neighbour corroborates the class before a byte is compared: RequestChat
// is landed at 0x006865C0 and opens with the same two loads this body does --
// `mov ecx,[esi+0x40]` for m_currentGame and `call [eax+0xC4]` for
// fillInLANMessage, which is virtual here and reached through vtable slot
// +0xC4 rather than called directly.
//
// What the 135 bytes fix, all of it from where the stores land:
//
//   LANAPI      +0x3D  m_inLobby, tested as a byte
//               +0x40  m_currentGame
//               +0xC4  fillInLANMessage, vtable slot
//   LANMessage  size 0x1DC. The 0x1E0 frame holds the UnicodeString temporary
//               at its base and the message four bytes above it, so the frame
//               size minus four IS sizeof(LANMessage) and nails it exactly.
//               +0x00  LANMessageType, set to 9 for MSG_SET_ACCEPT
//               +0x22  Accept.gameName, and the terminator store at +0x42
//                      puts g_lanGameNameLength at 16 WideChars
//               +0x44  Accept.isAccepted
//
// str() is spelled out rather than called: retail tests the string data
// pointer, adds 8 when it is live and loads the address of an empty wide
// literal when it is not, which is what UnicodeString::str() folds to.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
// MSVC 7.1 has no native wchar_t without /Zc:wchar_t; the game headers typedef
// it the same way.
typedef unsigned short WideChar;

#define NULL 0

extern "C" __declspec(dllimport) WideChar * __cdecl wcsncpy( WideChar *, const WideChar *, unsigned int );

enum { g_lanGameNameLength = 16 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	WideChar m_stringdata[1];								///< +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString() { releaseBuffer(); }

	const WideChar *str( void ) const
	{
		return m_data ? m_data->m_stringdata : L"";
	}

protected:
	void releaseBuffer( void );								///< ?releaseBuffer@UnicodeString@@IAEXXZ

private:
	UnicodeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	UnicodeString getName( void );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	enum { MSG_SET_ACCEPT = 9 };

	Int LANMessageType;										///< +0x000
	unsigned char m_unreconstructed_04[0x22 - 0x04];

	union
	{
		struct
		{
			WideChar gameName[ g_lanGameNameLength + 1 ];	///< +0x022
			Bool isAccepted;								///< +0x044
		} Accept;

		unsigned char m_unreconstructed_22[0x1DC - 0x22];
	};
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual void bfmeRetailSlot00( void ) = 0;
	virtual void bfmeRetailSlot01( void ) = 0;
	virtual void bfmeRetailSlot02( void ) = 0;
	virtual void bfmeRetailSlot03( void ) = 0;
	virtual void bfmeRetailSlot04( void ) = 0;
	virtual void bfmeRetailSlot05( void ) = 0;
	virtual void bfmeRetailSlot06( void ) = 0;
	virtual void bfmeRetailSlot07( void ) = 0;
	virtual void bfmeRetailSlot08( void ) = 0;
	virtual void bfmeRetailSlot09( void ) = 0;
	virtual void bfmeRetailSlot10( void ) = 0;
	virtual void bfmeRetailSlot11( void ) = 0;
	virtual void bfmeRetailSlot12( void ) = 0;
	virtual void bfmeRetailSlot13( void ) = 0;
	virtual void bfmeRetailSlot14( void ) = 0;
	virtual void bfmeRetailSlot15( void ) = 0;
	virtual void bfmeRetailSlot16( void ) = 0;
	virtual void bfmeRetailSlot17( void ) = 0;
	virtual void bfmeRetailSlot18( void ) = 0;
	virtual void bfmeRetailSlot19( void ) = 0;
	virtual void bfmeRetailSlot20( void ) = 0;
	virtual void bfmeRetailSlot21( void ) = 0;
	virtual void bfmeRetailSlot22( void ) = 0;
	virtual void bfmeRetailSlot23( void ) = 0;
	virtual void bfmeRetailSlot24( void ) = 0;
	virtual void bfmeRetailSlot25( void ) = 0;
	virtual void bfmeRetailSlot26( void ) = 0;
	virtual void bfmeRetailSlot27( void ) = 0;
	virtual void bfmeRetailSlot28( void ) = 0;
	virtual void bfmeRetailSlot29( void ) = 0;
	virtual void bfmeRetailSlot30( void ) = 0;
	virtual void bfmeRetailSlot31( void ) = 0;
	virtual void bfmeRetailSlot32( void ) = 0;
	virtual void bfmeRetailSlot33( void ) = 0;
	virtual void bfmeRetailSlot34( void ) = 0;
	virtual void bfmeRetailSlot35( void ) = 0;
	virtual void bfmeRetailSlot36( void ) = 0;
	virtual void bfmeRetailSlot37( void ) = 0;
	virtual void bfmeRetailSlot38( void ) = 0;
	virtual void bfmeRetailSlot39( void ) = 0;
	virtual void bfmeRetailSlot40( void ) = 0;
	virtual void bfmeRetailSlot41( void ) = 0;
	virtual void bfmeRetailSlot42( void ) = 0;
	virtual void bfmeRetailSlot43( void ) = 0;
	virtual void bfmeRetailSlot44( void ) = 0;
	virtual void bfmeRetailSlot45( void ) = 0;
	virtual void bfmeRetailSlot46( void ) = 0;
	virtual void bfmeRetailSlot47( void ) = 0;
	virtual void bfmeRetailSlot48( void ) = 0;
	virtual void fillInLANMessage( LANMessage *msg ) = 0;	///< +0xC4

	virtual void RequestAccept( void );

protected:
	void sendMessage( LANMessage *msg, UnsignedInt ip );	///< ?sendMessage@LANAPI@@IAEXPAULANMessage@@I@Z

private:
	unsigned char m_unreconstructed_04[0x3D - 0x04];
	Bool m_inLobby;											///< +0x3D
	unsigned char m_unreconstructed_3e[0x40 - 0x3E];
	LANGameInfo *m_currentGame;								///< +0x40
};

// ?RequestAccept@LANAPI@@UAEXXZ
void LANAPI::RequestAccept( void )
{
	if (m_inLobby || !m_currentGame)
		return;

	LANMessage msg;
	fillInLANMessage( &msg );
	msg.LANMessageType = LANMessage::MSG_SET_ACCEPT;
	msg.Accept.isAccepted = true;
	wcsncpy(msg.Accept.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
	msg.Accept.gameName[g_lanGameNameLength] = 0;
	sendMessage(&msg, 0);
}
