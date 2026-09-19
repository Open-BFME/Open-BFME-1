// cl: /DNDEBUG /MD /EHs-c-

extern "C" __declspec(dllimport) void *__stdcall GetProcessHeap(void);
extern "C" __declspec(dllimport) void *__stdcall HeapAlloc(
	void *, unsigned long, unsigned long);
extern "C" __declspec(dllimport) int __stdcall HeapFree(
	void *, unsigned long, void *);
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);

extern unsigned g_rva00883040Count;
extern unsigned *g_rva00883040Buf;

void Rva00882FB0ResizeDwordTable(unsigned byteCount)
{
	unsigned newCount = byteCount >> 2;
	if (g_rva00883040Buf)
	{
		unsigned *newBuf = (unsigned *)HeapAlloc(
			GetProcessHeap(), 8, newCount * sizeof(unsigned) + 1);
		unsigned copyCount = newCount < g_rva00883040Count
			? newCount : g_rva00883040Count;
		unsigned *oldBuf = g_rva00883040Buf;
		memcpy(newBuf, oldBuf, copyCount * sizeof(unsigned));
		HeapFree(GetProcessHeap(), 0, oldBuf);
		g_rva00883040Buf = newBuf;
		g_rva00883040Count = newCount;
		return;
	}

	unsigned *newBuf = (unsigned *)HeapAlloc(
		GetProcessHeap(), 8, newCount * sizeof(unsigned) + 1);
	g_rva00883040Count = newCount;
	g_rva00883040Buf = newBuf;
}
