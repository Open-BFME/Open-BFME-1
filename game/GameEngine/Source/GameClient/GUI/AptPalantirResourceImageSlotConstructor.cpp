// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Constructor of the Palantir resource-bar slot that retail 0x00597FC0 builds at +0x460
// (ILT 0x00048E96); the same subobject receives cacheResourceImage (0x00592570).

template <typename T> class BannerStringBase
{
	friend class BFMERetailAsciiString;

private:
	BannerStringBase( const T *text );
};

class AsciiString;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text )
	{
		((BannerStringBase<char> *)this)->BannerStringBase<char>::BannerStringBase( text );
	}
	~BFMERetailAsciiString() { releaseBuffer(); }

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

struct FunctorSlot
{
	FunctorSlot( void *slot ) : m_slot( slot ) {}

	void *m_slot;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}
	virtual void functorWrapperAnchor();

	unsigned int m_refCount;
};

// Retail table 0x0110BCD0: {target, method} binding, 16-byte allocation.
class Rva0058D0E0FunctorSingleWrapper : public FunctorWrapperHead
{
public:
	Rva0058D0E0FunctorSingleWrapper( const FunctorBindingSingle &binding )
		: m_binding( binding ) {}

	FunctorBindingSingle m_binding;
};

// Retail tables 0x0110BCDC, 0x0110BCE8 and 0x0110BCF4: one-pointer slot, 12-byte allocation.
#define RESOURCE_SLOT_WRAPPER( NAME )                                         \
	class NAME : public FunctorWrapperHead                                    \
	{                                                                         \
	public:                                                                   \
		NAME( const FunctorSlot &slot ) : m_slot( slot ) {}                   \
                                                                              \
		FunctorSlot m_slot;                                                   \
	};

RESOURCE_SLOT_WRAPPER( Rva0058D120FunctorSlotWrapper )
RESOURCE_SLOT_WRAPPER( Rva0058D160FunctorSlotWrapper )
RESOURCE_SLOT_WRAPPER( Rva0058D1A0FunctorSlotWrapper )

class PalantirCallbackHolder
{
public:
	PalantirCallbackHolder( FunctorBindingSingle binding )
	{
		m_ptr = new Rva0058D0E0FunctorSingleWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	PalantirCallbackHolder( const PalantirCallbackHolder &other )
		: m_ptr( other.m_ptr ) {}

	~PalantirCallbackHolder() {}

	Rva0058D0E0FunctorSingleWrapper *m_ptr;
};

class Rva0050F8B0FunctorHolder
{
public:
	// The pointer argument only selects the wrapper type the caller allocates.
	template <class Wrapper>
	Rva0050F8B0FunctorHolder( FunctorSlot binding, Wrapper * )
	{
		m_ptr = new Wrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr )
	{
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	FunctorWrapperHead *m_ptr;
};

class WindowManager
{
public:
	void registerPalantirCallback( const BFMERetailAsciiString &name,
		PalantirCallbackHolder callback );
	void bfmeBindRva004650F0( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
};

// Landed at 0x0046C790 (BfmeConv1024.cpp); retail passes the two string addresses as ints.
class BfmeA1024
{
public:
	void bfmeGo1024A( int image, int key );
};

extern WindowManager *g_theWindowManager;

// ILT to 0x00588E60, the draw callback that reads m_resourceImage at +0x1C.
extern void j_000062b2();

// Owners at +0x20 and +0x24; the unwind map destroys them through ILTs 0x00026A53 and 0x000144A2.
class Gen_uwm_00026a53
{
public:
	Gen_uwm_00026a53() : m_ptr( 0 ) {}
	~Gen_uwm_00026a53();

	void *m_ptr;
};

class Gen_uwm_000144a2
{
public:
	Gen_uwm_000144a2() : m_ptr( 0 ) {}
	~Gen_uwm_000144a2();

	void *m_ptr;
};

class Image;

class Rva00592570ResourceImageSlot
{
public:
	Rva00592570ResourceImageSlot();

private:
	int m_unknown00;
	int m_unknown04;
	bool m_flag08;
	int m_resources;
	int m_commandPoints;
	int m_unknown14;
	int m_resourceMultiplier;
	const Image *m_resourceImage;
	Gen_uwm_00026a53 m_owned20;
	Gen_uwm_000144a2 m_owned24;
};

// ??0Rva00592570ResourceImageSlot@@QAE@XZ
Rva00592570ResourceImageSlot::Rva00592570ResourceImageSlot()
	: m_unknown00( 0 )
	, m_unknown04( 0 )
	, m_flag08( false )
	, m_resources( -2 )
	, m_commandPoints( -1 )
	, m_unknown14( -1 )
	, m_resourceMultiplier( 0 )
	, m_resourceImage( 0 )
{
	{
		BFMERetailAsciiString key( "Resource_Icon" );
		BFMERetailAsciiString image( "ResourceBar/ResourceIcon" );
		( (BfmeA1024 *)g_theWindowManager )->bfmeGo1024A( (int)&image, (int)&key );
	}

	{
		union
		{
			void (*raw)( void );
			FunctorMethodSingle member;
		} callback;
		callback.raw = j_000062b2;
		BFMERetailAsciiString name( "RenderFactionIcon" );
		g_theWindowManager->registerPalantirCallback( name,
			PalantirCallbackHolder(
				FunctorBindingSingle( callback.member, (FunctorTargetSingle *)this ) ) );
	}

	{
		BFMERetailAsciiString name( "Palantir/ResourceBar/Resources/" );
		g_theWindowManager->bfmeBindRva004650F0( *(const AsciiString *)&name,
			Rva0050F8B0FunctorHolder( FunctorSlot( &m_resources ),
				(Rva0058D120FunctorSlotWrapper *)0 ) );
	}

	{
		BFMERetailAsciiString name( "Palantir/ResourceBar/ResourceMultiplier/" );
		g_theWindowManager->bfmeBindRva004650F0( *(const AsciiString *)&name,
			Rva0050F8B0FunctorHolder( FunctorSlot( &m_resourceMultiplier ),
				(Rva0058D160FunctorSlotWrapper *)0 ) );
	}

	{
		BFMERetailAsciiString name( "Palantir/ResourceBar/CommandPoints/" );
		g_theWindowManager->bfmeBindRva004650F0( *(const AsciiString *)&name,
			Rva0050F8B0FunctorHolder( FunctorSlot( &m_commandPoints ),
				(Rva0058D1A0FunctorSlotWrapper *)0 ) );
	}
}
