// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the GDI+ lifetime bookkeeping at 0x0005C020 / 0x0005C110 /
// 0x0005E160.
//
// 0x0005C020 names itself through its callee: it decrements a counter at
// this+0x1C under a critical section that lives at this+4, and when the count
// reaches zero it passes the word at this+0 to the gdiplus.dll GdiplusShutdown
// import stub and clears it. That is a reference-counted holder of the ULONG_PTR
// token GdiplusStartup hands back, and the object is therefore
// { token at +0, CRITICAL_SECTION at +4, count at +0x1C }.
//
// 0x0005C110 and 0x0005E160 are a DIFFERENT object -- 0x0005C110 lays down a
// vftable at 0x01073740 and initialises out to +0x2C, and 0x0005E160 tears the
// same field block down and hands the handle at +4 to GDI32 DeleteObject, so
// +4 there is an HBITMAP and not a lock. What ties them together is not
// GdiplusShutdown but the shared field list, and the ORDER proves they are two
// different source statements over it: the constructor writes +0x14 before
// +0x18 and +0x1C before +0x1D, the reset writes +0x18 before +0x14 and +0x1D
// before +0x1C, and MSVC 7.1 does not reorder straight-line constant stores.
//
// The global critical section at 0x0134FB1C and the count beside it at
// 0x0134FB34 are DIR32 operands the patcher copies; naming them costs nothing
// and proves nothing.
//
// Identity is address-derived apart from the GdiplusShutdown call.

typedef int Int;
typedef unsigned long DWORD;
typedef void *HGDIOBJ;

struct CriticalSection
{
	unsigned char m_opaque[24];
};

extern "C"
{
	__declspec(dllimport) void __stdcall EnterCriticalSection(CriticalSection *section);
	__declspec(dllimport) void __stdcall LeaveCriticalSection(CriticalSection *section);
	__declspec(dllimport) int __stdcall DeleteObject(HGDIOBJ object);

	void __stdcall GdiplusShutdown(DWORD token);
}

// ---------------------------------------------------------------------------

class Rva0005C020Token
{
public:
	void release(void);

private:
	DWORD m_token;										///< retail this+0x00
	CriticalSection m_lock;								///< retail this+0x04
	Int m_refCount;										///< retail this+0x1C
};

// ?release@Rva0005C020Token@@QAEXXZ
void Rva0005C020Token::release(void)
{
	EnterCriticalSection(&m_lock);

	m_refCount = m_refCount - 1;

	if (m_refCount == 0)
	{
		EnterCriticalSection(&m_lock);

		if (m_token != 0)
		{
			GdiplusShutdown(m_token);
		}

		m_token = 0;
		LeaveCriticalSection(&m_lock);
	}

	LeaveCriticalSection(&m_lock);
}

// ---------------------------------------------------------------------------

extern CriticalSection g_lock0134FB1C;					///< retail [0x0134FB1C]
extern Int g_count0134FB34;								///< retail [0x0134FB34]

class Rva0005C110Surface
{
public:
	Rva0005C110Surface(void);

	void reset(void);

	virtual void slot00(void);

private:
	HGDIOBJ m_bitmap;									///< retail this+0x04
	Int m_value08;										///< retail this+0x08
	Int m_value0C;										///< retail this+0x0C
	Int m_value10;										///< retail this+0x10
	Int m_value14;										///< retail this+0x14
	Int m_value18;										///< retail this+0x18
	bool m_flag1C;										///< retail this+0x1C
	bool m_flag1D;										///< retail this+0x1D
	Int m_value20;										///< retail this+0x20
	Int m_value24;										///< retail this+0x24
	Int m_value28;										///< retail this+0x28
	Int m_value2C;										///< retail this+0x2C
};

// ??0Rva0005C110Surface@@QAE@XZ
Rva0005C110Surface::Rva0005C110Surface(void)
{
	m_bitmap = 0;
	m_value08 = 0;
	m_value0C = 0;
	m_value10 = 0;
	m_value14 = 0;
	m_value18 = 0;
	m_flag1C = false;
	m_flag1D = false;
	m_value20 = -1;
	m_value24 = 0;
	m_value28 = 0;
	m_value2C = 0;

	EnterCriticalSection(&g_lock0134FB1C);
	g_count0134FB34 = g_count0134FB34 + 1;
	LeaveCriticalSection(&g_lock0134FB1C);
}

// ?reset@Rva0005C110Surface@@QAEXXZ
void Rva0005C110Surface::reset(void)
{
	HGDIOBJ bitmap = m_bitmap;

	if (bitmap != 0)
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

		DeleteObject(bitmap);
	}
}
