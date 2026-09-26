// ?writeLANGameInfo@@YAXPBVLANGameInfo@@PADI@Z
// partial score=0.62 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// readable body of ?RequestAccept@LANAPI@@UAEXXZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp
// readable body of ?sendMessage@LANAPI@@IAEXPAULANMessage@@I@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp
// readable body of ?RequestGameAnnounce@LANAPI@@UAEXXZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp
// readable body of ?RequestGameStart@LANAPI@@UAEXXZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp
// readable body of ?RequestGameStartTimer@LANAPI@@UAEXH@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// LANAPI's LANMessage traffic: the one send primitive and the bodies that
// build a message for it, plus the two receive handlers that answer a peer
// without sending anything back.
//
//   sendMessage             0x00684CF0  the primitive -- a named destination
//                                       goes straight to the transport, a
//                                       direct-connect game to every other
//                                       human slot, anything else broadcast
//                                       across ports 8086..8093
//   RequestGameStart        0x00684E70  type 13, host only, then OnGameStart
//   RequestGameStartTimer   0x00684F30  type 14, host only, seconds at +0x22
//   RequestGameAnnounce     0x00685FC0  type 1, slot 23
//   RequestAccept           0x00686110  type 9
//   handleRequestGameInfo   0x0068B380  answers a type-0x11 request with the
//                                       same type-1 announce
//   handleRequestLobbyLeave 0x0068AC20  drops the sender from the lobby list
//   handleSetAccept         0x0068AC80  forwards the sender's accept byte
//
// This TU is built /EHs-c- and the spelling matters: /EHsc- parses as /EHs plus
// /EHc-, which leaves handling ON and puts two unwind-state stores into every
// body with a UnicodeString temporary. Retail has none.
//
// LANMessage's shape falls out of the offsets these bodies write: the type word
// at +0x00, then one union at +0x22 -- the wide game name with its terminator
// at +0x42 (sixteen characters), the flag byte at +0x44 that is inProgress in
// an announce and isAccepted in a SET_ACCEPT, isDirectConnect at +0x45 and the
// serialized options filling +0x46 -- or the options block from +0x22, or the
// timer's second count there. It is 0x1DC bytes, which is what the 0x1E0 frame
// RequestAccept reserves for the message plus a UnicodeString temporary fixes.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
// MSVC 7.1 has no native wchar_t without /Zc:wchar_t; the game headers typedef
// it the same way.
typedef unsigned short WideChar;

#define NULL 0

extern "C" __declspec(dllimport) WideChar * __cdecl wcsncpy( WideChar *, const WideChar *, unsigned int );
extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime( void );
extern "C" __declspec(dllimport) UnsignedInt __stdcall htonl( UnsignedInt );
extern "C" __declspec(dllimport) unsigned short __stdcall ntohs( unsigned short );
extern "C" void * __cdecl memset( void *, int, unsigned int );
extern "C" void * __cdecl memcpy( void *, const void *, unsigned int );
#pragma intrinsic( memset )
#pragma intrinsic( memcpy )

enum { g_lanGameNameLength = 16, g_lanMaxOptionsLength = 0x196 };

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

// The serializer uses the canonical WWLib string bodies for its map path and
// the bounded player-name copy.  Keep these views separate from the older
// UnicodeString shim above, whose release method is needed by the neighbouring
// LANAPI message bodies.
template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class BfmeWideSlotString;

private:
	StringBase( void ) : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	StringBase( const T *text, Int length );
	~StringBase();
	void set( const StringBase<T> &other );

	void *m_data;
};

extern const char g_bfmeEmptyUnicode[];

class AsciiString : private StringBase<char>
{
public:
	AsciiString( void ) : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString();

	AsciiString &operator=( const AsciiString &other )
	{
		StringBase<char>::set( other );
		return *this;
	}

	const char *str( void ) const
	{
		const void *data = ((const StringBase<char> *)this)->m_data;
		return data ? (const char *)data + 8 : "";
	}
};

class BfmeWideSlotString : private StringBase<WideChar>
{
public:
	BfmeWideSlotString( const WideChar *text, Int length )
		: StringBase<WideChar>( text, length ) {}
	~BfmeWideSlotString();

