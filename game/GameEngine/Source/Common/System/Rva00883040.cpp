// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(void *, unsigned long, unsigned long);

// Retail .data 0x012D4D10 holds 20: the slot count d_00883040 bounds index
// against and Rva00882FB0 grows. Address-derived name.
unsigned g_Va012D4D10Count = 20;
// Retail .bss 0x0130E9F0: the lazily HeapAlloc'd slot buffer. Address-derived name.
unsigned *g_Va0130E9F0Buf;

void d_00883040(unsigned index, unsigned value)
{
	if (!index)
		return;
	unsigned capBytes = g_Va012D4D10Count << 2;
	if (index > capBytes)
		return;

	unsigned *buf = g_Va0130E9F0Buf;
	unsigned slot = (index - 1) >> 2;
	if (!buf)
	{
		buf = (unsigned *)HeapAlloc(GetProcessHeap(), 8, capBytes);
		g_Va0130E9F0Buf = buf;
	}

	unsigned stride = (slot << 2) + 4;
	if (value / stride <= 0x4000000)
		buf[slot] = value;
}
