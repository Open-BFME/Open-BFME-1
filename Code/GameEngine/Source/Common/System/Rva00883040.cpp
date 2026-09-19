// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *, unsigned long, unsigned long);

extern unsigned g_rva00883040Count;
extern unsigned *g_rva00883040Buf;

void d_00883040(unsigned index, unsigned value)
{
	if (!index)
		return;
	unsigned capBytes = g_rva00883040Count << 2;
	if (index > capBytes)
		return;

	unsigned *buf = g_rva00883040Buf;
	unsigned slot = (index - 1) >> 2;
	if (!buf)
	{
		buf = (unsigned *)HeapAlloc(GetProcessHeap(), 8, capBytes);
		g_rva00883040Buf = buf;
	}

	unsigned stride = (slot << 2) + 4;
	if (value / stride <= 0x4000000)
		buf[slot] = value;
}
