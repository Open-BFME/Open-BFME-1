// cl: /DNDEBUG /MD /EHs-c-
// The complete virtual destructor for the object whose constructor at
// 0x0005C110 installs vtable 0x01073740.  The vtable's scalar deleting thunk
// (0x0005FA60 -> 0x0005EC20) independently anchors this class identity.

typedef int Int;
typedef unsigned long DWORD;
typedef void *HGDIOBJ;

struct CriticalSection
{
	unsigned char m_opaque[ 24 ];
};

extern "C"
{
	__declspec( dllimport ) void __stdcall EnterCriticalSection( CriticalSection *section );
	__declspec( dllimport ) void __stdcall LeaveCriticalSection( CriticalSection *section );
	__declspec( dllimport ) int __stdcall DeleteObject( HGDIOBJ object );
	void __stdcall GdiplusShutdown( DWORD token );
}

extern CriticalSection g_lock0134FB1C;
extern Int g_count0134FB34;
extern DWORD g_token0134FB18;

class Rva0005C110Surface
{
public:
	virtual ~Rva0005C110Surface();

private:
	HGDIOBJ m_bitmap;
	Int m_value08;
	Int m_value0C;
	Int m_value10;
	Int m_value14;
	Int m_value18;
	bool m_flag1C;
	bool m_flag1D;
	Int m_value20;
	Int m_value24;
	Int m_value28;
	Int m_value2C;
};

Rva0005C110Surface::~Rva0005C110Surface()
{
	HGDIOBJ bitmap = m_bitmap;
	if( bitmap != 0 )
	{
		m_bitmap = 0;
		m_value08 = 0;
		m_value0C = 0;
		m_value10 = 0;
		m_value18 = 0;
		m_value14 = 0;
		m_value20 = -1;
		m_flag1D = false;
		m_flag1C = false;
		DeleteObject( bitmap );
	}

	EnterCriticalSection( &g_lock0134FB1C );
	--g_count0134FB34;

	if( g_count0134FB34 == 0 )
	{
		EnterCriticalSection( &g_lock0134FB1C );
		if( g_token0134FB18 != 0 )
			GdiplusShutdown( g_token0134FB18 );
		g_token0134FB18 = 0;
		LeaveCriticalSection( &g_lock0134FB1C );
	}

	LeaveCriticalSection( &g_lock0134FB1C );
}
