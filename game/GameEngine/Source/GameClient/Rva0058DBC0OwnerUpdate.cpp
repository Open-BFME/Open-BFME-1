// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0058DDD0 (872 bytes).  Per-frame refresh of the resource-bar
// subobject whose destructor is 0x0058DBC0 (GameClient+0x460 holds it; the
// only caller is GameClient::update through ILT 0x00035431).  The +0x20 and
// +0x24 owning pointers are the two fields that destructor frees, one with
// and one without a null test.  The bodies it feeds are the palantir
// resource count (0x00565620), command points (0x00565940) and resource
// multiplier (0x00565A80) updates.  The owner and method names stay
// address-derived: no semantic class identity is proven.

extern void __cdecl operator delete( void *value ) throw();
extern void * __cdecl operator new( unsigned int size );

class PlayerTemplate
{
public:
	unsigned char m_beforePlayableSide[ 0xbd ];
	bool m_playableSide;
};

// Money is Snapshot-derived: the vftable sits at +0x0 and the count at +0x4.
class Money
{
public:
	unsigned int countMoney() const { return m_money; }

private:
	void *m_vftable;
	unsigned int m_money;
};

// Player+0x30; the two readers are reached only through their ILT thunks
// and carry no proven name (same spelling as ScriptActionsCounters.cpp).
class PlayerCommandPoints
{
};

class Player
{
public:
	bool isPlayerActive() const;
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Money *getMoney() { return &m_money; }
	PlayerCommandPoints *getCommandPoints() { return &m_commandPoints; }

private:
	void *m_vftable;
	const PlayerTemplate *m_playerTemplate;
	unsigned char m_beforeCommandPoints[ 0x30 - 0x08 ];
	PlayerCommandPoints m_commandPoints;
	unsigned char m_beforeMoney[ 0x48 - 0x31 ];
	Money m_money;
};

class PlayerList
{
};

extern PlayerList *ThePlayerList;

class Glo012F1028Type
{
public:
	int j_0000353f();

	unsigned char m_before2c[ 0x2c ];
	bool m_byte2c;
	bool m_byte2d;
};

extern Glo012F1028Type *Glo012F1028;

class BfmeCampaignManagerVictorious
{
public:
	unsigned char m_before1c[ 0x1c ];
	bool m_byte1c;
};

// The retail global at 0x012F1024 is EA's
// `LivingWorldCampaignManager *TheLivingWorldCampaignManager`, defined once in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldCampaignManager.cpp;
// BfmeCampaignManagerVictorious above is this TU's view of the object, cast at the use.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

static inline const BfmeCampaignManagerVictorious *livingWorldCampaignManagerView()
{
	return (const BfmeCampaignManagerVictorious *)TheLivingWorldCampaignManager;
}

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva006C9270GlobalData
{
	unsigned char m_beforeE70[ 0xe70 ];
	int m_int0E70;
	int m_int0E74;
};

static inline const Rva006C9270GlobalData *ownerUpdateGlobalData()
{
	return (const Rva006C9270GlobalData *)TheWritableGlobalData;
}

extern int __fastcall bfmeOffset( int base );
extern void __cdecl bfmeSetPalantirYW( int count );
extern void __cdecl Rva00564C70( bool value );
extern char __cdecl bfmePalantirCountZD( int count, int total );
extern char __cdecl bfmeMultiplierZC( float multiplier );

class Rva00564910
{
public:
	static void go();
};

// ILT thunks whose targets carry no proven identity: PlayerList local-player
// accessor (0x000DF860), the two command-point readers (0x000C7C10,
// 0x000C7BF0) and the living-world bounty percentage (0x003BDCF0).
extern void j_0000762b();
extern void j_00004e3f();
extern void j_0003deb0();
extern void j_00029cbc();

class Rva0058DDD0Call
{
};

static __forceinline Player *getLocalPlayer( PlayerList *list )
{
	typedef Player *( Rva0058DDD0Call::*Function )();
	union { void ( *raw )(); Function member; } fn;
	fn.raw = j_0000762b;
	return ( reinterpret_cast<Rva0058DDD0Call *>( list )->*fn.member )();
}

static __forceinline int rva000C7C10Get( PlayerCommandPoints *points )
{
	typedef int ( Rva0058DDD0Call::*Function )();
	union { void ( *raw )(); Function member; } fn;
	fn.raw = j_00004e3f;
	return ( reinterpret_cast<Rva0058DDD0Call *>( points )->*fn.member )();
}

static __forceinline int rva000C7BF0Get( PlayerCommandPoints *points )
{
	typedef int ( Rva0058DDD0Call::*Function )( int );
	union { void ( *raw )(); Function member; } fn;
	fn.raw = j_0003deb0;
	return ( reinterpret_cast<Rva0058DDD0Call *>( points )->*fn.member )( 1 );
}

static __forceinline int rva003BDCF0Get( Glo012F1028Type *logic )
{
	typedef int ( Rva0058DDD0Call::*Function )();
	union { void ( *raw )(); Function member; } fn;
	fn.raw = j_00029cbc;
	return ( reinterpret_cast<Rva0058DDD0Call *>( logic )->*fn.member )();
}

struct Rva0058DDD0CountAnim
{
	Rva0058DDD0CountAnim( int from, int to )
		: m_delay( 150 ), m_value( from ), m_delta( to - from ), m_accum( 0 )
	{
	}

	int m_delay;
	int m_value;
	int m_delta;
	int m_accum;
};

struct Rva0058DDD0MultiplierAnim
{
	Rva0058DDD0MultiplierAnim( float value )
		: m_delay( 180 ), m_hold( 56 ), m_value( value )
	{
	}

	int m_delay;
	int m_hold;
	float m_value;
};

