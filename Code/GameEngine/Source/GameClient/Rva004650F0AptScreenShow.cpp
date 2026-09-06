// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// Near-twin of _bfme_AptGameWindow::_bfme_showAptScreen (twin 0x00464ED0,
// AptScreenShow.cpp): identical push-name-then-forward shape, but the vector
// member sits at +0x1C here instead of +4, and the forwarded call reaches a
// different WindowManager helper (retail 0x0000F31C, still an unclaimed
// dump; address-derived name). 0x18 bytes of unclaimed fields precede the
// vector on this sibling window class.

#include "StringInline.h"
#include <vector>

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

class WindowManager
{
public:
	void bfmeBindRva004650F0( const AsciiString &name, Rva0050F8B0FunctorHolder callback );	///< retail 0x0000F31C
};

extern WindowManager *g_theWindowManager;

class Rva004650F0GameWindow
{
public:
	virtual ~Rva004650F0GameWindow();
	void showAptScreenRva004650F0( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );

private:
	unsigned char m_pad[0x18];
	_STL::vector<AsciiString> m_names;
};

// address-derived: real ZH method name not recovered
void Rva004650F0GameWindow::showAptScreenRva004650F0( const AsciiString &name,
	Rva0050F8B0FunctorHolder callback )
{
	if( g_theWindowManager )
	{
		m_names.push_back( name );
		g_theWindowManager->bfmeBindRva004650F0( name, callback );
	}
}
