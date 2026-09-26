// cl: /DNDEBUG /MD
// Open-BFME5: teardown callback at retail 0x004C84C0.
//
// The flag test and the global clear are deliberately present in both source
// arms.  MSVC 7.1 folds the two stores into the retail placement between the
// test and the branch, while retaining the byte load in CL.

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

// pinned at ILT 0x00047D52 -> ShowUnderlyingGUIElements
void __cdecl ShowUnderlyingGUIElements(
	bool show,
	char const *layout,
	char const *window,
	char const **hideList,
	char const **showList);

void rva004C84C0Teardown(void)
{
	Rva004C84C0Obj *p = g_rva004C84C0A;
	if (!p)
		return;
	p->slot20();
	p = g_rva004C84C0A;
	if (p)
		p->slot04(1);
	if (!g_rva004C84C0B->m_flag43c)
	{
		g_rva004C84C0A = 0;
		ShowUnderlyingGUIElements(
			true,
			(char const *)g_rva004C84C0_12b6a34,
			(char const *)g_rva004C84C0_12b6a38,
			(char const **)&g_rva004C84C0_12b6a3c,
			(char const **)&g_rva004C84C0_12b6a68);
	}
	else
	{
		g_rva004C84C0A = 0;
		ShowUnderlyingGUIElements(
			true,
			(char const *)g_rva004C84C0_12b6a84,
			(char const *)g_rva004C84C0_12b6a88,
			(char const **)&g_rva004C84C0_12b6a8c,
			(char const **)&g_rva004C84C0_12f3a38);
	}
}
