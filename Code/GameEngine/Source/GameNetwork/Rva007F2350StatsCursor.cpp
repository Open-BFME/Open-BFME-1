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

class Rva007F2350StatsRecord
{
public:
	FeslInt64 m_owner;
	char m_pad08[ 8 ];
	char m_name[ 0x20 ];
	char m_30;
	char m_pad31[ 0x1F ];
	int m_value;
	char m_addStat[ 0x100 ];
	int m_rank;
};

class Rva007F2350StatsCursor
{
public:
	bool next( Rva007F2350StatsRecord *record );

	Rva007E8810Message *m_msg;
	int m_index;
	int m_state;
};

bool Rva007F2350StatsCursor::next( Rva007F2350StatsRecord *record )
{
	char name[ 0x40 ];
	char valueText[ 0x40 ];
	int value;

	record->m_name[ 0 ] = 0;
	record->m_30 = 0;
	record->m_value = 0;
	record->m_addStat[ 0 ] = 0;
	record->m_rank = 0;

	sprintf( name, "stats.%d.value", m_index );
	if ( !m_msg->getString( name, valueText, 0x40 ) )
		return false;
	sscanf( valueText, "%f", &value );
	record->m_value = value;

	sprintf( name, "stats.%d.rank", m_index );
	record->m_rank = m_msg->getInt( name, 0 );

	sprintf( name, "stats.%d.owner", m_index );
	record->m_owner = m_msg->getInt64( name, 0 );

	sprintf( name, "stats.%d.name", m_index );
	m_msg->getString( name, record->m_name, 0x20 );

	sprintf( name, "stats.%d.text", m_index );
	m_msg->getString( name, record->m_addStat, 0xff );

	++m_index;
	m_state = 0;
	return true;
}
