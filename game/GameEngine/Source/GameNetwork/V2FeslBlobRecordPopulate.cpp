// cl: /GS

// EA FESL client SDK ("jabba") blob-service result record populated constructor.
// The fixed keys and the adjacent default constructor identify the record as the
// 0x228-byte blob result returned by the FESL message object.

#include <stdio.h>

typedef __int64 FeslInt64;

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class BfmeThingRF
{
public:
	void *bfmeGoRF( void *one, void *two );                       // 0x007E8900
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *one, char *out, void *two );            // 0x007E8A80
};

class Rva007E8810Message
{
public:
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );
};

struct Rva007FF700Date
{
	int m_month;
	int m_day;
	int m_year;

	Rva007FF700Date();
	int parse( const char *text );
};

class Rva007F0CB0BlobRecord
{
public:
	Rva007F0CB0BlobRecord( Rva007E8810Message *message );

private:
	Rva007E8810Message *m_message;
	char m_pad004[ 0x04 ];
	FeslInt64 m_blobId;
	FeslInt64 m_ownerId;
	int m_ownerType;
	char m_pad01C[ 0x04 ];
	int m_type;
	int m_formatType;
	FeslInt64 m_iconId;
	Rva007FF700Date m_creator;
	Rva007FF700Date m_update;
	char m_creatorName[ 0x20 ];
	char m_name[ 0x20 ];
	int m_downloadCount;
	float m_rating;
	int m_reviewCount;
	char m_version[ 0x20 ];
	char m_shortDescription[ 0x50 ];
	char m_longDescription[ 0xFF ];
	char m_locale[ 0x20 ];
	int m_224;
};

Rva007F0CB0BlobRecord::Rva007F0CB0BlobRecord( Rva007E8810Message *message )
	: m_ownerId( 0 ), m_ownerType( 0 )
{
	char text[ 0x4C ];

	m_blobId = ( m_message = message )->getInt64( "blobId", -1 );
	m_ownerId = m_message->getInt64( "ownerId", -1 );
	m_ownerType = (int)(long)reinterpret_cast< BfmeThingRF * >( m_message )->bfmeGoRF( (void *)"ownerType", (void *)-1 );
	m_type = (int)(long)reinterpret_cast< BfmeThingRF * >( m_message )->bfmeGoRF( (void *)"type", (void *)-1 );
	m_formatType = (int)(long)reinterpret_cast< BfmeThingRF * >( m_message )->bfmeGoRF( (void *)"formatType", (void *)-1 );
	m_iconId = m_message->getInt64( "iconId", -1 );

	text[ 0 ] = 0;
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"createDate", text, (void *)0x20 );
	m_creator.parse( text );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"updateDate", text, (void *)0x20 );
	m_update.parse( text );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"creator", m_creatorName, (void *)0x20 );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"name", m_name, (void *)0x20 );
	m_downloadCount = (int)(long)reinterpret_cast< BfmeThingRF * >( m_message )->bfmeGoRF( (void *)"downloadCount", (void *)-1 );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"rating", text + 0x0C, (void *)0x40 );
	sscanf( text + 0x0C, "%f", &m_rating );
	m_reviewCount = (int)(long)reinterpret_cast< BfmeThingRF * >( m_message )->bfmeGoRF( (void *)"reviewCount", (void *)-1 );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"version", m_version, (void *)0x20 );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"shortDescription", m_shortDescription, (void *)0x50 );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"longDescription", m_longDescription, (void *)0xFF );
	reinterpret_cast< BfmeThingUPB * >( m_message )->bfmeGoUPB( (void *)"locale", m_locale, (void *)0x20 );
	m_224 = 0;
}
