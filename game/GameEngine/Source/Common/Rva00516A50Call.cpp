// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeGlobal_012f19e8
{
public:
	void bfmeCall_000290d2(void);
};

extern void *g_Va012F4998;
extern BfmeGlobal_012f19e8 *TheBfmeGlobal_012f19e8;

class Rva00516A50
{
public:
	void wrap(int a);
};

void Rva00516A50::wrap(int)
{
	if (g_Va012F4998)
		TheBfmeGlobal_012f19e8->bfmeCall_000290d2();
}
