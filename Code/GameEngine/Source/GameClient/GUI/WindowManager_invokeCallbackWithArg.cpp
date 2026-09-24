// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// The argument-carrying callback map at WindowManager+0x1C (filled by
// bindShownWithArg).  The only caller, the static wrapper at 0x007832B0, loads
// ECX from g_theWindowManager (0x012F19E8) and calls ILT 0x000095A2.  Retail
// looks the name up, retries without the level prefix, then invokes the
// stored functor (vtable slot 1) with the stored argument.  The method's own
// name is not proven, so it keeps its address.

#include "StringInline.h"
#include <exception>
#include <hash_map>

class FunctorNotSet : public std::exception
{
public:
	FunctorNotSet() : std::exception() {}
};

class FunctorWrapperHead
{
public:
	virtual ~FunctorWrapperHead();
	virtual void invoke( void *argument, void *context, int flag );

	int m_refCount;
};

struct Rva0046C2A0Mapped
{
	FunctorWrapperHead *m_callback;
	void *m_value;
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

typedef std::hash_map<AsciiString, Rva0046C2A0Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > CallbackWithArgumentMap;

extern const char *__cdecl bfmeSkipLevelPrefix( const char *key );

class WindowManager
{
public:
	void invokeCallbackWithArg_0046CE60( const char *name, void *context );

private:
	unsigned char m_pad[0x1C];
	CallbackWithArgumentMap m_callbacks;
};

void WindowManager::invokeCallbackWithArg_0046CE60( const char *name, void *context )
{
	CallbackWithArgumentMap::iterator it = m_callbacks.find( AsciiString( name ) );
	if( it == m_callbacks.end() )
		it = m_callbacks.find( AsciiString( bfmeSkipLevelPrefix( name ) ) );
	if( it != m_callbacks.end() )
	{
		void *argument = it->second.m_value;
		FunctorWrapperHead *callback = it->second.m_callback;
		if( callback == 0 )
			throw FunctorNotSet();
		callback->invoke( argument, context, 1 );
	}
}
