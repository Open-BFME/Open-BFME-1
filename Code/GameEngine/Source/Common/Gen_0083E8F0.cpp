// Clean reconstruction of the two-argument global dispatch at retail RVA
// 0x0083E8F0.  The imported routine and global owner are address-derived;
// the fixed callback value is the immediate used by the retail body.

typedef void (__cdecl *Gen_0083E8F0_Call)(void *, void *);
extern Gen_0083E8F0_Call g_call;
extern void *g_global;

void process()
{
	g_call((void *)0x0112EBAC, (char *)g_global + 0x40);
}
