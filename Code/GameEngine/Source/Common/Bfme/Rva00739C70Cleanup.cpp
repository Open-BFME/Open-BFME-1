// 23-byte and 32-byte cleanup routines, 62-byte reset, 109-byte update, and 81-byte destructor
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
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

class Member0C00739C70
{
public:
	VirtualReleaser00739E00 *m_obj;

	~Member0C00739C70();
	void clear();
	void reset()
	{
		if ( m_obj )
		{
			m_obj->Release();
			m_obj = 0;
		}
	}
	TextureBaseClass *methodA( int arg, int a, int b, int c, int d );
	TextureBaseClass *methodB( int arg, int a );
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

	int               m_int0;
	int               m_int4;
	TexturePtr        m_ptr08;
	Member0C00739C70  m_member0c;
	int               m_flags;
};

void Rva00739C70::cleanup()
{
	if ( m_flags & 1 )
	{
		m_member0c.clear();
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
		m_member0c.clear();
		m_flags &= ~1;
	}
	if ( m_member0c.m_obj )
	{
		if ( !( m_flags & 0xC ) )
		{
			result = m_member0c.methodA( arg, 0, 0, m_int0, m_int4 );
		}
		else
		{
			result = m_member0c.methodB( arg, 1 );
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
