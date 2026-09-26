// ?d_00897360@@YAXXZ
// partial score=0.98 date=2026-09-06
// Shutdown the BFME registry and its intrusive item list.

class Rva8CD130IdleHook
{
public:
	int m_unused;
	int m_enabled;
	void run(void);
};

extern Rva8CD130IdleHook *g_rva8CD130IdleHook;

class Rva00897260Node
{
};

extern void __cdecl bfmeCleanup97260(Rva00897260Node *node);

class Rva008972B0Source
{
public:
	void *m_data;
	int (__cdecl *getCount)(void *data);
	void *(__cdecl *getItem)(void *data, int index);
};

extern void __cdecl bfmeWalk972B0(Rva008972B0Source *source);

class Rva00897360Item
{
public:
	virtual void op0(void) = 0;
	virtual void op1(void) = 0;
	virtual void op2(void) = 0;
	virtual void op3(void) = 0;
	virtual void op4(void) = 0;
	virtual void op5(void) = 0;
	virtual void op6(void) = 0;
	virtual void op7(void) = 0;
	virtual void op8(void) = 0;
	virtual void op9(void) = 0;
	virtual void op10(void) = 0;
	virtual void op11(void) = 0;
	virtual void op12(void) = 0;

	unsigned int m_flags;
};

class Rva00897360Links
{
public:
	Rva00897360Item *m_previous;
	Rva00897360Item *m_next;
};

inline Rva00897360Links *rva00897360Links(Rva00897360Item *item)
{
	return (Rva00897360Links *)item - 1;
}

extern Rva00897360Item *g_bfmeHeadDX;

extern int g_bfmeCountDU;
extern Rva008972B0Source g_bfmeEntriesDU[16];
extern void (__cdecl *TheBfmeFreeCount)(void *storage, int count);

extern void __cdecl rva008D2A40(void);
extern void __cdecl rva008D29D0(void);
extern void __cdecl rva008D2960(void);
extern void __cdecl rva008C3B60(void);

// ?rva00897360@@YAX_N@Z
void __cdecl rva00897360(bool skipItems)
{
	int removed = 0;
	g_rva8CD130IdleHook->run();

	Rva00897360Item *item = g_bfmeHeadDX;
	if (item != 0)
	{
		while (item != 0)
		{
			item->m_flags &= 0xffffbfff;
			item = *(Rva00897360Item **)((char *)item - 4);
		}
	}

	if (!skipItems)
	{
		item = g_bfmeHeadDX;
		while (item != 0)
		{
			unsigned char type = (unsigned char)(item->m_flags >> 14);
			if ((item->m_flags & 0x3fc0) != 0 && (type & 1) == 0)
			{
				bfmeCleanup97260((Rva00897260Node *)item);
			}
			item = *(Rva00897360Item **)((char *)item - 4);
		}
	}

	if (!skipItems)
	{
		for (int index = 0; index < g_bfmeCountDU; ++index)
			bfmeWalk972B0((Rva008972B0Source *)&g_bfmeEntriesDU[index]);
	}

	item = g_bfmeHeadDX;
	while (item != 0)
	{
		Rva00897360Item *next = rva00897360Links(item)->m_next;
		unsigned char type = (unsigned char)(item->m_flags >> 14);
		if ((type & 1) == 0)
		{
			Rva00897360Item *previous = rva00897360Links(item)->m_previous;
			if (previous != 0)
				rva00897360Links(previous)->m_next = next;
			if (next != 0)
				rva00897360Links(next)->m_previous = previous;
			if (g_bfmeHeadDX == item)
				g_bfmeHeadDX = next;
			item->op12();
			++removed;
		}
		item = next;
	}

	if (removed != 0)
		TheBfmeFreeCount((void *)0x01135DF0, removed);

	g_rva8CD130IdleHook->run();
	rva008D2A40();
	rva008D29D0();
	rva008D2960();
	rva008C3B60();
}
