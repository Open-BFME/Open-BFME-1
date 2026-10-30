// ?writeLANGameInfo@@YAXPBVLANGameInfo@@PADI@Z
// partial score=0.2488 date=2026-10-30
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// BFME's binary LAN game-info serializer:
//
//   ?writeLANGameInfo@@YAXPBVLANGameInfo@@PADI@Z  0x0068E090  1037 B
//
// Identity: reloc_names.csv names it from the byte-true calls in
// LANAPISendPath.cpp (RequestGameAnnounce 0x00685FC0) and the matched
// handleRequestGameInfo 0x0068B380 / fillCurrentLANGameInfo 0x0068E630, which
// reach it through ILT 0x00041579. Retail returns at +0x40C and +0x40D is
// int3 padding.
//
// Zero Hour builds the same announcement as text (GameInfoToAsciiString in
// GameNetwork/GameInfo.cpp); BFME writes it into a bounded byte buffer
// instead: the portable map path, four network-order header words, then one
// record per slot -- 'P' + name + address + flags + settings for a human,
// 'E'/'M'/'H' + settings for an AI, 'O' open, 'C' closed and 'X' otherwise,
// in Zero Hour's slot-kind order. Every field goes through one bounded write:
// with a limit the field is written only when it fits whole, and the cursor
// stays put when it does not. Out-of-line copies of these writers are matched
// at 0x0068D6A0 (byte), 0x0068D5A0 (ntohs word), 0x0068D5E0 (htonl dword) and
// 0x0068D550 (block); retail inlines all of them here.
//
// The GameInfo and GameSlot views below carry only the offsets this body reads;
// fields whose meaning no matched caller proves keep address-derived names.

#include "string_base.h"
#include "ascii_string.h"

extern "C" void * __cdecl memset( void *, int, unsigned int );
extern "C" void * __cdecl memcpy( void *, const void *, unsigned int );
#pragma intrinsic( memset, memcpy )

extern "C" __declspec(dllimport) int __stdcall ntohs( unsigned short netshort );
extern "C" __declspec(dllimport) unsigned long __stdcall htonl( unsigned long hostlong );

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

enum { MAX_SLOTS = 8 };

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

// Shared empty wide string, VA 0x0107388C (data row in LANAPIRequestHasMap.cpp).
extern const unsigned short BFMEEmptyUnicodeString;

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString( const WideChar *text, Int length )
		: StringBase<unsigned short>( text, length ) {}
	~UnicodeString() {}

	const WideChar *str( void ) const
	{
		return m_data ? (const WideChar *)((const char *)m_data + 8)
			: &BFMEEmptyUnicodeString;
	}
};

class GameSlot
{
public:
	Bool isHuman( void ) const;							///< 0x0061E580
	Bool isAI( void ) const;							///< 0x0061E5C0
	UnicodeString getName( void ) const;					///< 0x003879C0

	void *m_vptr;
	SlotState m_state;									///< +0x04
	Bool m_isAccepted;									///< +0x08
	Bool m_hasMap;										///< +0x09
	Bool m_isMuted;										///< +0x0A
	Int m_color;										///< +0x0C
	Int m_startPos;										///< +0x10
	Int m_playerTemplate;								///< +0x14
	Int m_teamNumber;									///< +0x18
	unsigned char m_gap1C[0x30 - 0x1C];
	UnsignedInt m_ip;									///< +0x30
	unsigned short m_port;								///< +0x34
	Int m_bfme38;										///< +0x38
};

class GameInfo
{
public:
	AsciiString getMap( void ) const;					///< 0x00098E70
	const GameSlot *getConstSlot( Int slotNum ) const;		///< 0x0061E900

	unsigned char m_gap00[0x40];
	UnsignedInt m_bfme40;								///< +0x40
	UnsignedInt m_bfme44;								///< +0x44
	Int m_bfme48;										///< +0x48
	UnsignedInt m_bfme4C;								///< +0x4C
};

class LANGameInfo : public GameInfo
{
};

AsciiString _Rva00621170MapPathHelperConcat( const AsciiString &input, Bool option );
char *rva68d730( char *cursor, char *text, char *limit );

