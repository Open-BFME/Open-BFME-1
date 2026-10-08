// 23-byte and 32-byte cleanup routines, 62-byte reset, 109-byte update, and 81-byte destructor
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

struct TexturePtr
{
	TextureBaseClass *m_ptr;
	~TexturePtr()
	{
		if ( m_ptr )
			m_ptr->Release_Ref();
	}
	TextureBaseClass *operator->() { return m_ptr; }
	operator bool() { return m_ptr != 0; }
	TexturePtr& operator=( int val ) { m_ptr = (TextureBaseClass*)val; return *this; }
};

class VirtualReleaser00739E00
{
public:
	virtual void v0();
	virtual void v1();
	virtual unsigned long __stdcall Release();
};

// The three calls made on the member at +0x0C reach the matched SurfaceClass
// rows: Unlock 0x008FC7D0, rectangle Lock 0x008FC710 and discard Lock
// 0x008FC660; this is a second view of the bytes W3DRadarResetSurface owns.
class SurfaceClass
{
public:
	VirtualReleaser00739E00 *m_obj;

	void Unlock();
	void *Lock( int *pitch, int left, int top, int right, int bottom );
	void *Lock( int *pitch, bool discard );
};

// Retail's destructor for this sub-object lives at 0x008FC5B0 and is defined as
// W3DRadarResetSurface::~W3DRadarResetSurface, so the member that owns it is
// spelled with that class name.
class W3DRadarResetSurface
{
public:
	VirtualReleaser00739E00 *m_obj;

	~W3DRadarResetSurface();
	void reset()
	{
		if ( m_obj )
		{
			m_obj->Release();
			m_obj = 0;
		}
	}
};

class Rva00739C70
{
public:
	~Rva00739C70();
	void cleanup();
	void reset();
	TextureBaseClass *update( int arg );
	// Retail identity is not recovered; the synthetic name records its exact
	// address while keeping this small predicate attached to the proven object.
	bool rva_00739E50();

	int                  m_int0;
	int                  m_int4;
	TexturePtr           m_ptr08;
	// Both views alias the same four bytes at +0x0C; retail has one class there
	// and only the split spelling is ours.
	W3DRadarResetSurface m_member0c;
	int                  m_flags;

	SurfaceClass &calls()
	{
		return *reinterpret_cast<SurfaceClass *>( &m_member0c );
	}
};

void Rva00739C70::cleanup()
{
	if ( m_flags & 1 )
	{
		calls().Unlock();
		m_flags &= ~1;
	}
}

void Rva00739C70::reset()
{
	cleanup();
	if ( m_ptr08 )
	{
		m_ptr08->Release_Ref();
		m_ptr08 = 0;
	}
	m_member0c.reset();
}

TextureBaseClass *Rva00739C70::update( int arg )
{
	TextureBaseClass *result = 0;
	if ( m_flags & 1 )
	{
		calls().Unlock();
		m_flags &= ~1;
	}
	if ( m_member0c.m_obj )
	{
		if ( !( m_flags & 0xC ) )
		{
			result = (TextureBaseClass *)calls().Lock( (int *)arg, 0, 0, m_int0, m_int4 );
		}
		else
		{
			result = (TextureBaseClass *)calls().Lock( (int *)arg, true );
		}
		m_flags |= 1;
	}
	return result;
}

Rva00739C70::~Rva00739C70()
{
}

bool Rva00739C70::rva_00739E50()
{
	return m_ptr08.m_ptr != 0 || m_member0c.m_obj != 0;
}

class Owner00739C90
{
public:
	void cleanup();

	char         m_pad0[ 0x28 ];
	bool         m_dirty28;
	char         m_pad29[ 0x1B ];
	Rva00739C70 *m_subObject;
};

void Owner00739C90::cleanup()
{
	m_subObject->cleanup();
	m_dirty28 = true;
}
