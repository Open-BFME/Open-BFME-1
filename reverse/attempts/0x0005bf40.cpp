// ?bfmeForward@Gen_0005C450Target@@QAE_NXZ
// partial score=0.92 date=2026-09-08
// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x0005BF40 is the body reached by the 0x00018205 incremental-link
// thunk for Gen_0005C450Target::bfmeForward. The 0x0005C450 forwarder supplies
// the singleton at 0x0134FB18, which stores the GDI+ token followed by its
// critical section.

typedef unsigned long ULONG_PTR;

struct CriticalSection
{
	unsigned char m_opaque[ 24 ];
};

struct GdiplusStartupInput
{
	unsigned long version;
	void *debugEventCallback;
	int suppressBackgroundThread;
	int suppressExternalCodecs;
};

struct GdiplusStartupOutput
{
	void *notificationHook;
	void *notificationUnhook;
};

extern "C"
{
	__declspec( dllimport ) void __stdcall EnterCriticalSection( CriticalSection *section );
	__declspec( dllimport ) void __stdcall LeaveCriticalSection( CriticalSection *section );
	int __stdcall GdiplusStartup( ULONG_PTR *token, const GdiplusStartupInput *input,
		GdiplusStartupOutput *output );
}

class Gen_0005C450Target
{
public:
	bool bfmeForward( void );

private:
	ULONG_PTR m_token;
	CriticalSection m_lock;
};

// ?bfmeForward@Gen_0005C450Target@@QAE_NXZ
bool Gen_0005C450Target::bfmeForward( void )
{
	EnterCriticalSection( &m_lock );

	int success = 1;
	if( m_token == 0 )
	{
		GdiplusStartupOutput output;
		volatile GdiplusStartupInput input = { 0 };
		input.version = success;
		if( GdiplusStartup( &m_token,
			(const GdiplusStartupInput *)&input, &output ) != 0 )
			success = 0;
	}

	LeaveCriticalSection( &m_lock );
	return success != 0;
}