	const WideChar *str( void ) const
	{
		const void *data = ((const StringBase<WideChar> *)this)->m_data;
		return data ? (const WideChar *)((const unsigned char *)data + 8)
			: (const WideChar *)g_bfmeEmptyUnicode;
	}
};

// The address pair vtable slot 55 hands back, and what a LANPlayer and a game
// slot store. BfmeTransportAddress below is the same pair packed to six bytes,
// which is the spelling ?queueSend@BfmeTransportQueueShim@@ is pinned under, so
// both names have to stay.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	unsigned short m_port;
};

#pragma pack(push, 1)
struct BfmeTransportAddress
{
	UnsignedInt m_ip;
	unsigned short m_port;
};
#pragma pack(pop)

class BfmeGameSlot;

class BfmeGameInfo
{
public:
	BfmeGameSlot *getSlot( Int slot );
};

class GameSlot
{
public:
	BfmeWideSlotString getName( void ) const;
	Bool isAI( void ) const;

	void *m_vptr;
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	UnsignedByte m_pad0B;
	Int m_color;
	Int m_startPos;
	Int m_playerTemplate;
	Int m_teamNumber;
	Int m_origColor;
	Int m_origStartPos;
	Int m_origPlayerTemplate;
	void *m_name;
	void *m_ip;
	UnsignedInt m_bfme30;
	UnsignedInt m_bfme34;
	UnsignedInt m_bfme38;
	UnsignedInt m_bfme3C;
	UnsignedByte m_bfme40;
};

class GameInfo
{
public:
	AsciiString getMap( void ) const;
	const GameSlot *getConstSlot( Int slot ) const;

	UnsignedByte m_beforeSerializedFields[0x40];
	UnsignedInt m_bfme40;
	UnsignedInt m_bfme44;
	UnsignedInt m_bfme48;
	UnsignedInt m_bfme4C;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo : public BfmeGameInfo
{
public:
	UnicodeString getName( void );								///< ILT thunk 0x00041FC9
	virtual void bfmeGameInfoSlot01( void ) = 0;
	virtual void bfmeGameInfoSlot02( void ) = 0;
	virtual void bfmeGameInfoSlot03( void ) = 0;
	virtual void bfmeGameInfoSlot04( void ) = 0;
	virtual void bfmeGameInfoSlot05( void ) = 0;
	virtual Int getLocalSlotNum( void ) const = 0;

	Bool getIsDirectConnect( void ) const
	{
		return m_isDirectConnect;
	}

	unsigned char m_bfmeGapA[0x0D - 4];
	Bool m_inProgress;									///< +0x00D
	unsigned char m_bfmeGapB[0x88 - 0x0E];
	BfmeTransportAddress m_hostAddress;							///< +0x088
	unsigned char m_bfmeGapC[0x3A4 - 0x8E];
	Bool m_isDirectConnect;									///< +0x3A4
};

struct BfmeLANSlot
{
	BfmeNetAddress m_address;
	UnsignedByte m_bfmeRest[0x68 - 8];
};

// handleSetAccept walks eight 0x68-byte participant records from +0x88, which
// runs to +0x3C8 and would swallow m_isDirectConnect at +0x3A4. Both offsets are
// byte-proven from the bodies here, so the two readings of +0x88 cannot both be
// members of one class; the walk keeps its own view rather than either reading
// being quietly dropped. Whichever is the real LANGameInfo, this is the open
// question, stated once.
class BfmeLANGameInfoSlots
{
public:
	UnsignedByte m_bfmeHead[0x88];
	BfmeLANSlot m_slot[8];									///< +0x088
};

class BfmeGameSlot
{
public:
	virtual void bfmeGameSlotVft( void ) = 0;
	Bool isHuman( void ) const;
	unsigned char m_bfmeGameSlotGap[0x30 - 4];
	BfmeTransportAddress m_address;
};

class Transport
{
public:
	void update( void );
};

class BfmeTransportQueueShim
{
public:
	Bool queueSend(const BfmeTransportAddress *address,
		const unsigned char *data, Int length);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	UnsignedByte m_bfmeHead[0x10];
	LANPlayer *m_next;									///< +0x10
	BfmeNetAddress m_address;								///< +0x14
};

// The timer's second count is an Int at message +0x22, which is not
// four-aligned, so it is packed on its own rather than packing the whole
// message and changing how a LANMessage local is laid out.
#pragma pack(push, 1)
struct LANMessageStartTimer
{
	Int seconds;										///< message +0x22
};
#pragma pack(pop)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	enum
	{
		MSG_GAME_ANNOUNCE = 1,
		MSG_SET_ACCEPT = 9,
		MSG_GAME_START = 13,
		MSG_GAME_START_TIMER = 14
	};

