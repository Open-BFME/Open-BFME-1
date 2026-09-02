// ?rva004C84C0Teardown@@YAXXZ
// partial score=0.98 date=2026-09-02
// cl: /DNDEBUG /MD
// Open-BFME5: cdecl teardown at 0x004C84C0. Null-guarded slot 0x20 on g_A,
// reload and guarded slot 4 with arg 1, g_A = 0, then a five-argument cdecl
// call chosen by g_B->m_43c.

class Rva004C84C0Obj
{
public:
	virtual void slot00();
	virtual void slot04(int a);
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
};

class Rva004C84C0B
{
public:
	char m_pad[0x43c];
	char m_flag43c;
};

extern Rva004C84C0Obj *g_rva004C84C0A;
extern Rva004C84C0B *g_rva004C84C0B;

extern void *g_rva004C84C0_12b6a34;
extern void *g_rva004C84C0_12b6a38;
extern char g_rva004C84C0_12b6a3c;
extern char g_rva004C84C0_12b6a68;
extern void *g_rva004C84C0_12b6a84;
extern void *g_rva004C84C0_12b6a88;
extern char g_rva004C84C0_12b6a8c;
extern char g_rva004C84C0_12f3a38;

void fiveArg004C84C0(int a, void *b, void *c, void *d, void *e);

void rva004C84C0Teardown(void)
{
	Rva004C84C0Obj *p = g_rva004C84C0A;
	if (!p)
		return;
	p->slot20();
	p = g_rva004C84C0A;
	if (p)
		p->slot04(1);
	Rva004C84C0B *b = g_rva004C84C0B;
	char flag = b->m_flag43c;
	g_rva004C84C0A = 0;
	if (!flag)
		fiveArg004C84C0(1, g_rva004C84C0_12b6a34, g_rva004C84C0_12b6a38, &g_rva004C84C0_12b6a3c, &g_rva004C84C0_12b6a68);
	else
		fiveArg004C84C0(1, g_rva004C84C0_12b6a84, g_rva004C84C0_12b6a88, &g_rva004C84C0_12b6a8c, &g_rva004C84C0_12f3a38);
}
