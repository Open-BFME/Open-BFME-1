// ?d_00803d30@@YAXXZ
// partial score=0.26 date=2026-09-25
// cl: /O2 /GX-
// Candidate for the FESL browser dispatch body at retail 0x00803D30.

class SnapshotDupReplica
{
public:
	virtual void handle();
};

class Rva007E8810Message : public SnapshotDupReplica
{
public:
	Rva007E8810Message();
	~Rva007E8810Message();
	int getInt( const char *key, int defaultValue );

	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	char m_30;
	char m_pad31[ 3 ];
};

struct Rva00809500Entry
{
	volatile int m_00;
	volatile int m_04;
	volatile int m_08;
	volatile int m_0c;
};

class BfmeSrc803A00 { public: int getInt( const char *, int ); };
class BfmeOwner803A00 { public: void go( BfmeSrc803A00 * ); };
class BfmeSrc803B60 { public: int getInt( const char *, int ); };
class BfmeOwner803B60 { public: void go( BfmeSrc803B60 * ); };
class BfmeSrc803BF0 { public: int getInt( const char *, int ); };
class BfmeOwner803BF0 { public: void go( BfmeSrc803BF0 * ); };
class BfmeSrc803C90 { public: int getInt( const char *, int ); };
class BfmeOwner803C90 { public: void go( BfmeSrc803C90 * ); };

class BfmeMsgVJI;
class BfmeThingVJI { public: void bfmeGoVJI( BfmeMsgVJI * ); };
class Rva00803620Getter;
class Rva00803620Host { public: void go( Rva00803620Getter * ); };
class BfmeGetterTCA;
class BfmeHostTCA { public: void bfmeGoTCA( BfmeGetterTCA * ); };
class Rva00803730Getter;
class Rva00803730Host { public: void go( Rva00803730Getter * ); };
class BfmeThingSA { };
class BfmeHostSA { public: void bfmeGoSA( BfmeThingSA * ); };
class BfmeThingSB { };
class BfmeHostSB { public: void bfmeGoSB( BfmeThingSB * ); };

class Rva00803620Sink
{
public:
	void rva0080AA80( Rva00809500Entry * );
};

class Rva00809BF0Owner
{
public:
	void notify( Rva00809500Entry * );
};

class LanTheaterEmulator
{
public:
	void notifyAddress( Rva00809500Entry * );
};

class Rva0080A940Owner
{
public:
	void initFromMessage( Rva007E8810Message * );
};

class Rva00803D30CallbackResult
{
public:
	int m_00;
};

class Rva00803D30Callback
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual Rva00803D30CallbackResult *accept( Rva00809500Entry * );
};

struct Rva00803D30State
{
	char m_pad00[ 0x2d8 ];
	Rva00803D30Callback *m_callback;
};

class Rva00803D30Fallback
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void *fallback( Rva00809500Entry * );
};

class Rva00803D30Owner
{
public:
	void *dispatch( Rva00809500Entry *entry );

	char m_pad00[ 8 ];
	char m_flag08;
	char m_pad09[ 3 ];
	Rva00803D30State *m_state;
	char m_pad10[ 4 ];
	Rva00803D30Fallback *m_fallback;
	void *m_sink;
};

void *Rva00803D30Owner::dispatch( Rva00809500Entry *entry )
{
	Rva007E8810Message message;
	message.m_14 = entry->m_0c;
	message.m_10 = entry->m_08;
	message.m_20 = entry->m_04;
	message.m_1c = entry->m_00;

	if( !m_flag08 )
	{
		if( message.m_1c <= 'RLST' )
		{
			switch( message.m_1c )
			{
			case 'LLST':
				reinterpret_cast< BfmeOwner803BF0 * >( this )->go(
					reinterpret_cast< BfmeSrc803BF0 * >( &message ) );
				return 0;
			case 'CONN':
				reinterpret_cast< BfmeOwner803A00 * >( this )->go(
					reinterpret_cast< BfmeSrc803A00 * >( &message ) );
				return 0;
			case 'RLST':
				reinterpret_cast< BfmeOwner803B60 * >( this )->go(
					reinterpret_cast< BfmeSrc803B60 * >( &message ) );
				return 0;
			}
		}
		else if( message.m_1c == 'USER' )
		{
			reinterpret_cast< BfmeThingVJI * >( this )->bfmeGoVJI(
				reinterpret_cast< BfmeMsgVJI * >( &message ) );
			return 0;
		}
	}

	int transaction = message.getInt( "TID", 0 );
	if( transaction == -2 )
	{
		if( message.m_1c <= 'GDAT' )
		{
			if( message.m_1c == 'EGAM' )
			{
				reinterpret_cast< Rva00803620Sink * >( m_sink )->rva0080AA80(
					reinterpret_cast< Rva00809500Entry * >( &message ) );
				return 0;
			}
			else if( message.m_1c == 'ECNL' )
			{
				reinterpret_cast< Rva00809BF0Owner * >( m_sink )->notify(
					reinterpret_cast< Rva00809500Entry * >( &message ) );
				return 0;
			}
			else if( message.m_1c == 'CGAM' )
			{
				reinterpret_cast< Rva00803620Host * >( this )->go(
					reinterpret_cast< Rva00803620Getter * >( &message ) );
				return 0;
			}
			else if( message.m_1c == 'GDAT' )
			{
				reinterpret_cast< LanTheaterEmulator * >( m_sink )->notifyAddress(
					reinterpret_cast< Rva00809500Entry * >( &message ) );
				return 0;
			}
		}
		else if( message.m_1c == 'GLST' )
		{
			reinterpret_cast< Rva0080A940Owner * >( m_sink )->initFromMessage(
				&message );
			return 0;
		}
		else if( message.m_1c == 'HGAM' )
		{
			reinterpret_cast< BfmeOwner803C90 * >( this )->go(
				reinterpret_cast< BfmeSrc803C90 * >( &message ) );
			return 0;
		}
		return 0;
	}

	Rva00803D30Callback *callback = m_state->m_callback;
	if( callback != 0 && callback->accept( entry )->m_00 == -2 )
	{
		if( message.m_1c <= 'PLVT' )
		{
			if( message.m_1c == 'PENT' )
			{
				reinterpret_cast< BfmeHostSA * >( this )->bfmeGoSA(
					reinterpret_cast< BfmeThingSA * >( &message ) );
				return 0;
			}
			else if( message.m_1c == 'EGRS' )
			{
				reinterpret_cast< Rva00803730Host * >( this )->go(
					reinterpret_cast< Rva00803730Getter * >( &message ) );
				return 0;
			}
			else if( message.m_1c == 'PLVT' )
			{
				reinterpret_cast< BfmeHostSB * >( this )->bfmeGoSB(
					reinterpret_cast< BfmeThingSB * >( &message ) );
				return 0;
			}
		}
		else if( message.m_1c == 'RGAM' )
		{
			reinterpret_cast< BfmeHostTCA * >( this )->bfmeGoTCA(
				reinterpret_cast< BfmeGetterTCA * >( &message ) );
			return 0;
		}
	}

	if( m_flag08 )
		return m_fallback->fallback( entry );
	return 0;
}
