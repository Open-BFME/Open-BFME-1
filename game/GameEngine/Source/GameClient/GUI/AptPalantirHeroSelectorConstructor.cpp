// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <algorithm>
#include <list>

#include "ascii_string.h"

template <typename T> class BannerStringBase
{
	friend class BFMERetailAsciiString;

private:
	BannerStringBase( const T *text );
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	BFMERetailAsciiString( const char *text )
	{
		((BannerStringBase<char> *)this)->BannerStringBase<char>::BannerStringBase( text );
	}
	~BFMERetailAsciiString() { releaseBuffer(); }

	void __cdecl format( BFMERetailAsciiString format, ... );

private:
	void releaseBuffer();
	void *m_data;
};

class __single_inheritance FunctorTargetSingle
{
};
typedef void (FunctorTargetSingle::*FunctorMethodSingle)( void );

struct FunctorBindingSingle
{
	FunctorBindingSingle( FunctorMethodSingle method, FunctorTargetSingle *target )
		: m_target( target ), m_method( method ) {}

	FunctorTargetSingle *m_target;
	FunctorMethodSingle m_method;
};

struct Gen_p24pod
{
	int a[ 5 ];
	unsigned char first;
	unsigned char second;
};

class FunctorSingleWrapperHead
{
public:
	FunctorSingleWrapperHead() : m_refCount( 0 ) {}
	virtual void functorSingleWrapperAnchor();

	unsigned int m_refCount;
};

class Rva0058D030FunctorSingleWrapper : public FunctorSingleWrapperHead
{
public:
	Rva0058D030FunctorSingleWrapper( const FunctorBindingSingle &binding )
		: m_binding( binding ) {}

	FunctorBindingSingle m_binding;
};

class Rva0058D070FunctorSingleWrapper : public FunctorSingleWrapperHead
{
public:
	Rva0058D070FunctorSingleWrapper( const FunctorBindingSingle &binding )
		: m_binding( binding ) {}

	FunctorBindingSingle m_binding;
};

class Rva0050F8B0FunctorHolder
{
public:
	Rva0050F8B0FunctorHolder( FunctorBindingSingle binding )
	{
		m_ptr = new Rva0058D070FunctorSingleWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	FunctorSingleWrapperHead *m_ptr;
};

class BannerAptCallbackHolder
{
public:
	BannerAptCallbackHolder( FunctorBindingSingle binding )
	{
		m_ptr = new Rva0058D030FunctorSingleWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	BannerAptCallbackHolder( const BannerAptCallbackHolder &other )
		: m_ptr( other.m_ptr ) {}

	~BannerAptCallbackHolder() {}

	FunctorSingleWrapperHead *m_ptr;
};

class WindowManager
{
public:
	void registerAptCallback( const BFMERetailAsciiString &name,
		BannerAptCallbackHolder callback );
	void bfmeBindRva004650F0( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
};

extern WindowManager *g_theWindowManager;

class AptPalantirHeroSelector : public FunctorTargetSingle
{
public:
	AptPalantirHeroSelector();

private:
	struct HeroListEntry
	{
		unsigned char bytes[ 12 ];
	};

	bool m_active;
	_STL::list<HeroListEntry> m_heroes;
	Gen_p24pod m_slots[ 17 ];
	bool m_selectAll;
	int m_window;
};

static FunctorMethodSingle rawFunctorMethod( unsigned int value )
{
	union
	{
		unsigned int raw;
		FunctorMethodSingle member;
	} method;
	method.raw = value;
	return method.member;
}

// ??0AptPalantirHeroSelector@@QAE@XZ
AptPalantirHeroSelector::AptPalantirHeroSelector()
	: m_active( false )
	, m_heroes()
{
	union
	{
		void (*raw)( void );
		FunctorMethodSingle member;
	} callback;
	callback.raw = (void (*)( void ))0x00440BBF;
	AptPalantirHeroSelector *self = this;
	Gen_p24pod *end = self->m_slots + 17;
	self->m_selectAll = false;
	self->m_window = 0;
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnSelectAllHeroes" );
		g_theWindowManager->registerAptCallback( name,
			BannerAptCallbackHolder(
				FunctorBindingSingle( callback.member, self ) ) );
	}

	Gen_p24pod empty;
	empty.a[ 0 ] = *(int *)&self->m_heroes;
	empty.a[ 1 ] = 0;
	empty.a[ 2 ] = -1;
	empty.a[ 3 ] = -1;
	empty.a[ 4 ] = -1;
	empty.first = 0;
	empty.second = 0;
	std::fill( self->m_slots, end, empty );

	for( int index = 0; index < 17; ++index )
	{
		BFMERetailAsciiString name;
		name.format( "Palantir/HeroSelectUI/Hero%d/", index + 1 );
		g_theWindowManager->bfmeBindRva004650F0( *(const AsciiString *)&name,
			Rva0050F8B0FunctorHolder(
				FunctorBindingSingle( rawFunctorMethod( index ), self ) ) );
	}

	{
		BFMERetailAsciiString name( "Palantir/HeroSelectUI/SelectAllHeroesBttn/" );
		g_theWindowManager->bfmeBindRva004650F0( *(const AsciiString *)&name,
			Rva0050F8B0FunctorHolder(
				FunctorBindingSingle( rawFunctorMethod( 0x0041CFDF ), self ) ) );
	}
}
