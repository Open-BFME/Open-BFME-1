// cl: /GS

#include <stdio.h>

typedef __int64 FeslInt64;

// Calls name each Rva007E8810Message helper by the ledger row at its pinned
// address (link_check.py near), the spelling the link resolves.
class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *one, char *out, void *two );            // 0x007E8A80
};

class BfmeThingRF
{
public:
	void *bfmeGoRF( void *one, void *two );                       // 0x007E8900
};

class Rva007E8810Message
{
public:
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
	bool rva007F2230( Rva007F2350StatsRecord *record );
	bool rva007F24A0( Rva007F2350StatsRecord *record );

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
	if ( !reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, valueText, (void *)0x40 ) )
		return false;
	sscanf( valueText, "%f", &value );
	record->m_value = value;

	sprintf( name, "stats.%d.rank", m_index );
	record->m_rank = (int)(long)reinterpret_cast< BfmeThingRF * >( m_msg )->bfmeGoRF( (void *)name, (void *)0 );

	sprintf( name, "stats.%d.owner", m_index );
	record->m_owner = m_msg->getInt64( name, 0 );

	sprintf( name, "stats.%d.name", m_index );
	reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, record->m_name, (void *)0x20 );

	sprintf( name, "stats.%d.text", m_index );
	reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, record->m_addStat, (void *)0xff );

	++m_index;
	m_state = 0;
	return true;
}

// Retail 0x007F2230: int3 at 0x007F222F, ret 4 at 0x007F2348,
// then five int3 bytes. The stats.* strings prove this shares the cursor
// and output record layout with next; its +0x30 output is the key string.
bool Rva007F2350StatsCursor::rva007F2230(Rva007F2350StatsRecord *record)
{
 char name[0x40];
 char valueText[0x40];
 union { float number; int bits; } value;
 record->m_name[0] = 0;
 record->m_30 = 0;
 record->m_value = 0;
 record->m_addStat[0] = 0;
 record->m_rank = 0;
 sprintf(name, "stats.%d.key", m_index);
 if (!reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, &record->m_30, (void *)0x20 )) return false;
 sprintf(name, "stats.%d.value", m_index);
 reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, valueText, (void *)0x40 );
 sscanf(valueText, "%f", &value.number);
 record->m_value = value.bits;
 sprintf(name, "stats.%d.rank", m_index);
 record->m_rank = (int)(long)reinterpret_cast< BfmeThingRF * >( m_msg )->bfmeGoRF( (void *)name, (void *)0 );
 sprintf(name, "stats.%d.text", m_index);
 reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, record->m_addStat, (void *)0xff );
 ++m_index;
 return true;
}

// Retail 0x007F24A0: the per-stat addStats reader.  It formats the keys with
// the index the cursor has already stepped past (m_index - 1, read once) and
// the addStats counter in m_state, which it advances instead of m_index.
bool Rva007F2350StatsCursor::rva007F24A0(Rva007F2350StatsRecord *record)
{
 char name[0x40];
 char valueText[0x40];
 union { float number; int bits; } value;
 record->m_name[0] = 0;
 record->m_30 = 0;
 record->m_value = 0;
 record->m_addStat[0] = 0;
 record->m_rank = 0;
 int stat = m_index - 1;
 sprintf(name, "stats.%d.addStats.%d.value", stat, m_state);
 if (!reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, valueText, (void *)0x40 )) return false;
 sscanf(valueText, "%f", &value.number);
 record->m_value = value.bits;
 sprintf(name, "stats.%d.addStats.%d.key", stat, m_state);
 reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, &record->m_30, (void *)0x20 );
 sprintf(name, "stats.%d.addStats.%d.text", stat, m_state);
 reinterpret_cast< BfmeThingUPB * >( m_msg )->bfmeGoUPB( (void *)name, record->m_addStat, (void *)0xff );
 ++m_state;
 return true;
}
