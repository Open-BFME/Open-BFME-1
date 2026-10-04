// cl: /GS
#include <stdio.h>

// EA FESL client SDK ("jabba") -- Aries game-key records.
//
// Same SDK cluster as V2FeslAriesRecords.cpp; see that file for how the span
// was identified and for the message accessors used here.  This file lands the
// LID/GID base constructor itself (0x007FBC30 -- already PINNED by the V2 lane,
// which declares it and calls it from three derived records but never defines
// it) together with the game-attribute record whose three lookup helpers build
// their key with sprintf from a "B-%s" / "D-%s" / "P-%s" prefix.
//
// Buffer sizes and member offsets are immediates with no relocation and are
// therefore hard evidence: 0x25 for the UGID field, 0x40 for the sprintf
// scratch (its /GS cookie slot at +0x40 fixes the array length exactly).
// The three prefixes differ only in one literal byte, so the three helper
// bodies are NOT interchangeable and each is distinguished by its own DIR32.
//
// CAVEAT ON THE MODEL.  The three lookup helpers reach their message through
// `this + 8` and nothing else, so the bytes prove only that their owner keeps
// the message pointer at +8.  The record at 0x007FBC60 (see
// Y4FeslGameDetailRecords.cpp) ALSO keeps its message at +8, so the bytes
// cannot decide which of the two owns them; grouping them with 0x007FBEF0 here
// is a modelling choice, not a byte-level finding.  The names are
// address-derived precisely because of that.
//
// This lane may not add a .h file, so the message class is re-declared here.

typedef __int64 FeslInt64;

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class BfmeThingRF
{
public:
	void *bfmeGoRF( void *one, void *two );                       // 0x007E8900
};

// The pinned body at 0x007E8A80 is the ledger's ?bfmeGoUPB@BfmeThingUPB
// (char return), but these three helpers plus the constructor return a bool and
// the retail bytes carry no char-to-bool conversion after the call. The calls
// are therefore made through a union: the member-pointer slot is typed like the
// old getString (bool (this)(const char *, char *, int)) so the call sequence is
// byte-identical, while the value in the union is the address of the real
// ?bfmeGoUPB@BfmeThingUPB body. Both classes are TU-local re-declarations and
// a thiscall member pointer is a bare code address on x86, so the pun is exact.
class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *key, char *dest, void *destSize );          // 0x007E8A80
};

class Rva007E8810Message;

typedef char (BfmeThingUPB::*UpbFn007E8A80)( void *, char *, void * );
typedef bool (Rva007E8810Message::*MsgFn007E8A80)( const char *, char *, int );

class Rva007E8810Message
{
public:
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );   // 0x007E8930
};

// ------------------------------------------------------- LID/GID base record
class Rva007FBC30GameKey
{
public:
	Rva007FBC30GameKey( Rva007E8810Message *msg );
	int m_lid;
	int m_gid;
};

Rva007FBC30GameKey::Rva007FBC30GameKey( Rva007E8810Message *msg )
{
	m_lid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"LID", (void *)0 );
	m_gid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"GID", (void *)0 );
}

// ------------------------------------------------- game record with UGID key
class Rva007FBEF0GameRecord
{
public:
	Rva007FBEF0GameRecord( Rva007E8810Message *msg );
	bool Rva007FBE80( const char *key, char *dest, unsigned int destSize );
	bool Rva007FBF40( const char *key, char *dest, unsigned int destSize );
	bool Rva007FBFB0( const char *key, char *dest, unsigned int destSize );

	int m_lid;
	int m_gid;
	Rva007E8810Message *m_msg;
	char m_ugid[ 0x25 ];
};

Rva007FBEF0GameRecord::Rva007FBEF0GameRecord( Rva007E8810Message *msg )
{
	m_lid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"LID", (void *)0 );
	m_gid = (int)(long)reinterpret_cast< BfmeThingRF * >( msg )->bfmeGoRF( (void *)"GID", (void *)0 );
	m_msg = msg;
	m_ugid[ 0 ] = 0;
	union { UpbFn007E8A80 upb; MsgFn007E8A80 call; } u007e8a80 = { &BfmeThingUPB::bfmeGoUPB };
	( m_msg->*u007e8a80.call )( "UGID", m_ugid, 0x25 );
}

bool Rva007FBEF0GameRecord::Rva007FBE80( const char *key, char *dest,
	unsigned int destSize )
{
	char name[ 0x40 ];

	if( key == 0 || destSize <= 0 )
		return false;
	sprintf( name, "B-%s", key );
	union { UpbFn007E8A80 upb; MsgFn007E8A80 call; } u007e8a80 = { &BfmeThingUPB::bfmeGoUPB };
	return ( m_msg->*u007e8a80.call )( name, dest, destSize );
}

bool Rva007FBEF0GameRecord::Rva007FBF40( const char *key, char *dest,
	unsigned int destSize )
{
	char name[ 0x40 ];

	if( key == 0 || destSize <= 0 )
		return false;
	sprintf( name, "D-%s", key );
	union { UpbFn007E8A80 upb; MsgFn007E8A80 call; } u007e8a80 = { &BfmeThingUPB::bfmeGoUPB };
	return ( m_msg->*u007e8a80.call )( name, dest, destSize );
}

bool Rva007FBEF0GameRecord::Rva007FBFB0( const char *key, char *dest,
	unsigned int destSize )
{
	char name[ 0x40 ];

	if( key == 0 || destSize <= 0 )
		return false;
	sprintf( name, "P-%s", key );
	union { UpbFn007E8A80 upb; MsgFn007E8A80 call; } u007e8a80 = { &BfmeThingUPB::bfmeGoUPB };
	return ( m_msg->*u007e8a80.call )( name, dest, destSize );
}