	Int LANMessageType;									///< +0x000
	unsigned char m_unreconstructed_04[0x22 - 0x04];

	union
	{
		struct
		{
			WideChar gameName[ g_lanGameNameLength + 1 ];			///< +0x022
			Bool inProgress;						///< +0x044
			Bool isDirectConnect;						///< +0x045
			char options[ g_lanMaxOptionsLength ];				///< +0x046
		} GameAnnounce;

		struct
		{
			WideChar gameName[ g_lanGameNameLength + 1 ];			///< +0x022
			Bool isAccepted;						///< +0x044, the announce's inProgress byte
		} Accept;

		struct
		{
			char options[ g_lanMaxOptionsLength + 1 ];			///< +0x022
		} GameOptions;

		LANMessageStartTimer StartTimer;					///< +0x022
	};
};

// The existing generated helper is a bounded append: its third argument is
// the one-past-end pointer and it returns the unchanged cursor on overflow.
// Its body is independently byte-proven at 0x0068D730; this declaration keeps
// that real callee visible without fabricating a second implementation.
extern "C" char *rva0068D730Append( char *destination, const char *source,
	char *end );

extern AsciiString _Rva00621170MapPathHelperConcat(
	const AsciiString &input, Bool option );

void __cdecl writeLANGameInfo(const LANGameInfo *game, char *buffer, UnsignedInt size)
{
	if (!buffer)
		return;

	memset(buffer, 0, size);
	if (!game || size == 0)
		return;

	char *cursor = buffer;
	char *end = buffer + size;
	const GameInfo *info = reinterpret_cast<const GameInfo *>(game);
	AsciiString mapName = info->getMap();
	mapName = _Rva00621170MapPathHelperConcat(mapName, true);
	cursor = rva0068D730Append(buffer, mapName.str(), end);

	UnsignedInt value = ntohs(info->m_bfme48);
	if (end && cursor <= end && cursor + 2 <= end)
	{
		*reinterpret_cast<unsigned short *>(cursor) = (unsigned short)value;
		cursor += 2;
	}

	value = htonl(info->m_bfme40);
	if (end && cursor <= end && cursor + 4 <= end)
	{
		*reinterpret_cast<UnsignedInt *>(cursor) = value;
		cursor += 4;
	}

	value = htonl(info->m_bfme44);
	if (end && cursor <= end && cursor + 4 <= end)
	{
		*reinterpret_cast<UnsignedInt *>(cursor) = value;
		cursor += 4;
	}

	value = htonl(info->m_bfme4C);
	if (end && cursor <= end && cursor + 4 <= end)
	{
		*reinterpret_cast<UnsignedInt *>(cursor) = value;
		cursor += 4;
	}

	for (Int player = 0; player < 8; ++player)
	{
		const GameSlot *slot = info->getConstSlot(player);
		if (!slot)
			continue;

		if (reinterpret_cast<const BfmeGameSlot *>(slot)->isHuman())
		{
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = 'P';
				++cursor;
			}

			{
				BfmeWideSlotString playerName = slot->getName();
				BfmeWideSlotString limitedName(playerName.str(), 12);
				if (end && cursor <= end && cursor + 26 <= end)
				{
					memcpy(cursor, limitedName.str(), 26);
					cursor += 26;
				}
			}

			value = htonl(slot->m_bfme30);
			if (end && cursor <= end && cursor + 4 <= end)
			{
				*reinterpret_cast<UnsignedInt *>(cursor) = value;
				cursor += 4;
			}

			value = ntohs(slot->m_bfme34);
			if (end && cursor <= end && cursor + 2 <= end)
			{
				*reinterpret_cast<unsigned short *>(cursor) =
					(unsigned short)value;
				cursor += 2;
			}

			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_isAccepted |
					((unsigned char)slot->m_hasMap << 1);
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_color;
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_playerTemplate;
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_startPos;
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_teamNumber;
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_bfme38;
				++cursor;
			}
		}
		else
		{
			char status;
			if (slot->isAI())
			{
				if (slot->m_state == 2)
					status = 'E';
				else if (slot->m_state == 3)
					status = 'M';
				else
					status = 'H';
			}
			else if (slot->m_state == 0)
				status = 'O';
			else if (slot->m_state == 1)
				status = 'C';
			else
				status = 'X';

			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = status;
				++cursor;
			}

			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_isAccepted |
					((unsigned char)slot->m_hasMap << 1);
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_color;
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_playerTemplate;
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_startPos;
				++cursor;
			}
			if (end && cursor <= end && cursor + 1 <= end)
			{
				*cursor = (unsigned char)slot->m_teamNumber;
				++cursor;
			}
		}
	}
}

