// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: GDI+ startup forwarder at retail 0x0005BF40.
//
// The 0x00018205 incremental-link thunk reaches this body, while the
// singleton forwarder at 0x0005C450 supplies the token/critical-section
// object at 0x0134FB18.  The address-derived owner is intentional: the
// available evidence proves the layout and call path, not an original class
// name.

typedef unsigned long ULONG_PTR;

struct CriticalSection
{
	unsigned char m_opaque[24];
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
	__declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection *section);
	__declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection *section);
}

extern void ji_009f6c0a();
typedef int (__stdcall *GdiplusStartupType)(ULONG_PTR *,
	const GdiplusStartupInput *, GdiplusStartupOutput *);

class Rva0005BF40Target
{
public:
	bool bfmeForward(void);

private:
	ULONG_PTR m_token;
	CriticalSection m_lock;
};

// ?bfmeForward@Rva0005BF40Target@@QAE_NXZ
bool Rva0005BF40Target::bfmeForward(void)
{
	EnterCriticalSection(&m_lock);

	bool success = true;
	if (m_token == 0)
	{
		GdiplusStartupOutput output;
		GdiplusStartupInput input;
		input.debugEventCallback = 0;
		input.suppressBackgroundThread = 0;
		input.suppressExternalCodecs = 0;
		input.version = success;
		if (((GdiplusStartupType)ji_009f6c0a)(&m_token,
			(const GdiplusStartupInput *)&input, &output) != 0)
			success = false;
	}

	LeaveCriticalSection(&m_lock);
	return success;
}
