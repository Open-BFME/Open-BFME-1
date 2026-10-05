// cl: /O2 /GX- /GS
// Retail 0x0080A3C0 is the BfmeThingUNC PDAT/TADP dispatcher.  Its receiver
// is the registered object constructed at 0x00808FD0; the matched
// rva00809330 and rva00809400 siblings consume the live message and GID on
// the two response arms.  The remaining 0x008091C0 call is retained as an
// address-derived declaration-only helper with its direct ret-0xc ABI.

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();

	int m_field04;
};

class BfmeC994 : public Rva007E86B0Base
{
public:
	BfmeC994( char *buffer, int capacity );

	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_category;
	int m_field20;
	char m_pad24[ 0x0c ];
	char m_tail30;
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *one, void *two );
};

class BfmeThingRF
{
public:
	void *bfmeGoRF( void *one, void *two );
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *one, char *out, void *two );
};

class Rva00802680Owner
{
public:
	virtual ~Rva00802680Owner();
	virtual const char *name() = 0;
	virtual int get() const = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual const char *valueForKey( const char *key ) = 0;
	virtual void slot18() = 0;
	virtual int type() = 0;
};

class Rva00809330Sender
{
public:
	virtual void slot00();
	virtual const char *value( const char *key ) const;
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual const char *uid() const;
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual int count();
	virtual Rva00802680Owner *at( int index );
};

struct BfmeOwnerUNC
{
	char m_pad00[ 0x2b0 ];
	char m_pad2b0[ 0x28 ];
	Rva00809330Sender *m_sender;
};

struct Rva0080A3C0Input
{
	int m_field00;
	int m_field04;
	int m_field08;
	int m_field0c;
	char m_pad10[ 0x0c ];
	int m_field1c;
};

class Rva008091C0Owner
{
public:
	void handle( BfmeC994 *message, int gid, char *name );
};

struct Rva0080A680Input;
class BfmeThingUNC
{
public:
	void rva00809330( BfmeC994 *message, int gid );
	void rva00809400( BfmeC994 *message, int gid,
		Rva00802680Owner *player );
	void rva0080A3C0( Rva0080A3C0Input *input );
	void rva0080A680(Rva0080A680Input *input);

	void *m_vtable;
	int m_registrationValue;
	BfmeOwnerUNC *m_owner;
	char m_pad0c[ 4 ];
	void *m_routeOwner;
};

void *Rva007F93E0( void *message, void *route, void *owner );
extern const char g_feslTransactionIdKey[4];

