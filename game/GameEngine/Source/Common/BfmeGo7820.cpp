// cl: /DNDEBUG /MD /O2

extern int g_bfmeTableC7E0;
extern int g_bfmeTableC800;

void __cdecl bfmeGo76A0(int delta, int *table, void *p2, int a, int b, int c, void *p3);
void __cdecl bfmeGo7760(int *table, void *p1, int a, int b, int c, int d, void *p5);

// ?bfmeGo7820@@YAXPAX0000@Z
void __cdecl bfmeGo7820(void *p0, void *p1, void *p2, void *p3, void *p4)
{
	bfmeGo76A0((char *)p0 - (char *)p2, &g_bfmeTableC7E0, p2, 1, 0xB, 8, p3);
	bfmeGo7760(&g_bfmeTableC800, p1, 8, 8, 8, 8, p4);
}
