// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// WindowManager retains the first APT callback registered for each name.
// The APT callback table starts at WindowManager+0x30; the caller-side
// alternate name for this overload is the AptMapPreview registration ILT.

#include "StringInline.h"
#include <hash_map>

class BFMERetailAsciiString
{
private:
	void *m_data;
};

class Rva0046C540Counted
{
public:
	virtual void release( unsigned int deleting );

	int m_references;
};

class AptMapPreviewFunctorHolder
{
public:
	AptMapPreviewFunctorHolder( const AptMapPreviewFunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	~AptMapPreviewFunctorHolder()
	{
		Rva0046C540Counted *p = m_ptr;
		if( p && ( p->m_references = p->m_references - 1 ) <= 0 )
			p->release( 1 );
	}

	Rva0046C540Counted *m_ptr;
};

struct Rva0046C540Mapped
{
	Rva0046C540Mapped() : m_counted( 0 ) {}

	Rva0046C540Mapped( const Rva0046C540Mapped &other )
		: m_counted( other.m_counted )
	{
		if( m_counted )
			++m_counted->m_references;
	}

	~Rva0046C540Mapped()
	{
		if( m_counted && --m_counted->m_references <= 0 )
			m_counted->release( 1 );
	}

	Rva0046C540Counted *m_counted;
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
		int operator()( const AsciiString &left,
			const AsciiString &right ) const;
	};
}

typedef std::hash_map<AsciiString, Rva0046C540Mapped,
	rts::hash<AsciiString>, rts::equal_to<AsciiString> > Rva0046C540Map;

class WindowManager
{
public:
	void registerAptCallback( const BFMERetailAsciiString &name,
		AptMapPreviewFunctorHolder callback );

private:
	unsigned char m_pad[ 0x30 ];
	Rva0046C540Map m_callbacks;
};

// ?registerAptCallback@WindowManager@@QAEXABVBFMERetailAsciiString@@VAptMapPreviewFunctorHolder@@@Z
void WindowManager::registerAptCallback(
	const BFMERetailAsciiString &name,
	AptMapPreviewFunctorHolder callback )
{
	if( callback.m_ptr == 0 )
		return;

	Rva0046C540Map::iterator found = m_callbacks.find(
		reinterpret_cast<const AsciiString &>( name ) );
	if( found != m_callbacks.end() && (*found).second.m_counted != 0 )
		return;

	Rva0046C540Mapped *slot = &m_callbacks[
		reinterpret_cast<const AsciiString &>( name )];
	if( slot != reinterpret_cast<Rva0046C540Mapped *>( &callback ) )
	{
		++callback.m_ptr->m_references;

		Rva0046C540Counted *old = slot->m_counted;
		if( old && ( old->m_references = old->m_references - 1 ) <= 0 )
			old->release( 1 );

		slot->m_counted = callback.m_ptr;
	}
}