void __cdecl fillCurrentLANGameInfo(char *buffer, unsigned int size);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
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
	virtual Bool isPacketRouter( void ) = 0;						///< slot 35, vtable+0x8C
};

extern NetworkInterface *TheNetwork;

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
	virtual void RequestGameAnnounce( void );						///< slot 23
	virtual void bfmeRetailSlot24( void ) = 0;
	virtual void bfmeRetailSlot25( void ) = 0;
	virtual void bfmeRetailSlot26( void ) = 0;
	virtual void bfmeRetailSlot27( void ) = 0;
	virtual void OnPlayerList( LANPlayer *players ) = 0;					///< slot 28, vtable+0x70
	virtual void bfmeRetailSlot29( void ) = 0;
	virtual void bfmeRetailSlot30( void ) = 0;
	virtual void bfmeRetailSlot31( void ) = 0;
	virtual void bfmeRetailSlot32( void ) = 0;
	virtual void OnAccept( BfmeNetAddress *from, UnsignedInt status ) = 0;			///< slot 33, vtable+0x84
	virtual void bfmeRetailSlot34( void ) = 0;
	virtual void bfmeRetailSlot35( void ) = 0;
	virtual void OnGameStart( void ) = 0;							///< slot 36, vtable+0x90
	virtual void OnGameStartTimer( Int seconds ) = 0;					///< slot 37, vtable+0x94
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
	virtual void fillInLANMessage( LANMessage *msg ) = 0;					///< slot 49, vtable+0xC4
	virtual void bfmeRetailSlot50( void ) = 0;
	virtual void bfmeRetailSlot51( void ) = 0;
	virtual void bfmeRetailSlot52( void ) = 0;
	virtual void bfmeRetailSlot53( void ) = 0;
	virtual void bfmeRetailSlot54( void ) = 0;
	virtual BfmeNetAddress *_bfme_localAddress( void ) = 0;					///< slot 55, vtable+0xDC

	// No slot evidence for these three: nothing in the image dispatches them
	// through the table at 0x0111AF50 at an offset the bodies here pin, so they
	// are declared past the end rather than claiming a slot they may not own.
	virtual void RequestAccept( void );
	virtual void RequestGameStart( void );
	virtual void RequestGameStartTimer( Int seconds );