void BfmeThingUNC::rva0080A3C0( Rva0080A3C0Input *input )
{
	char buffer[ 0x200 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	BfmeThingRF *sourceRF = reinterpret_cast< BfmeThingRF * >( input );
	BfmeThingCIB *messageCIB = reinterpret_cast< BfmeThingCIB * >( &message );

	message.m_category = input->m_field1c;
	void *value = sourceRF->bfmeGoRF( const_cast<char *>(g_feslTransactionIdKey), (void *)-1 );
	if( value != (void *)-1 )
		messageCIB->bfmeGoCIB( const_cast<char *>(g_feslTransactionIdKey), value );
	message.m_field04 = input->m_field04;
	message.m_field08 = input->m_field08;
	message.m_field0c = input->m_field0c;

	if( m_owner->m_sender == 0 )
	{
		message.m_field20 = 0x6e67616d;
		Rva007F93E0( &message, (void *)"->L", m_routeOwner );
		return;
	}

	int gid = (int)(long)sourceRF->bfmeGoRF( (void *)"GID", (void *)0 );
	char name[ 0x20 ];
	reinterpret_cast< BfmeThingUPB * >( input )->bfmeGoUPB(
		(void *)"I", name, (void *)0x20 );
	reinterpret_cast< Rva008091C0Owner * >( this )->handle(
		&message, gid, name );
	Rva007F93E0( &message, (void *)"->L", m_routeOwner );

	BfmeC994 second( buffer, sizeof( buffer ) );
	BfmeThingCIB *secondCIB = reinterpret_cast< BfmeThingCIB * >( &second );
	second.m_category = input->m_field1c;
	value = sourceRF->bfmeGoRF( const_cast<char *>(g_feslTransactionIdKey), (void *)-1 );
	if( value != (void *)-1 )
		secondCIB->bfmeGoCIB( const_cast<char *>(g_feslTransactionIdKey), value );
	second.m_field04 = input->m_field04;
	second.m_field08 = input->m_field08;
	second.m_field0c = input->m_field0c;
	second.m_category = 0x47444554;
	rva00809330( &second, gid );
	Rva007F93E0( &second, (void *)"->L", m_routeOwner );

	Rva00809330Sender *sender = m_owner->m_sender;
	int index = 0;
	int count = sender->count();
	while( index < count )
	{
		Rva00802680Owner *player = sender->at( index );
		if( player->type() == 4 )
		{
			BfmeC994 playerMessage( buffer, sizeof( buffer ) );
			BfmeThingCIB *playerCIB =
				reinterpret_cast< BfmeThingCIB * >( &playerMessage );
			playerMessage.m_category = input->m_field1c;
			value = sourceRF->bfmeGoRF( const_cast<char *>(g_feslTransactionIdKey), (void *)-1 );
			if( value != (void *)-1 )
				playerCIB->bfmeGoCIB( const_cast<char *>(g_feslTransactionIdKey), value );
			playerMessage.m_field04 = input->m_field04;
			playerMessage.m_field08 = input->m_field08;
			playerMessage.m_field0c = input->m_field0c;
			playerMessage.m_category = 0x50444154;
			rva00809400( &playerMessage, gid, player );
			Rva007F93E0( &playerMessage, (void *)"->L",
				m_routeOwner );
		}
		++index;
		count = sender->count();
	}
}

class Gen_007e86c0 { public: void m(); };
class Rva007E8810Message
{
public:
 Rva007E8810Message();
 ~Rva007E8810Message() { ((Gen_007e86c0 *)this)->m(); }
 unsigned m_00, m_04, m_08, m_0c, m_10, m_14, m_18, m_1c, m_20, m_24, m_28, m_2c;
 char m_30;
};
struct Rva0080A680Input { int m_00, m_04, m_08, m_0c, m_10, m_14, m_18, m_1c, m_20; };
struct Rva00800E50Header;
void Rva007F91D0(Rva00800E50Header *, const char *);
struct Rva00809500Entry;
struct Rva00809500Sink { void accept(Rva00809500Entry *); };
class Rva00809010Finder { public: Rva00809500Sink *find(Rva00809500Entry *); };
class Rva00809E40Owner { public: void rva00809E40(Rva007E8810Message *); };
struct Rva0080A110Message;
class Rva0080A110Owner { public: void route(Rva0080A110Message *); };
struct Rva0080A280Input;
class Rva0080A280Owner { public: void rva0080A280(Rva0080A280Input *); };
class Rva0080A680Forwarder
{
public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0c(Rva0080A680Input *);
};
class Rva0080A680Base { public: virtual void base00(); };
class Rva0080A680ForwarderOwner : public Rva0080A680Base, public Rva0080A680Forwarder {};
// Int3 at 0x0080A67F proves the start; final ret 4 at 0x0080A7D6
// is followed by seven int3 bytes. The vtable reference is VA 0x0112C83C.
void BfmeThingUNC::rva0080A680(Rva0080A680Input *input)
{
 bool response = (input->m_04 & 0x80000000) && (input->m_04 & 0x40000000);
 Rva007F91D0((Rva00800E50Header *)input, "<-L");
 Rva007E8810Message message;
 message.m_10 = input->m_08;
 message.m_14 = input->m_0c;
 message.m_20 = input->m_04;
 message.m_1c = input->m_00;
 message.m_04 = input->m_18;
 message.m_08 = input->m_1c;
 message.m_0c = input->m_20;
 if (!response) {
  if (message.m_1c != 0x474c5354) {
   ((Rva0080A680ForwarderOwner *)m_registrationValue)->slot0c(input);
   return;
  }
  Rva00809500Sink *sink = ((Rva00809010Finder *)this)->find((Rva00809500Entry *)&message);
  if (sink) sink->accept((Rva00809500Entry *)&message);
 } else {
  switch ((int)message.m_1c) {
   case 0x4547414d: ((Rva00809E40Owner *)this)->rva00809E40(&message); break;
   case 0x45434e4c: ((Rva0080A110Owner *)this)->route((Rva0080A110Message *)&message); break;
   case 0x47444154: rva0080A3C0((Rva0080A3C0Input *)&message); break;
   case 0x474c5354: ((Rva0080A280Owner *)this)->rva0080A280((Rva0080A280Input *)&message); break;
  }
 }
}
