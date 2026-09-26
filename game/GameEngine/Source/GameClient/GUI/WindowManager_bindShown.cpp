// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// WindowManager keeps a second callback map -- the plain (no-argument) one --
// at WindowManager+0x08, separate from the with-arg map at +0x1C that
// WindowManager_bindShownWithArg.cpp already carries. Both maps share the
// exact same mapped_type instantiation the hash_map helper at 0x0046D0C0
// encodes (Rva0046C000Mapped, from game/GameEngine/Source/Common/
// Rva0046C2A0HashIndex.cpp's explicit `template Rva0046C000Mapped &
// Rva0046C000Map::operator[]`), so this map has to reuse that exact class
// name for the operator[] call to resolve to the landed body. The mangled
// symbol itself is already pinned in targets/game/reverse/symbols.csv:
//   ?bindShown@WindowManager@@QAEXABVAsciiString@@VRva0050F8B0FunctorHolder@@@Z
// -- the same Rva0050F8B0FunctorHolder declared (opaquely) by
// game/GameEngine/Source/GameClient/GUI/AptScreenShow.cpp's showAptScreen.

#include "StringInline.h"
#include <hash_map>

class FunctorWrapperHead
{
public:
	virtual ~FunctorWrapperHead();

	int m_refCount;
};

class Rva0050F8B0FunctorHolder
{
public:
	Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	~Rva0050F8B0FunctorHolder()
	{
		FunctorWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	FunctorWrapperHead *m_ptr;
};

// Same shape as Rva0050F8B0FunctorHolder -- one refcounted pointer -- but
// named to match the explicit hash_map<AsciiString, Rva0046C000Mapped, ...>
// instantiation the 0x0046D0C0 operator[] body already encodes.
struct Rva0046C000Mapped
{
	Rva0046C000Mapped() : m_ptr( 0 ) {}

	Rva0046C000Mapped( const Rva0046C000Mapped &other ) : m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	~Rva0046C000Mapped()
	{
		FunctorWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	FunctorWrapperHead *m_ptr;
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

class WindowManager
{
public:
	void bindShown( const AsciiString &name, Rva0050F8B0FunctorHolder callback );

private:
	unsigned char m_pad[0x08];
	Rva0046C000Map m_shownCallbacks;
};

// ?bindShown@WindowManager@@QAEXABVAsciiString@@VRva0050F8B0FunctorHolder@@@Z
void WindowManager::bindShown( const AsciiString &name, Rva0050F8B0FunctorHolder callback )
{
	if( callback.m_ptr == 0 )
		return;

	Rva0046C000Mapped *slot = &m_shownCallbacks[name];
	Rva0050F8B0FunctorHolder previous(
		*reinterpret_cast<Rva0050F8B0FunctorHolder *>( slot ) );
	if( previous.m_ptr != 0 )
		return;

	slot = &m_shownCallbacks[name];
	if( slot != reinterpret_cast<Rva0046C000Mapped *>( &callback ) )
	{
		if( callback.m_ptr )
			++callback.m_ptr->m_refCount;
		FunctorWrapperHead *old = slot->m_ptr;
		if( old && ( old->m_refCount = old->m_refCount - 1 ) <= 0 )
			delete old;
		slot->m_ptr = callback.m_ptr;
	}
}
