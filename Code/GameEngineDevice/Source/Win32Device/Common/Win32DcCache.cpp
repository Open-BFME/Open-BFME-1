// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob0 /Ireference/shims/sweep
#include <windows.h>

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
