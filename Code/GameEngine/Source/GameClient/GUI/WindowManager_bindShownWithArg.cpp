// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// WindowManager stores each player-color callback with the argument that the
// callback receives. The callback map starts at WindowManager+0x1C.

#include "StringInline.h"
#include <hash_map>

class FunctorWrapperHead
{
public:
	virtual ~FunctorWrapperHead();

	int m_refCount;
};

class Rva0050F920FunctorHolder
{
public:
	Rva0050F920FunctorHolder( const Rva0050F920FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	~Rva0050F920FunctorHolder()
	{
		FunctorWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	FunctorWrapperHead *m_ptr;
};

struct Rva0046C2A0Mapped
{
	Rva0046C2A0Mapped() : m_ptr( 0 ), m_value( 0 ) {}

	Rva0046C2A0Mapped( const Rva0046C2A0Mapped &other )
		: m_ptr( other.m_ptr ), m_value( other.m_value )
	{
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	~Rva0046C2A0Mapped()
	{
		FunctorWrapperHead *p = m_ptr;
		if( p && ( p->m_refCount = p->m_refCount - 1 ) <= 0 )
			delete p;
	}

	FunctorWrapperHead *m_ptr;
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
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C2A0Map;

class WindowManager
{
public:
	void bindShownWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );

private:
	unsigned char m_pad[0x1C];
	Rva0046C2A0Map m_callbacks;
};

// ?bindShownWithArg@WindowManager@@QAEXABVAsciiString@@PAXVRva0050F920FunctorHolder@@@Z
void WindowManager::bindShownWithArg( const AsciiString &name, void *argument,
	Rva0050F920FunctorHolder callback )
{
	if( callback.m_ptr == 0 )
		return;

	Rva0046C2A0Mapped *slot = &m_callbacks[name];
	Rva0050F920FunctorHolder previous(
		*reinterpret_cast<Rva0050F920FunctorHolder *>( slot ) );
	if( previous.m_ptr != 0 )
		return;
	if( slot != reinterpret_cast<Rva0046C2A0Mapped *>( &callback ) )
	{
		if( callback.m_ptr )
			++callback.m_ptr->m_refCount;
		FunctorWrapperHead *old = slot->m_ptr;
		if( old && ( old->m_refCount = old->m_refCount - 1 ) <= 0 )
			delete old;
		slot->m_ptr = callback.m_ptr;
	}
	slot->m_value = argument;
}
