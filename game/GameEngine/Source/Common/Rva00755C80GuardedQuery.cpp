// 0x00755C80 -- store a method result from a global pointer, or skip.
//
//     mov ecx,[GLOBAL_PTR] / test ecx,ecx / je end / call <ILT> /
//     mov [GLOBAL_RESULT],eax / end: ret
//
// Retail loads the pointer into ecx (8b 0d, 6 bytes) rather than the eax
// short form, which is what a thiscall on that pointer looks like. A free
// function under the same guard compiles to a1 and comes out one byte short.

class Gen01304B64
{
public:
	int bfmeQuery(void);
};

extern Gen01304B64 *g_Va01304B64;
extern int g_Va01304B5C;

// @?Rva00755C80@@YAXXZ 0x00755C80
void Rva00755C80(void)
{
	if (g_Va01304B64)
		g_Va01304B5C = g_Va01304B64->bfmeQuery();
}
