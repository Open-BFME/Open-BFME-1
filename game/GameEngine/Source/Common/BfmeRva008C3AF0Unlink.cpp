// Drop a hashed node's last hold and unlink it from its bucket.

class BfmeNode3AF0
{
public:
	virtual void destroy(void);
	virtual void release(void);

	unsigned int m_bfmeFlags;				// +0x04
	unsigned char *m_bfmeKey;				// +0x08
	BfmeNode3AF0 *m_bfmeNext;				// +0x0C
};

extern int g_bfmeHashCount3AF0;					// retail 0x01338474
extern BfmeNode3AF0 **g_bfmeHashArr3AF0;			// retail 0x01338470

// ?bfmeUnlink3AF0@@YAXPAVBfmeNode3AF0@@@Z
void __cdecl bfmeUnlink3AF0(BfmeNode3AF0 *node)
{
	unsigned int flags = node->m_bfmeFlags;
	unsigned int hold = (flags >> 6) & 0xFF;

	if (hold == 0xFF)
		return;

	node->m_bfmeFlags = flags - 0x40;

	if (hold != 1)
		return;

	unsigned short key = *(unsigned short *)(node->m_bfmeKey + 6);
	unsigned short bucket = (unsigned short)((int)key % g_bfmeHashCount3AF0);

	BfmeNode3AF0 **slot = &g_bfmeHashArr3AF0[bucket];
	BfmeNode3AF0 *head = *slot;

	if (head == node)
	{
		*slot = node->m_bfmeNext;
		node->release();
		return;
	}

	while (head->m_bfmeNext != node)
		head = head->m_bfmeNext;

	head->m_bfmeNext = node->m_bfmeNext;
	node->release();
}

class BfmeG1211
{
public:
	void bfmeStep1211C(void);
};

extern BfmeG1211 *g_bfme1211;
extern void (__cdecl *g_bfmeFreeDWF)(void *);

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern BfmeStringData3AF0 *g_bfmeRouteKeys1282[];
extern int g_bfmeCount1233;

// ?bfmeClearHash3AF0@@YAXXZ
void __cdecl bfmeClearHash3AF0(void)
{
	int count = g_bfmeHashCount3AF0;
	int index = 0;

	if (count > 0)
	{
		do
		{
			BfmeNode3AF0 *node = g_bfmeHashArr3AF0[index];

			if (node != 0)
			{
				do
				{
					BfmeNode3AF0 *next = node->m_bfmeNext;

					node->release();
					node = next;
				} while (node != 0);

				g_bfme1211->bfmeStep1211C();
			}

			count = g_bfmeHashCount3AF0;
			++index;
		} while (index < count);
	}

	g_bfmeFreeDWF(g_bfmeHashArr3AF0);
	g_bfmeHashArr3AF0 = 0;
	g_bfmeHashCount3AF0 = 0;

	BfmeStringData3AF0 **slot = g_bfmeRouteKeys1282;

	do
	{
		BfmeStringData3AF0 *data = *slot;

		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);

		++g_bfmeDefaultString1284.m_refCount;
		*slot = &g_bfmeDefaultString1284;
		++slot;
	} while ((int)slot < (int)(void *)&g_bfmeCount1233);
}
