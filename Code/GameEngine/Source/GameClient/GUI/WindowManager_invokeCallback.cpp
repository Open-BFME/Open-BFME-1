// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// The callback map starts at WindowManager+0x08.  Retail builds a temporary
// string for the lookup, releases it, then invokes the stored callback.

#include "StringInline.h"
#include <exception>
#define private public
#include <hash_map>
#undef private

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class FunctorNotSet : public std::exception
{
public:
	FunctorNotSet() : std::exception() {}
};

class Rva0046C000Callback
{
public:
	virtual ~Rva0046C000Callback();
	virtual void invoke( void *argument );
};

struct Rva0046C000Mapped
{
	Rva0046C000Callback *m_callback;
};

namespace rts
{
template <class T> struct hash;
template <class T> struct equal_to;

template <> struct hash<AsciiString>
{
	unsigned int operator()( AsciiString value ) const;
};

template <> struct equal_to<AsciiString>
{
	int operator()( const AsciiString &left, const AsciiString &right ) const;
};
}

typedef std::hash_map<AsciiString, Rva0046C000Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C000Map;
typedef _STL::pair<const AsciiString, Rva0046C000Mapped> Rva0046C000Pair;
typedef _STL::_Hashtable_node<Rva0046C000Pair> Rva0046C000Node;

class WindowManager
{
public:
	void invokeCallback( const char *name, void *unused );

	private:
	unsigned char m_prefix[ 8 ];
	Rva0046C000Map m_callbacks;
};

// ?invokeCallback@WindowManager@@QAEXPBDPAX@Z
void WindowManager::invokeCallback( const char *name, void *unused )
{
	WindowManager *self = this;
	if( name == 0 )
		return;

	Rva0046C000Node *found;
	{
		BFMERetailAsciiString key( name );
		const Rva0046C000Map *map = &self->m_callbacks;
		found = map->_M_ht._M_find(
			reinterpret_cast<const AsciiString &>( key ) );
	}

	if( found != 0 )
	{
		Rva0046C000Callback *callback = found->_M_val.second.m_callback;
		if( callback == 0 )
			throw FunctorNotSet();
		callback->invoke( unused );
	}
}
