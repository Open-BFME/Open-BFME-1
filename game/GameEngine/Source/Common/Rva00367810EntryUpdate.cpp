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
// The body at retail RVA 0x00367330 is the Rva00367810Entry::update method.
// The caller through ILT 0x0000E0AC and the retail string
// "Auto-Summoning army %s into battle" identify this entry's role.
//
// The neighboring body uses one virtual predicate and the Living World predicate,
// then walks the same 0x58-byte entry range used by the neighboring bodies.
// Flagged entries dispatch their own update; otherwise state 2 advances to 3
// once the simulation frame reaches the entry's frame.  The entries carry the
// LivingWorld reinforcement/auto-summon INI fields (RegionName,
// AddReinforcementArmy, Close/Medium/FarDistanceTime, AutoSummon) and the
// entry body formats retail's "Auto-Summoning army %s into battle" string, so
// the narrowest evidence-supported description is the embedded LivingWorld
// reinforcement-army (auto-summon) store.  The caller and reloc_names.csv
// establish Rva00367810Entry as the real class name for this method.

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

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

static __forceinline unsigned int rva00367810Frame(
	Rva00367810GameLogic *logic )
{
	return logic->m_frame;
}

template <typename T>
class StringBase
{
	friend class AsciiString;

	private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void __cdecl format( AsciiString format, ... );
};

class Rva00367810Campaign
{
public:
	void notify( const AsciiString &message );
};

extern void j_00026fc1();
extern void j_0003fe09();

#define Rva00367810TheCampaign (*(Rva00367810Campaign **)0x012F1028)

static __forceinline void rva00367810Notify(
	const AsciiString &message, Rva00367810Campaign *campaign )
{
	typedef void (Rva00367810Campaign::*Function)( const AsciiString & );
	union
	{
		void (*raw)( void );
		Function member;
	} function;
	function.raw = j_00026fc1;
	(campaign->*function.member)( message );
}

class Rva00367810Entry
{
public:
	void update();
	void finish( void *value, bool enabled );

	char          m_beforeName[ 0x10 ];
	void         *m_name;
	char          m_beforeState[ 0x0C ];
	int           m_state;
	unsigned int  m_delay;
	unsigned int  m_frame;
	unsigned int  m_startFrame;
	char          m_beforeFlag[ 0x1C ];
	unsigned char m_flag;
	char          m_tail[ 0x0B ];
};

static __forceinline void rva00367810Finish(
	Rva00367810Entry *entry, void *value, bool enabled )
{
	typedef void (Rva00367810Entry::*Function)( void *, bool );
	union
	{
		void (*raw)( void );
		Function member;
	} function;
	function.raw = j_0003fe09;
	(entry->*function.member)( value, enabled );
}

void Rva00367810Entry::update()
{
	AsciiString message;

	switch( m_state )
	{
	case 0:
		message.format( AsciiString( "Auto-Summoning army %s into battle" ),
			m_name != 0 ? (const char *)m_name + 8 :
			(const char *)0x0107388B );
		rva00367810Notify( message, Rva00367810TheCampaign );
		if( m_state == 0 )
		{
			m_state = 2;
			_ReadWriteBarrier();
			unsigned int frame = Rva00367810TheGameLogic->m_frame;
			// The clean C++ expression matches every other instruction but emits
			// add eax,ecx and stores EAX.  MSVC 7.1 needs these short asm blocks
			// to preserve retail's add ecx,eax register order.
			__asm
			{
				mov ecx, dword ptr [esi+24h]
			}
			m_startFrame = frame;
			__asm
			{
				mov edx, dword ptr Rva00367810TheGameLogic
				mov eax, dword ptr [edx+3Ch]
				add ecx, eax
				mov dword ptr [esi+28h], ecx
			}
		}
		break;

	case 2:
		if( rva00367810Frame( Rva00367810TheGameLogic ) < m_frame )
			break;
		m_state = 3;
		break;

	case 3:
		m_state = 4;
		rva00367810Finish( this, (char *)this + 0x3C, false );
		break;
	}
}

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
