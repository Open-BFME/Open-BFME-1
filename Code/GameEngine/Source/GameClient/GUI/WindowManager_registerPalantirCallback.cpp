// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// WindowManager keeps the first Palantir callback registered for each name.
// Retail stores the callback map at WindowManager+0x94.

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

struct Rva0046AF20Mapped
{
	Rva0046AF20Mapped() : m_ptr( 0 ) {}
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

typedef std::hash_map<AsciiString, Rva0046AF20Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046AF20Map;

class WindowManager
{
public:
	void registerPalantirCallback( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );

private:
	unsigned char m_pad[0x94];
	Rva0046AF20Map m_callbacks;
};

// ?registerPalantirCallback@WindowManager@@QAEXABVAsciiString@@VRva0050F8B0FunctorHolder@@@Z
void WindowManager::registerPalantirCallback( const AsciiString &name,
	Rva0050F8B0FunctorHolder callback )
{
	if( callback.m_ptr == 0 )
		return;

	Rva0046AF20Mapped *slot = &m_callbacks[name];
	if( slot->m_ptr != 0 )
		return;

	if( slot != reinterpret_cast<Rva0046AF20Mapped *>( &callback ) )
	{
		FunctorWrapperHead *incoming = callback.m_ptr;
		if( incoming )
			++incoming->m_refCount;
		FunctorWrapperHead *old = slot->m_ptr;
		if( old && ( old->m_refCount = old->m_refCount - 1 ) <= 0 )
			delete old;
		slot->m_ptr = incoming;
	}
}
