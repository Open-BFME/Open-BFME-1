// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// The callback map starts at WindowManager+0x08.  Retail builds a temporary
// string for the lookup, releases it, then invokes the stored callback.

#include "StringInline.h"
#include <exception>
#include <hash_map>

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
		found = map->find(
			reinterpret_cast<const AsciiString &>( key ) )._M_cur;
	}

	if( found != 0 )
	{
		Rva0046C000Callback *callback = found->_M_val.second.m_callback;
		if( callback == 0 )
			throw FunctorNotSet();
		callback->invoke( unused );
	}
}

struct Rva0046CA40Result
{
	Rva0046CA40Result(float value, int arg) : threshold(value), m_arg(arg) {}
	float threshold;
	int m_arg;
};

class Rva0046CA40Callback
{
public:
	virtual ~Rva0046CA40Callback();
	virtual Rva0046CA40Result invoke(const char *key);
};

struct Rva0046AF20Mapped
{
	Rva0046CA40Callback *m_ptr;
};

typedef std::hash_map<AsciiString, Rva0046AF20Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046AF20Map;
typedef _STL::pair<const AsciiString, Rva0046AF20Mapped> Rva0046AF20Pair;
typedef _STL::_Hashtable_node<Rva0046AF20Pair> Rva0046AF20Node;

extern const char *__cdecl bfmeSkipLevelPrefix(const char *key);

// The caller's manager global differs from TheWindowManager.  The body proves
// the callback-map layout and result ABI, but not the original owner name.
class Rva0046CA40Owner
{
public:
	Rva0046CA40Result lookupThreshold_0046CA40(const char *name);

private:
	unsigned char m_prefix[0x94];
	Rva0046AF20Map m_callbacks;
};

Rva0046CA40Result Rva0046CA40Owner::lookupThreshold_0046CA40(const char *name)
{
	const char *keyName = bfmeSkipLevelPrefix(name);
	Rva0046AF20Node *found;
	{
		BFMERetailAsciiString key(keyName);
		const Rva0046AF20Map *map = &m_callbacks;
		found = map->find(reinterpret_cast<const AsciiString &>(key))._M_cur;
	}
	if (found != 0) {
		Rva0046CA40Callback *callback = found->_M_val.second.m_ptr;
		if (callback == 0)
			throw FunctorNotSet();
		return callback->invoke(keyName);
	}
	return Rva0046CA40Result(1.0f, 0);
}
