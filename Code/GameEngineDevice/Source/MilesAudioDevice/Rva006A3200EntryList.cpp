// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A3200, 71 bytes, between MilesAudioManager's sample-pool
// initialisers.  For kind >= 5 it passes its own `this` to ILT 0x00023F79
// (0x006955C0, ledger ?createVideoPlayer@W3DGameClient) for a fresh 0x18-byte
// entry, stamps +0x8 with the kind and +0x0 with 1, and
// push_backs it onto an STLport list at +0x4C.  No caller, vtable slot or
// string names the owner, so the names keep the address.  Retail's early
// ESI/EDI saves come from STLport list::push_back with exceptions off; a
// hand-written node insertion shrink-wraps them past the guard.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value );
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value );

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
	unsigned int getSoundClass( void ) const;

	char m_unmodelled04[ 0x28 - 4 ];
	int m_field28;
	char m_unmodelled2C[ 0x70 - 0x2C ];
};

class Rva006A1790RefCounted
{
public:
	virtual ~Rva006A1790RefCounted();

	void Add_Ref( void )
	{
		InterlockedIncrement( &m_refCount );
	}

	void Release_Ref( void )
	{
		if( InterlockedDecrement( &m_refCount ) <= 0 )
			delete this;
	}

private:
	long m_refCount;
};

// The counted base sits at +0x70, after the AudioEventRTS part that
// getSoundClass receives unadjusted.
class Rva006A1790Event : public AudioEventRTS, public Rva006A1790RefCounted
{
};

class Rva006A1790EventRef
{
public:
	Rva006A1790EventRef &operator=( const Rva006A1790EventRef &other )
	{
		if( this != &other )
		{
			if( other.m_ptr )
				other.m_ptr->Add_Ref();
			if( m_ptr )
				m_ptr->Release_Ref();
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	Rva006A1790Event *operator->( void ) const { return m_ptr; }

private:
	Rva006A1790Event *m_ptr;
};

struct Rva006A3200Entry
{
	unsigned int m_state;
	Rva006A1790EventRef m_event;
	unsigned int m_kind;
	unsigned char m_unmodelled0C[ 6 ];
	bool m_flag12;
	bool m_flag13;
	bool m_flag14;
	unsigned char m_unmodelled15[ 3 ];
};

class VideoPlayerInterface;

// The ILT target's ledger name.  Its constructor stores no vtable, so the
// returned object is modelled only by the fields this body writes.
class W3DGameClient
{
	friend class Rva006A3200Owner;

protected:
	virtual VideoPlayerInterface *createVideoPlayer();
};

class Rva006A3200Owner
{
public:
	bool pushEventEntry( const Rva006A1790EventRef &event, int mode );
	void pushNewEntry( unsigned int kind );

private:
	char m_unmodelled[ 0x4C ];
	_STL::list<Rva006A3200Entry *> m_entries;
	char m_unmodelled50[ 0x63C - 0x50 ];
	unsigned int m_classMask63C[ 3 ];
	unsigned int m_classMask648[ 3 ];
};

// Retail 0x006A1790, 195 bytes: the same entry source and list as
// 0x006A3200, with the entry holding a counted event reference whose
// sound class is tested against two per-index masks.
bool Rva006A3200Owner::pushEventEntry( const Rva006A1790EventRef &event, int mode )
{
	Rva006A3200Entry *entry = (Rva006A3200Entry *)
		( (W3DGameClient *)this )->W3DGameClient::createVideoPlayer();
	entry->m_event = event;
	entry->m_state = 0;
	if( mode == 1 )
		entry->m_flag14 = true;
	unsigned int soundClass = event->getSoundClass();
	if( m_classMask63C[ event->m_field28 ] & soundClass )
		entry->m_flag12 = true;
	if( m_classMask648[ event->m_field28 ] & soundClass )
		entry->m_flag13 = true;
	m_entries.push_back( entry );
	return true;
}

void Rva006A3200Owner::pushNewEntry( unsigned int kind )
{
	if( kind < 5 )
		return;
	Rva006A3200Entry *entry = (Rva006A3200Entry *)
		( (W3DGameClient *)this )->W3DGameClient::createVideoPlayer();
	entry->m_kind = kind;
	entry->m_state = 1;
	m_entries.push_back( entry );
}
