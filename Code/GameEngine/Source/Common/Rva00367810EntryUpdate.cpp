// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Retail RVA 0x00367810, 164 bytes, thiscall, direct call through ILT thunk
// RVA 0x000159C9.  The sole caller in the image is phase 5 of
// GameLogic::update (RVA 0x0038DA10): at RVA 0x0038E17B,
// `lea ecx,[ebp+0x170]` passes the embedded GameLogic+0x170 store as this.
// The same member is built by the body at RVA 0x00366B90 (GameLogic ctor at
// RVA 0x00392B27), torn down by the body at RVA 0x003643C0 (GameLogic dtor at
// RVA 0x0038F220), and serviced in GameLogic::startNewGame by the body at
// RVA 0x00367470 (at RVA 0x00395E70), so +0x170 is one embedded store object.
//
// The body is gated by one virtual predicate and the Living World predicate,
// then walks the same 0x58-byte entry range used by the neighboring bodies.
// Flagged entries dispatch their own update; otherwise state 2 advances to 3
// once the simulation frame reaches the entry's frame.  The entries carry the
// LivingWorld reinforcement/auto-summon INI fields (RegionName,
// AddReinforcementArmy, Close/Medium/FarDistanceTime, AutoSummon) and the
// entry body formats retail's "Auto-Summoning army %s into battle" string, so
// the narrowest evidence-supported description is the embedded LivingWorld
// reinforcement-army (auto-summon) store.  Class and method names stay
// address-derived because the exact C++ class name is not proven.

class Rva00367810VirtualGate;

struct Rva00367810VirtualGateTable
{
	void *m_beforeTest[ 0x138 / sizeof( void * ) ];
	unsigned char (__fastcall *m_test)( Rva00367810VirtualGate *gate );
};

class Rva00367810VirtualGate
{
public:
	Rva00367810VirtualGateTable *m_table;
};

extern Rva00367810VirtualGate *Rva00367810TheVirtualGate;

class Rva00367810GameLogic
{
public:
	bool isLivingWorld();

	char         m_lead[ 0x3C ];
	unsigned int m_frame;
};

extern Rva00367810GameLogic *Rva00367810TheGameLogic;

class Rva00367810Entry
{
public:
	void update();

	char          m_lead[ 0x20 ];
	int           m_state;
	char          m_beforeFrame[ 4 ];
	unsigned int  m_frame;
	char          m_beforeFlag[ 0x20 ];
	unsigned char m_flag;
	char          m_tail[ 0x0B ];
};

class Rva00367810EntryRange
{
public:
	unsigned int size() const { return m_last - m_first; }
	Rva00367810Entry &operator[]( int index ) { return m_first[ index ]; }

private:
	Rva00367810Entry *m_first;
	Rva00367810Entry *m_last;
};

class Rva00367810Entries
{
public:
	void update();

private:
	char m_lead[ 0x18 ];
	Rva00367810EntryRange m_entries;
};

void Rva00367810Entries::update()
{
	Rva00367810VirtualGate *gate = Rva00367810TheVirtualGate;
	if( gate->m_table->m_test( gate ) )
		return;
	if( !Rva00367810TheGameLogic->isLivingWorld() )
		return;

	for( unsigned int index = 0; index < m_entries.size(); ++index )
	{
		Rva00367810Entry &entry = m_entries[ index ];
		if( entry.m_flag )
		{
			entry.update();
		}
		else if( entry.m_state == 2 &&
			Rva00367810TheGameLogic->m_frame >= entry.m_frame )
		{
			entry.m_state = 3;
		}
	}
}
