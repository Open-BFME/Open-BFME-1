// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob0 /Ireference/shims/sweep
#include <windows.h>

// Not declared by the sweep shim's windows.h.
extern "C" __declspec(dllimport) UINT __stdcall SetDIBColorTable(HDC, UINT, UINT, const RGBQUAD *);


// A four-entry cache of memory DCs. Acquire takes the first slot that still
// holds one, atomically clearing it; an empty cache creates a fresh DC.
class DcPool
{
public:
	HDC acquire(void);
	void release(HDC dc);
private:
	LONG m_slots[4];
};

HDC DcPool::acquire(void)
{
	int i = 0;
	LONG *slot = m_slots;
	for (; i < 4; ++i, ++slot)
	{
		HDC dc = (HDC)InterlockedExchange(slot, 0);
		if (dc)
			return dc;
	}
	return CreateCompatibleDC(NULL);
}

// ??4 release: retail makes a CALL to DeleteDC here where MSVC 7.1 tail-jumps
// it; every other byte matches. Marked rather than claimed.
// ?release@DcPool@@QAEXPAX@Z present-unmatched
// Park the DC in the first empty slot. A slot that was already occupied hands
// its own DC back, so the loop carries that one onward; whatever is still held
// after four slots is destroyed.
void DcPool::release(HDC dc)
{
	int i = 0;
	LONG *slot = m_slots;
	for (; i < 4; ++i, ++slot)
	{
		dc = (HDC)InterlockedExchange(slot, (LONG)dc);
		if (!dc)
			return;
	}
	DeleteDC(dc);
}

extern DcPool TheDcPool;					// 0x0134FB38

// Holds a pooled memory DC for as long as any nested call needs it: the first
// entry borrows one and selects the bitmap into it, the last exit puts the old
// object back and returns the DC to the pool.
class DibPalette
{
public:
	void setColorTable(UINT start, UINT entries, const RGBQUAD *colors);
private:
	LONG m_unreconstructed_00;			// +0x00
	HBITMAP m_bitmap;					// +0x04
	LONG m_unreconstructed_08[7];		// +0x08
	HDC m_dc;							// +0x24
	LONG m_depth;						// +0x28
	HGDIOBJ m_oldObject;				// +0x2C
};

void DibPalette::setColorTable(UINT start, UINT entries, const RGBQUAD *colors)
{
	++m_depth;
	if (!m_dc)
	{
		m_dc = TheDcPool.acquire();
		m_oldObject = SelectObject(m_dc, m_bitmap);
	}
	SetDIBColorTable(m_dc, start, entries, colors);
	if (--m_depth == 0)
	{
		SelectObject(m_dc, m_oldObject);
		TheDcPool.release(m_dc);
		m_dc = 0;
	}
}
