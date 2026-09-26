// cl: /GS

#include <stdio.h>

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	int getInt( const char *key, int defaultValue );
	bool getString( const char *key, char *dest, int destSize );
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );
};

struct Rva007FF700Date
{
	int m_month;
	int m_day;
	int m_year;
	int parse( const char *text );
};

class Rva007F0CB0BlobRecord
{
public:
	int m_000;
	char m_pad004[ 4 ];
	FeslInt64 m_blobId;
	FeslInt64 m_ownerId;
	int m_ownerType;
	int m_pad01C;
	int m_type;
	int m_formatType;
	FeslInt64 m_iconId;
	Rva007FF700Date m_creator;
	Rva007FF700Date m_update;
	char m_updateDate[ 0x20 ];
	char m_createDate[ 0x20 ];
	int m_downloadCount;
	float m_rating;
	int m_reviewCount;
	char m_version[ 0x20 ];
	char m_shortDescription[ 0x50 ];
	char m_longDescription[ 0xFF ];
	char m_locale[ 0x20 ];
	int m_224;
};

class Rva007F05A0BlobCursor
{
public:
	bool next( Rva007F0CB0BlobRecord *record );

	Rva007E8810Message *m_msg;
	int m_index;
};

bool Rva007F05A0BlobCursor::next( Rva007F0CB0BlobRecord *record )
{
	char name[ 0x40 ];
	char text[ 0x4C ];
	float rating;

	sprintf( name, "blobs.%d.blobId", m_index );
	record->m_blobId = m_msg->getInt64( name, -1 );
	if ( record->m_blobId == -1 )
		return false;

	sprintf( name, "blobs.%d.ownerId", m_index );
	record->m_ownerId = m_msg->getInt64( name, -1 );

	sprintf( name, "blobs.%d.ownerType", m_index );
	record->m_ownerType = m_msg->getInt( "ownerType", -1 );

	sprintf( name, "blobs.%d.type", m_index );
	record->m_type = m_msg->getInt( name, -1 );

	sprintf( name, "blobs.%d.formatType", m_index );
	record->m_formatType = m_msg->getInt( name, -1 );

	sprintf( name, "blobs.%d.iconId", m_index );
	record->m_iconId = m_msg->getInt64( name, -1 );

	text[ 0 ] = 0;
	sprintf( name, "blobs.%d.createDate", m_index );
	m_msg->getString( name, text, 0x20 );
	record->m_creator.parse( text );

	sprintf( name, "blobs.%d.updateDate", m_index );
	m_msg->getString( "updateDate", text, 0x20 );
	record->m_update.parse( text );

	sprintf( name, "blobs.%d.creator", m_index );
	m_msg->getString( name, record->m_updateDate, 0x20 );

	sprintf( name, "blobs.%d.name", m_index );
	m_msg->getString( name, record->m_createDate, 0x20 );

	sprintf( name, "blobs.%d.downloadCount", m_index );
	record->m_downloadCount = m_msg->getInt( name, -1 );

	sprintf( name, "blobs.%d.rating", m_index );
	m_msg->getString( name, text + 0x0C, 0x40 );
	sscanf( text + 0x0C, "%f", &rating );
	record->m_rating = rating;

	sprintf( name, "blobs.%d.reviewCount", m_index );
	record->m_reviewCount = m_msg->getInt( name, -1 );

	sprintf( name, "blobs.%d.version", m_index );
	m_msg->getString( name, record->m_version, 0x20 );

	sprintf( name, "blobs.%d.shortDescription", m_index );
	m_msg->getString( name, record->m_shortDescription, 0x50 );

	sprintf( name, "blobs.%d.longDescription", m_index );
	m_msg->getString( name, record->m_longDescription, 0xff );

	sprintf( name, "blobs.%d.locale", m_index );
	m_msg->getString( name, record->m_locale, 0x20 );

	++m_index;
	return true;
}
