// cl: /GS

// EA FESL client SDK ("jabba") blob-service result record populated constructor.
// The fixed keys and the adjacent default constructor identify the record as the
// 0x228-byte blob result returned by the FESL message object.

#include <stdio.h>

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );
	int getInt( const char *key, int defaultValue );
	bool getString( const char *key, char *dest, int destSize );
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
	m_ownerType = m_message->getInt( "ownerType", -1 );
	m_type = m_message->getInt( "type", -1 );
	m_formatType = m_message->getInt( "formatType", -1 );
	m_iconId = m_message->getInt64( "iconId", -1 );

	text[ 0 ] = 0;
	m_message->getString( "createDate", text, 0x20 );
	m_creator.parse( text );
	m_message->getString( "updateDate", text, 0x20 );
	m_update.parse( text );
	m_message->getString( "creator", m_creatorName, 0x20 );
	m_message->getString( "name", m_name, 0x20 );
	m_downloadCount = m_message->getInt( "downloadCount", -1 );
	m_message->getString( "rating", text + 0x0C, 0x40 );
	sscanf( text + 0x0C, "%f", &m_rating );
	m_reviewCount = m_message->getInt( "reviewCount", -1 );
	m_message->getString( "version", m_version, 0x20 );
	m_message->getString( "shortDescription", m_shortDescription, 0x50 );
	m_message->getString( "longDescription", m_longDescription, 0xFF );
	m_message->getString( "locale", m_locale, 0x20 );
	m_224 = 0;
}
