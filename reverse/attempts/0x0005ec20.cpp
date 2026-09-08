// Partial ordinary-C++ reconstruction of the cleanup body at retail RVA
// partial score=0.91 date=2026-09-07
// 0x0005EC20.  The owner/layout is shared with Rva0005C110Surface in
// Code/gen_small/U3GdiplusTokenHolder.cpp.  Best probe: 134 bytes, with the
// release/count/token tail exact; the remaining differences are prologue/vptr
// scheduling and the order of the +0x18/+0x14 stores.

typedef void *HGDIOBJ;
typedef unsigned long DWORD;
typedef void (__stdcall *GdiReleaseOne)(void *);

struct CriticalSection
{
	unsigned char m_opaque[24];
};

extern GdiReleaseOne g_release;
extern CriticalSection g_lock0134FB1C;
extern int g_count0134FB34;
extern DWORD g_gdiplusToken0134FB18;
extern "C" void __stdcall EnterCriticalSection(CriticalSection *);
extern "C" void __stdcall LeaveCriticalSection(CriticalSection *);
extern "C" void __stdcall GdiplusShutdown(DWORD);

class Rva0005EC20Surface
{
public:
	void cleanup(void);

private:
	void *m_vptr;
	HGDIOBJ m_bitmap;
	int m_value08;
	int m_value0C;
	int m_value10;
	int m_value14;
	int m_value18;
	bool m_flag1C;
	bool m_flag1D;
	int m_value20;
};

void Rva0005EC20Surface::cleanup(void)
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
		g_release(bitmap);
		EnterCriticalSection(&g_lock0134FB1C);
		--g_count0134FB34;
		if (g_count0134FB34 == 0)
		{
			EnterCriticalSection(&g_lock0134FB1C);
			if (g_gdiplusToken0134FB18 != 0)
				GdiplusShutdown(g_gdiplusToken0134FB18);
			g_gdiplusToken0134FB18 = 0;
			LeaveCriticalSection(&g_lock0134FB1C);
		}
		LeaveCriticalSection(&g_lock0134FB1C);
	}
}