protected:
	void handleRequestGameInfo( LANMessage *msg, UnsignedInt senderIP );
	void handleRequestLobbyLeave( LANMessage *msg, BfmeNetAddress *sender );
	void handleSetAccept( LANMessage *msg, BfmeNetAddress *sender );
	void sendMessage( LANMessage *msg, UnsignedInt ip );					///< ILT thunk 0x0002B599
	void removePlayer( LANPlayer *player );							///< ILT thunk 0x0003BDF4

	unsigned char m_unreconstructed_04[0x08 - 0x04];
	LANPlayer *m_lobbyPlayers;								///< +0x08
	unsigned char m_unreconstructed_0c[0x1C - 0x0C];
	UnsignedInt m_gameStartTime;								///< +0x1C
	Int m_gameStartSeconds;									///< +0x20
	unsigned char m_unreconstructed_24[0x3D - 0x24];
	Bool m_inLobby;										///< +0x3D
	unsigned char m_unreconstructed_3e[0x40 - 0x3E];
	LANGameInfo *m_currentGame;								///< +0x40
	unsigned char m_bfmeHoleBeforeTransport[8];
	BfmeTransportQueueShim * volatile m_transport;						///< +0x4C
	UnsignedInt m_broadcastAddr;								///< +0x50
};

// ?sendMessage@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::sendMessage( LANMessage *msg, UnsignedInt ip )
{
	BfmeTransportAddress *address =
		reinterpret_cast<BfmeTransportAddress *>(ip);
	if (address != 0 && (address->m_ip != 0 || address->m_port != 0))
	{
		m_transport->queueSend(address,
			reinterpret_cast<const unsigned char *>(msg), sizeof(LANMessage));
		return;
	}

	if (m_currentGame != 0 && m_currentGame->getIsDirectConnect())
	{
		Int localSlot = m_currentGame->getLocalSlotNum();
		for (Int i = 0; i < 8; ++i)
		{
			if (i == localSlot)
				continue;
			// BFME's LANGameInfo subobject starts at the object address; keep this
			// view explicit because the reference declaration is not BFME's base layout.
			BfmeGameInfo *gameInfo =
				reinterpret_cast<BfmeGameInfo *>(m_currentGame);
			BfmeGameSlot *slot = gameInfo->getSlot(i);
			if (slot != 0 && slot->isHuman())
			{
				m_transport->queueSend(&slot->m_address,
					reinterpret_cast<const unsigned char *>(msg), sizeof(LANMessage));
			}
		}
	}
	else
	{
		BfmeTransportAddress address;
		for (unsigned short port = 8086; port < 8094; ++port)
		{
			address.m_ip = m_broadcastAddr;
			address.m_port = port;
			m_transport->queueSend(&address,
				reinterpret_cast<const unsigned char *>(msg), sizeof(LANMessage));
		}
	}
}

// ?RequestGameStart@LANAPI@@UAEXXZ
//
// Zero Hour only sends MSG_GAME_START; BFME's host first broadcasts the
// serialized game-info block into msg+0x22 before OnGameStart.
void LANAPI::RequestGameStart( void )
{
	if (m_inLobby)
		return;

	LANGameInfo *game = m_currentGame;
	if (game == 0)
		return;

	BfmeNetAddress *me = _bfme_localAddress();
	if (game->m_hostAddress.m_ip != me->m_ip || game->m_hostAddress.m_port != me->m_port)
		return;

	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_GAME_START;
	fillInLANMessage(&msg);
	fillCurrentLANGameInfo(msg.GameOptions.options, g_lanMaxOptionsLength);
	sendMessage(&msg, 0);
	reinterpret_cast<Transport *>(m_transport)->update();
	OnGameStart();
}

// ?RequestGameStartTimer@LANAPI@@UAEXH@Z
//
// Retail writes the type and the second count BEFORE fillInLANMessage runs,
// where the ported lanapi.cpp body stores the type after it.
void LANAPI::RequestGameStartTimer( Int seconds )
{
	if (m_inLobby)
		return;

	LANGameInfo *game = m_currentGame;
	if (game == 0)
		return;

	BfmeNetAddress *me = _bfme_localAddress();
	if (game->m_hostAddress.m_ip != me->m_ip || game->m_hostAddress.m_port != me->m_port)
		return;

	m_gameStartTime = timeGetTime() + 1000;

	Int timerSeconds = seconds;
	m_gameStartSeconds = timerSeconds ? timerSeconds - 1 : 0;

	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_GAME_START_TIMER;
	msg.StartTimer.seconds = timerSeconds;
	fillInLANMessage(&msg);
	sendMessage(&msg, 0);
	reinterpret_cast<Transport *>(m_transport)->update();
	OnGameStartTimer(timerSeconds);
}

