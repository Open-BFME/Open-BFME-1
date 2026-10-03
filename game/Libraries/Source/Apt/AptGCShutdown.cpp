// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Opaque Apt cleanup at RVA 0x00897360; full extent 257 bytes.
// Evidence: targets/game/reverse/identity_evidence/00897360-link-copy.md
// The value copy of the intrusive header preserves the independent successor
// temporary used while the outer loop retains its next item across vslot 12.

class BfmeItemDX;

class BfmeLinksDX
{
public:
	BfmeItemDX *m_bfmePrev;					// -0x08
	BfmeItemDX *m_bfmeNext;					// -0x04
};

class BfmeItemDX
{
public:
	virtual void v0(void);
	virtual void v1(void);
	virtual void v2(void);
	virtual void v3(void);
	virtual void v4(void);
	virtual void v5(void);
	virtual void v6(void);
	virtual void v7(void);
	virtual void v8(void);
	virtual void v9(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);					// vtable +0x30

	unsigned int m_bfmeFlags;				// +0x04
};

// The links live in the header just ahead of the item.
inline BfmeLinksDX *bfmeLinksDX(BfmeItemDX *item)
{
	return (BfmeLinksDX *)item - 1;
}

extern BfmeItemDX *g_bfmeHeadDX;				// retail 0x013379A0

inline void bfmeRemove(BfmeItemDX *item)
{
	BfmeLinksDX links = *bfmeLinksDX(item);
	BfmeItemDX *previous = links.m_bfmePrev;
	BfmeItemDX *next = links.m_bfmeNext;

	if (previous != 0)
		bfmeLinksDX(previous)->m_bfmeNext = next;

	if (next != 0)
		bfmeLinksDX(next)->m_bfmePrev = previous;

	if (g_bfmeHeadDX == item)
		g_bfmeHeadDX = next;
}

class Rva8CD130IdleHook
{
public:
	void run(void);						// retail 0x008A30C0
};

extern Rva8CD130IdleHook *g_rva8CD130IdleHook;			// retail 0x01337810

class Rva00897260Node;

void __cdecl bfmeCleanup97260(Rva00897260Node *node);		// retail 0x00897260

class Rva008972B0Source
{
public:
	void *m_data;						// +0x00
	int (__cdecl *getCount)(void *data);			// +0x04
	void *(__cdecl *getItem)(void *data, int index);	// +0x08
};

void __cdecl bfmeWalk972B0(Rva008972B0Source *source);		// retail 0x008972B0

extern int g_bfmeCountDU;					// retail 0x013379A4
extern Rva008972B0Source g_bfmeEntriesDU[];			// retail 0x013378E0

// Same callback storage and variadic call view as TraceRva008C7D30.cpp.
extern "C" void (__cdecl *g_bfmeCallback1226)(const void *, const void *);

void __cdecl shutdownChain008D2A40(void);			// retail 0x008D2A40
void __cdecl shutdownChain008D29D0(void);			// retail 0x008D29D0
void __cdecl shutdownChain2(void);				// retail 0x008D2960
void __cdecl shutdownChain(void);				// retail 0x008C3B60

// ?rva00897360@@YAX_N@Z
void __cdecl rva00897360(bool skipItems)
{
	int removed = 0;

	g_rva8CD130IdleHook->run();

	BfmeItemDX *item = g_bfmeHeadDX;

	while (item != 0)
	{
		item->m_bfmeFlags &= 0xffffbfff;

		item = bfmeLinksDX(item)->m_bfmeNext;
	}

	if (!skipItems)
	{
		item = g_bfmeHeadDX;

		while (item != 0)
		{
			unsigned int flags = item->m_bfmeFlags;
			unsigned char type = (unsigned char)(flags >> 14);

			if ((flags & 0x3fc0) != 0 && (type & 1) == 0)
				bfmeCleanup97260((Rva00897260Node *)item);

			item = bfmeLinksDX(item)->m_bfmeNext;
		}

		for (int index = 0; index < g_bfmeCountDU; ++index)
			bfmeWalk972B0(&g_bfmeEntriesDU[index]);
	}

	item = g_bfmeHeadDX;

	while (item != 0)
	{
		BfmeItemDX *next = bfmeLinksDX(item)->m_bfmeNext;
		unsigned char type = (unsigned char)(item->m_bfmeFlags >> 14);

		if ((type & 1) == 0)
		{
			bfmeRemove(item);

			item->v12();

			++removed;
		}

		item = next;
	}

	if (removed != 0)
		((void (__cdecl *)(const char *, ...))g_bfmeCallback1226)(
			"Apt-GC---------------------- Sweeping of %d objects\n", removed);

	g_rva8CD130IdleHook->run();

	shutdownChain008D2A40();
	shutdownChain008D29D0();
	shutdownChain2();
	shutdownChain();
}
