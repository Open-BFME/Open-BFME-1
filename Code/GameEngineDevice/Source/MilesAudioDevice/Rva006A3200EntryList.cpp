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

struct Rva006A3200Entry
{
	unsigned int m_state;
	unsigned int m_unmodelled04;
	unsigned int m_kind;
	unsigned char m_unmodelled0C[ 0xC ];
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
	void pushNewEntry( unsigned int kind );

private:
	char m_unmodelled[ 0x4C ];
	_STL::list<Rva006A3200Entry *> m_entries;
};

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
