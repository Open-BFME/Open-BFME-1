// cl: /O2 /GS
// Retail 0x00809400 is reached directly from the PDAT branch in the complete
// 0x0080A3C0 dispatcher helper.  Its receiver is the registered BfmeThingUNC
// object constructed at 0x00808FD0.  The caller passes a live BfmeC994, the
// signed GID parsed by BfmeC994::getInt, and a polymorphic record selected by
// type 4.  This is the existing 0x38-byte Rva00802680Owner: its constructor at
// 0x00802640 installs vtable 0x0112C548 and its virtual destructor is matched.
// Slot +8 is the independently matched one-word by-value getter at 0x008022E0;
// here its value is written as PID.  Slots +4 and +0x14 supply NAME and the
// per-key player values.  No surviving public name identifies this private
// helper, so only the method name remains RVA-derived.

#include <stdio.h>

class BfmeC994
{
public:
	void addInt( const char *key, int value );
	void addString( const char *key, const char *value );
};

class GetterWord
{
public:
	int m_value;
};

class Rva00802680Owner
{
public:
	virtual ~Rva00802680Owner();
	virtual const char *name() = 0;
	virtual GetterWord get() const = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual const char *valueForKey( const char *key ) = 0;
	virtual void slot18() = 0;
	virtual int type() = 0;
};

struct Rva00809400Attribute
{
	const char *m_key;
	int m_tag;
};

struct Rva00809400Attributes
{
	__forceinline const Rva00809400Attribute *at( int index ) const
	{
		if( index >= m_count )
			return 0;
		return m_data + index;
	}

	Rva00809400Attribute *m_data;
	int m_count;
};

struct Rva00809330Attribute
{
	const char *m_key;
	int m_tag;
};

struct Rva00809330Attributes
{
	__forceinline const Rva00809330Attribute *at( int index ) const
	{
		if( index >= m_count )
			return 0;
		return m_data + index;
	}

	Rva00809330Attribute *m_data;
	int m_count;
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
};

struct BfmeOwnerUNC
{
	char m_opaque000[ 0x2B0 ];
	Rva00809330Attributes m_gameAttributes;
	Rva00809400Attributes m_playerAttributes;
	char m_opaque2C0[ 0x18 ];
	Rva00809330Sender *m_sender;
};

class BfmeThingUNC
{
public:
	void rva00809330( BfmeC994 *message, int gid );
	void rva00809400( BfmeC994 *message, int gid,
		Rva00802680Owner *player );

	void *m_vtable;
	int m_registrationValue;
	BfmeOwnerUNC *m_owner;
};

void BfmeThingUNC::rva00809330( BfmeC994 *message, int gid )
{
	Rva00809330Sender const *sender = m_owner->m_sender;

	message->addInt( "LID", -2 );
	message->addInt( "GID", gid );

	Rva00809330Attributes *attributes = &m_owner->m_gameAttributes;
	int count = attributes->m_count;
	for( int index = 0; index < count; ++index )
	{
		char key[ 0x40 ];
		const char *attribute = attributes->at( index )->m_key;
		sprintf( key, "D-%.60s", attribute );
		message->addString( key, sender->value( attribute ) );
	}

	message->addString( "UGID", sender->uid() );
}

void BfmeThingUNC::rva00809400( BfmeC994 *message, int gid,
	Rva00802680Owner *player )
{
	GetterWord pid = player->get();

	message->addInt( "LID", -2 );
	message->addInt( "GID", gid );
	message->addInt( "PID", pid.m_value );
	message->addString( "NAME", player->name() );
	message->addInt( "UID", 0 );

	const Rva00809400Attributes *attributes = &m_owner->m_playerAttributes;
	int count = attributes->m_count;
	for( int index = 0; index < count; ++index )
	{
		char key[ 0x40 ];
		const char *attribute = attributes->at( index )->m_key;
		sprintf( key, "P-%.60s", attribute );
		message->addString( key, player->valueForKey( attribute ) );
	}
}
