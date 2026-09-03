// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x00464ED0 / 0x00464FE0. If g_theWindowManager is live, push the
// name onto the vector at this+4 (plain) or this+0x10 (with arg) and forward
// the by-value functor holder to the WindowManager helper.

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

class WindowManager
{
public:
	void bindShown( const AsciiString &name, Rva0050F8B0FunctorHolder callback );
	void bindShownWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );
};

extern WindowManager *g_theWindowManager;

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
	void _bfme_showAptScreenWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );

private:
	_STL::vector<AsciiString> m_names;
	_STL::vector<AsciiString> m_namesWithArg;
};

void _bfme_AptGameWindow::_bfme_showAptScreen( const AsciiString &name,
	Rva0050F8B0FunctorHolder callback )
{
	if( g_theWindowManager )
	{
		m_names.push_back( name );
		g_theWindowManager->bindShown( name, callback );
	}
}

void _bfme_AptGameWindow::_bfme_showAptScreenWithArg( const AsciiString &name,
	void *argument, Rva0050F920FunctorHolder callback )
{
	if( g_theWindowManager )
	{
		m_namesWithArg.push_back( name );
		g_theWindowManager->bindShownWithArg( name, argument, callback );
	}
}