// ?RequestGameAnnounce@LANAPI@@UAEXXZ
void LANAPI::RequestGameAnnounce( void )
{
	LANGameInfo *game = m_currentGame;

	// In game - are we a game host?
	if (game && !game->m_isDirectConnect)
	{
		BfmeNetAddress *me = _bfme_localAddress();

		// if we are in game we should reply if we are the packet router
		if ((game->m_hostAddress.m_ip == me->m_ip && game->m_hostAddress.m_port == me->m_port)
			|| (m_currentGame->m_inProgress && TheNetwork && TheNetwork->isPacketRouter()))
		{
			LANMessage reply;
			fillInLANMessage(&reply);
			reply.LANMessageType = LANMessage::MSG_GAME_ANNOUNCE;

			writeLANGameInfo(m_currentGame, reply.GameAnnounce.options, g_lanMaxOptionsLength);
			wcsncpy(reply.GameAnnounce.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
			reply.GameAnnounce.gameName[g_lanGameNameLength] = 0;
			reply.GameAnnounce.inProgress = m_currentGame->m_inProgress;
			reply.GameAnnounce.isDirectConnect = m_currentGame->m_isDirectConnect;

			sendMessage(&reply, 0);
		}
	}
}

// ?RequestAccept@LANAPI@@UAEXXZ
//
// str() is spelled out rather than called: retail tests the string data
// pointer, adds 8 when it is live and loads the address of an empty wide
// literal when it is not, which is what UnicodeString::str() folds to.
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

// ?handleRequestGameInfo@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleRequestGameInfo( LANMessage *, UnsignedInt senderIP )
{
	LANGameInfo *game = m_currentGame;
	if (game)
	{
		BfmeNetAddress *localAddress = _bfme_localAddress();
		if ((game->m_hostAddress.m_ip == localAddress->m_ip &&
			game->m_hostAddress.m_port == localAddress->m_port) ||
			(m_currentGame->m_inProgress && TheNetwork && TheNetwork->isPacketRouter()))
		{
			LANMessage reply;
			fillInLANMessage(&reply);
			reply.LANMessageType = LANMessage::MSG_GAME_ANNOUNCE;
			writeLANGameInfo(m_currentGame, reply.GameAnnounce.options, g_lanMaxOptionsLength);
			wcsncpy(reply.GameAnnounce.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
			reply.GameAnnounce.gameName[g_lanGameNameLength] = 0;
			reply.GameAnnounce.inProgress = m_currentGame->m_inProgress;
			reply.GameAnnounce.isDirectConnect = m_currentGame->m_isDirectConnect;
			sendMessage(&reply, senderIP);
		}
	}
}

// ?handleRequestLobbyLeave@LANAPI@@IAEXPAULANMessage@@PAUBfmeNetAddress@@@Z
void LANAPI::handleRequestLobbyLeave( LANMessage *msg, BfmeNetAddress *sender )
{
	if (m_inLobby)
	{
		LANPlayer *player = m_lobbyPlayers;
		while (player)
		{
			if (player->m_address.m_ip == sender->m_ip &&
				player->m_address.m_port == sender->m_port)
			{
				removePlayer(player);
				OnPlayerList(m_lobbyPlayers);
				break;
			}
			player = player->m_next;
		}
	}
}

// ?handleSetAccept@LANAPI@@IAEXPAULANMessage@@PAUBfmeNetAddress@@@Z
void LANAPI::handleSetAccept( LANMessage *msg, BfmeNetAddress *sender )
{
	if (!m_inLobby && m_currentGame && !m_currentGame->m_inProgress)
	{
		Int player;
		for (player = 0; player < 8; ++player)
		{
			BfmeNetAddress *slot = &reinterpret_cast<BfmeLANGameInfoSlots *>(
				m_currentGame)->m_slot[player].m_address;
			if (slot->m_ip == sender->m_ip && slot->m_port == sender->m_port)
			{
				OnAccept(sender, msg->Accept.isAccepted);
				break;
			}
		}
	}
}
