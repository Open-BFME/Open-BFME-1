// cl: /GS
// 0x007F7DA0: FESL game-browser ticket update on the BfmeThingZI entry table.

#include <string.h>

class Rva007E8810Message;

void Rva007E8640Copy( char *destination, unsigned size, const char *source );

class Rva007FC020Ticket
{
public:
	Rva007FC020Ticket( Rva007E8810Message *msg );

	int m_lid;
	int m_gid;
	int m_pid;
	int m_p;
	char m_ticket[ 0x80 ];
	char m_reason[ 0x100 ];
	char m_i[ 0x20 ];
	char m_host[ 0x20 ];
	char m_platform[ 0x10 ];
	char m_ugid[ 0x25 ];
};

class Rva00800290Buffer
{
public:
	void append( const char *text );

	char *m_ptr;
	int m_size;
};

class BfmeOwnerYA
{
public:
	void bfmeParseYA( const char *text );

	char m_pad[ 0x68 ];
	int m_value;
};

class Rva007E8760Addr
{
public:
	void parse( const char *text, int extra );

	char m_pad[ 8 ];
	unsigned m_address;
	int m_extra;
};

class BfmeE1029
{
public:
	void bfmeGo1029E( char *text, int value );

	char m_pad[ 8 ];
	char m_text[ 0x1c ];
	int m_value;
};

struct BfmeEntryZI
{
	char m_head[ 8 ];
	int m_bfmeUsed;
	int m_value0c;
	int m_value10;
	unsigned char m_value14;
	char m_pad15[ 3 ];
	int m_value18;
	Rva00800290Buffer m_buffer;
	int m_bfmeOther;
	int m_bfmeKey;
	Rva007E8760Addr m_address;
	BfmeE1029 m_text;
	void *m_current;
	char m_pad68[ 4 ];
	char m_ugid[ 0x25 ];
	char m_tail91[ 3 ];
};

class BfmeListenerZI
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void onEntry( BfmeEntryZI *entry, int value );
};

class Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail( const char *expression, const char *file, int line );
};

extern int Rva007EB810Get();

class Rva00800920Owner
{
public:
	int rva00800a40( void *input, unsigned char flag, int value );
};

class BfmeThingZI
{
public:
	__declspec( noinline ) BfmeEntryZI *bfmeFindZI( int key, int other );
	void rva007F7DA0( Rva007E8810Message *msg );

	char m_pad00[ 0x1c ];
	BfmeListenerZI *m_listener;
	char m_pad20[ 4 ];
	Rva00800920Owner *m_owner;
	char m_pad28[ 0x30 ];
	BfmeEntryZI m_bfmeEntries[ 4 ];
};

BfmeEntryZI *BfmeThingZI::bfmeFindZI( int key, int other )
{
	BfmeEntryZI *at = m_bfmeEntries;
	BfmeEntryZI *end = m_bfmeEntries + 4;
	while( at < end )
	{
		if( at->m_bfmeUsed != 0 && at->m_bfmeKey == key && at->m_bfmeOther == other )
			return at;
		++at;
	}
	return 0;
}

// ?rva007F7DA0@BfmeThingZI@@QAEXPAVRva007E8810Message@@@Z
void BfmeThingZI::rva007F7DA0( Rva007E8810Message *msg )
{
	BfmeThingZI *self = this;
	Rva007FC020Ticket ticket( msg );
	int lid = ticket.m_lid;
	BfmeEntryZI *entry = self->bfmeFindZI( lid, ticket.m_gid );

	if( entry == 0 )
	{
		reinterpret_cast<Rva007EB810Diag *>(Rva007EB810Get())->fail(
			"peri",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowser.cpp",
			0x59f );
	}
	else
	{
		int ticketLength = strlen( ticket.m_ticket );
		if( ticketLength == 0 )
		{
			entry->m_bfmeUsed = 0;
			((BfmeOwnerYA *)entry)->bfmeParseYA( ticket.m_reason );
			self->m_listener->onEntry( entry, 0x6a64656e );
			entry->m_bfmeUsed = 0;
			entry->m_value0c = 0;
			entry->m_value10 = 0;
			entry->m_value14 = 0;
			entry->m_value18 = 0;
			entry->m_buffer.append( (const char *)0x0107301c );
			entry->m_bfmeOther = 0;
			entry->m_bfmeKey = 0;
			entry->m_ugid[ 0 ] = 0;
		}
		else
		{
			bool notifyOwner;
			if( entry->m_value14 == 0 )
			{
				notifyOwner = true;
				if( lid == -2 )
					notifyOwner = false;
			}
			else
				notifyOwner = false;

			entry->m_bfmeUsed = 4;
			entry->m_value18 = ticket.m_pid;
			entry->m_buffer.append( ticket.m_ticket );
			Rva007E8640Copy( entry->m_ugid, 0x25, ticket.m_ugid );

			if( ticket.m_host[ 0 ] != 0 )
			{
				((BfmeE1029 *)( (char *)entry + 0x3c ))->bfmeGo1029E(
					ticket.m_host, ticket.m_p );
				entry->m_current = (void *)((char *)entry + 0x3c);
			}
			else
			{
				((Rva007E8760Addr *)( (char *)entry + 0x2c ))->parse(
					ticket.m_i, ticket.m_p );
				entry->m_current = (void *)((char *)entry + 0x2c);
			}
			if( !notifyOwner )
			{
				entry->m_bfmeUsed = 5;
				self->m_listener->onEntry( entry, 0 );
			}
			else
			{
				self->m_listener->onEntry( entry, 0 );
				self->m_owner->rva00800a40( entry->m_current, 1, (int)entry );
			}
		}
	}
}
