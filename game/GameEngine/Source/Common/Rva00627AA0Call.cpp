// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00627AA0Arg
{
	int m_value;
	char m_pad[0x2B4];
};

struct Rva00627AA0Obj
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6(Rva00627AA0Arg *arg);
};

Rva00627AA0Obj *g_rva00627AA0;

void rva00627AA0Call()
{
	Rva00627AA0Arg arg;
	arg.m_value = 1;
	g_rva00627AA0->slot6(&arg);
}