union BoundedWordConverted
{
	volatile unsigned int storage;
	unsigned short narrow;
};

static inline char *writeByte( char *cursor, char value, char *limit )
{
	if( limit != 0 )
	{
		if( cursor > limit )
			return cursor;

		if( cursor + 1 > limit )
			return cursor;
	}

	*cursor = value;
	return cursor + 1;
}

template <typename T>
static inline char *writeNetWord( char *cursor, T value, char *limit )
{
	BoundedWordConverted converted;
	converted.storage = (unsigned int)ntohs( value );

	if( limit != 0 )
	{
		if( cursor > limit )
			return cursor;

		if( cursor + 2 > limit )
			return cursor;
	}

	*(unsigned short *)cursor = converted.narrow;
	return cursor + 2;
}

static inline char *writeNetLong( char *cursor, unsigned long value, char *limit )
{
	unsigned long raw = htonl( value );

	if( limit == 0 || ( cursor <= limit && cursor + 4 <= limit ) )
	{
		*(unsigned long *)cursor = raw;
		cursor += 4;
	}

	return cursor;
}

static inline char *writeBlock( char *cursor, const void *data, unsigned n, char *limit )
{
	if( limit != 0 && ( cursor > limit || cursor + n > limit ) )
		return cursor;

	memcpy( cursor, data, n );
	return cursor + n;
}

void writeLANGameInfo( const LANGameInfo *game, char *buffer, UnsignedInt size )
{
	if( !buffer )
		return;

	memset( buffer, 0, size );
	if( !game )
		return;

	char *end = buffer + size;

	AsciiString mapName;
	mapName = _Rva00621170MapPathHelperConcat( game->getMap(), true );
	char *cursor = rva68d730( buffer, (char *)mapName.str(), end );

	cursor = writeNetWord( cursor, game->m_bfme48, end );
	cursor = writeNetLong( cursor, game->m_bfme40, end );
	cursor = writeNetLong( cursor, game->m_bfme44, end );
	cursor = writeNetLong( cursor, game->m_bfme4C, end );

	for( UnsignedInt i = 0; i < MAX_SLOTS; ++i )
	{
		const GameSlot *slot = game->getConstSlot( i );
		if( slot && slot->isHuman() )
		{
			cursor = writeByte( cursor, 'P', end );
			{
				UnicodeString name( slot->getName().str(), 12 );
				cursor = writeBlock( cursor, name.str(), 26, end );
			}
			cursor = writeNetLong( cursor, slot->m_ip, end );
			cursor = writeNetWord( cursor, slot->m_port, end );
			cursor = writeByte( cursor, (char)( ( slot->m_isAccepted != 0 ) | ( ( slot->m_hasMap != 0 ) << 1 ) ), end );
			cursor = writeByte( cursor, (char)slot->m_color, end );
			cursor = writeByte( cursor, (char)slot->m_playerTemplate, end );
			cursor = writeByte( cursor, (char)slot->m_startPos, end );
			cursor = writeByte( cursor, (char)slot->m_teamNumber, end );
			cursor = writeByte( cursor, (char)slot->m_bfme38, end );
		}
		else if( slot && slot->isAI() )
		{
			char c;
			switch( slot->m_state )
			{
				case SLOT_EASY_AI:
					c = 'E';
					break;
				case SLOT_MED_AI:
					c = 'M';
					break;
				default:
					c = 'H';
					break;
			}
			cursor = writeByte( cursor, c, end );
			cursor = writeByte( cursor, (char)slot->m_color, end );
			cursor = writeByte( cursor, (char)slot->m_playerTemplate, end );
			cursor = writeByte( cursor, (char)slot->m_startPos, end );
			cursor = writeByte( cursor, (char)slot->m_teamNumber, end );
		}
		else if( slot && slot->m_state == SLOT_OPEN )
		{
			cursor = writeByte( cursor, 'O', end );
		}
		else if( slot && slot->m_state == SLOT_CLOSED )
		{
			cursor = writeByte( cursor, 'C', end );
		}
		else
		{
			cursor = writeByte( cursor, 'X', end );
		}
	}
}