class Rva0058DDD0CountHolder
{
public:
	Rva0058DDD0CountAnim *operator->() const { return m_data; }
	Rva0058DDD0CountAnim *get() const { return m_data; }

	void clear()
	{
		if( m_data )
			::operator delete( m_data );
		m_data = 0;
	}

	void reset( Rva0058DDD0CountAnim *data )
	{
		if( data != m_data )
		{
			if( m_data )
				::operator delete( m_data );
			m_data = data;
		}
	}

private:
	Rva0058DDD0CountAnim *m_data;
};

class Rva0058DDD0MultiplierHolder
{
public:
	Rva0058DDD0MultiplierAnim *operator->() const { return m_data; }
	Rva0058DDD0MultiplierAnim *get() const { return m_data; }

	void clear()
	{
		::operator delete( m_data );
		m_data = 0;
	}

	void reset( Rva0058DDD0MultiplierAnim *data )
	{
		if( data != m_data )
		{
			::operator delete( m_data );
			m_data = data;
		}
	}

private:
	Rva0058DDD0MultiplierAnim *m_data;
};

class Rva0058DBC0Owner
{
public:
	void rva0058DDD0();

private:
	int m_lastCount00;	// +0x00
	int m_lastPercent04;	// +0x04
	bool m_resourcesShown08;	// +0x08
	int m_shownResources0c;	// +0x0c
	int m_shownCount10;	// +0x10
	int m_shownTotal14;	// +0x14
	float m_shownMultiplier18;	// +0x18
	int m_int1c;	// +0x1c
	Rva0058DDD0CountHolder m_countAnim20;	// +0x20
	Rva0058DDD0MultiplierHolder m_multiplierAnim24;	// +0x24
};

void Rva0058DBC0Owner::rva0058DDD0()
{
	bool livingWorld = Glo012F1028 && Glo012F1028->m_byte2c && Glo012F1028->m_byte2d;

	Player *player = getLocalPlayer( ThePlayerList );
	bool moneyShown = false;
	int money = -1;
	if( player && player->isPlayerActive() && !livingWorld
		&& player->getPlayerTemplate() && player->getPlayerTemplate()->m_playableSide )
	{
		Money *wallet = player->getMoney();
		if( wallet )
		{
			money = wallet->countMoney();
			moneyShown = true;
		}
	}

	if( money != m_shownResources0c )
	{
		m_shownResources0c = money;
		bfmeSetPalantirYW( money );
	}

	if( moneyShown != m_resourcesShown08 )
	{
		Rva00564C70( moneyShown );
		m_resourcesShown08 = moneyShown;
	}

	int count = -1;
	int total = -1;
	if( !livingWorld )
	{
		m_countAnim20.clear();
		if( player && player->isPlayerActive()
			&& player->getPlayerTemplate() && player->getPlayerTemplate()->m_playableSide )
		{
			PlayerCommandPoints *points = player->getCommandPoints();
			count = rva000C7C10Get( points );
			total = rva000C7BF0Get( points );
		}
	}
	else
	{
		int value = Glo012F1028->j_0000353f();
		if( value != m_lastCount00 )
		{
			if( value > m_lastCount00 )
			{
				int from = bfmeOffset( m_lastCount00 );
				int to = bfmeOffset( value );
				m_countAnim20.reset( new Rva0058DDD0CountAnim( from, to ) );
			}
			m_lastCount00 = value;
		}

		int limit = m_lastCount00 + ( livingWorldCampaignManagerView()->m_byte1c
			? ownerUpdateGlobalData()->m_int0E74 : ownerUpdateGlobalData()->m_int0E70 );

		if( m_countAnim20.get() )
		{
			if( m_countAnim20->m_delay > 0 )
			{
				if( --m_countAnim20->m_delay == 0 )
					Rva00564910::go();
			}
			else
			{
				m_countAnim20->m_accum += m_countAnim20->m_delta;
				while( m_countAnim20->m_accum >= 66 )
				{
					m_countAnim20->m_value++;
					m_countAnim20->m_accum -= 66;
				}
			}

			count = m_countAnim20->m_value;
			if( count >= limit )
			{
				m_countAnim20.clear();
				count = limit;
			}
		}
		else
			count = limit;
		total = -1;
	}

	if( count != m_shownCount10 || m_shownTotal14 != total )
	{
		if( bfmePalantirCountZD( count, total ) )
		{
			m_shownCount10 = count;
			m_shownTotal14 = total;
		}
	}

	float multiplier;
	if( !livingWorld )
	{
		m_multiplierAnim24.clear();
		if( Glo012F1028 && Glo012F1028->m_byte2c )
			multiplier = rva003BDCF0Get( Glo012F1028 ) * 0.01f + 1.0f;
		else
			multiplier = 1.0f;
	}
	else
	{
		int percent = rva003BDCF0Get( Glo012F1028 );
		if( percent > m_lastPercent04 )
		{
			m_multiplierAnim24.reset( new Rva0058DDD0MultiplierAnim(
				m_lastPercent04 * 0.01f + 1.0f ) );
			m_lastPercent04 = percent;
		}

		if( m_multiplierAnim24.get() )
		{
			multiplier = m_multiplierAnim24->m_value;
			if( m_multiplierAnim24->m_delay > 0 )
			{
				if( --m_multiplierAnim24->m_delay == 0 )
					Rva00564910::go();
			}
			else if( --m_multiplierAnim24->m_hold <= 0 )
				m_multiplierAnim24.clear();
		}
		else
			multiplier = m_lastPercent04 * 0.01f + 1.0f;
	}

	if( multiplier != m_shownMultiplier18 )
	{
		if( bfmeMultiplierZC( multiplier ) )
			m_shownMultiplier18 = multiplier;
	}
}
