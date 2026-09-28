// cl: /O2 /GX-
// Retail 0x00803D30, 734 bytes: slot 3 of vtable 0x0112C738, the FESL message
// dispatcher of the browser owner whose matched constructor (0x00803820) and
// destructor (0x00803890) install that vtable. The owner keeps its
// address-derived name; the layout (flag +8, owner +0xC, peer +0x14, child
// +0x18) is the one those two matched bodies witness. Every callee keeps the
// class name its matched ledger row or pin carries; "LID" is the retail
// literal at 0x0112B52C. The owner's sender at +0x2D8 is the BfmeOwnerUNC
// field the matched 0x0080A3C0 dispatcher reads; its slot 9 returns a value
// object by hidden pointer, which retail builds in the dead entry slot.
// Arms: 'LLST' 'CONN' 'RLST' 'USER' while unconnected; LID == -2 routes
// 'EGAM' 'ECNL' 'CGAM' 'GDAT' 'HGAM' 'GLST'; a -2 sender result routes 'PENT'
// 'EGRS' 'PLVT' 'RGAM'; otherwise a connected owner forwards to its peer.

struct Rva00809500Entry
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
};

// FESL message (ctor 0x007E8810, dtor 0x007E86C0, getInt 0x007E8900).
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
	int m_code;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	char m_30;
};

class BfmeSrc803A00;
class BfmeOwner803A00 { public: void go( BfmeSrc803A00 * ); };
class BfmeSrc803B60;
class BfmeOwner803B60 { public: void go( BfmeSrc803B60 * ); };
class BfmeSrc803BF0;
class BfmeOwner803BF0 { public: void go( BfmeSrc803BF0 * ); };
class BfmeSrc803C90;
class BfmeOwner803C90 { public: void go( BfmeSrc803C90 * ); };
class BfmeMsgVJI;
class BfmeThingVJI { public: void bfmeGoVJI( BfmeMsgVJI * ); };
class Rva00803620Getter;
class Rva00803620Host { public: void go( Rva00803620Getter * ); };
class BfmeGetterTCA;
class BfmeHostTCA { public: void bfmeGoTCA( BfmeGetterTCA * ); };
class Rva00803730Getter;
class Rva00803730Host { public: void go( Rva00803730Getter * ); };
class BfmeThingSA;
class BfmeHostSA { public: void bfmeGoSA( BfmeThingSA * ); };
class BfmeThingSB;
class BfmeHostSB { public: void bfmeGoSB( BfmeThingSB * ); };

class Rva00803620Sink { public: void rva0080AA80( Rva00809500Entry * ); };
class Rva00809BF0Owner { public: void notify( Rva00809500Entry * ); };
class LanTheaterEmulator { public: void notifyAddress( Rva00809500Entry * ); };
class Rva0080A940Owner { public: void initFromMessage( Rva007E8810Message * ); };

// Returned by value from the sender's slot 9; -2 means "not ours".
class Rva00803D30Result
{
public:
	Rva00803D30Result( const Rva00803D30Result &other ) : m_value( other.m_value ) {}
	int m_value;
};

class Rva00809330Sender
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual Rva00803D30Result slot24();
};

struct BfmeOwnerUNC
{
	char m_pad00[ 0x2d8 ];
	Rva00809330Sender *m_sender;
};

class Rva00803890Peer
{
public:
	virtual void v0();
	virtual void release( void *p );
	virtual void v8();
	virtual int slot0C( Rva00809500Entry *entry );
};

class Rva00803890Owner
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual int dispatch( Rva00809500Entry *entry );

	void *m_vt2;
	unsigned char m_flag;
	unsigned char m_connected;
	unsigned char m_padding[2];
	BfmeOwnerUNC *m_owner;
	int m_registry;
	Rva00803890Peer *m_peer;
	void *m_child;
};

int Rva00803890Owner::dispatch( Rva00809500Entry *entry )
{
	Rva007E8810Message message;
	message.m_10 = entry->m_08;
	message.m_14 = entry->m_0c;
	message.m_20 = entry->m_04;
	message.m_code = entry->m_00;

	if( !m_flag )
	{
		switch( message.m_code )
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
		case 'USER':
			reinterpret_cast< BfmeThingVJI * >( this )->bfmeGoVJI(
				reinterpret_cast< BfmeMsgVJI * >( &message ) );
			return 0;
		}
	}

	if( message.getInt( "LID", 0 ) == -2 )
	{
		switch( message.m_code )
		{
		case 'EGAM':
			reinterpret_cast< Rva00803620Sink * >( m_child )->rva0080AA80(
				reinterpret_cast< Rva00809500Entry * >( &message ) );
			return 0;
		case 'ECNL':
			reinterpret_cast< Rva00809BF0Owner * >( m_child )->notify(
				reinterpret_cast< Rva00809500Entry * >( &message ) );
			return 0;
		case 'CGAM':
			reinterpret_cast< Rva00803620Host * >( this )->go(
				reinterpret_cast< Rva00803620Getter * >( &message ) );
			return 0;
		case 'GDAT':
			reinterpret_cast< LanTheaterEmulator * >( m_child )->notifyAddress(
				reinterpret_cast< Rva00809500Entry * >( &message ) );
			return 0;
		case 'HGAM':
			reinterpret_cast< BfmeOwner803C90 * >( this )->go(
				reinterpret_cast< BfmeSrc803C90 * >( &message ) );
			return 0;
		case 'GLST':
			reinterpret_cast< Rva0080A940Owner * >( m_child )->initFromMessage(
				&message );
			return 0;
		}
		return 0;
	}

	Rva00809330Sender *sender = m_owner->m_sender;
	if( sender != 0 && sender->slot24().m_value == -2 )
	{
		switch( message.m_code )
		{
		case 'PENT':
			reinterpret_cast< BfmeHostSA * >( this )->bfmeGoSA(
				reinterpret_cast< BfmeThingSA * >( &message ) );
			return 0;
		case 'EGRS':
			reinterpret_cast< Rva00803730Host * >( this )->go(
				reinterpret_cast< Rva00803730Getter * >( &message ) );
			return 0;
		case 'PLVT':
			reinterpret_cast< BfmeHostSB * >( this )->bfmeGoSB(
				reinterpret_cast< BfmeThingSB * >( &message ) );
			return 0;
		case 'RGAM':
			reinterpret_cast< BfmeHostTCA * >( this )->bfmeGoTCA(
				reinterpret_cast< BfmeGetterTCA * >( &message ) );
			return 0;
		}
		return 0;
	}

	if( m_flag )
		return m_peer->slot0C( entry );
	return 0;
}
