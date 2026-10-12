// cl: /O2 /DNDEBUG /MD
// Open-BFME5 conversions.

struct Rva008BD5B0Key
{
	int unused;
	int value;
};

struct Rva008BD5B0Item
{
	char pad[0x50];
	Rva008BD5B0Key *key;
};

class Rva008BD5B0
{
public:
	__declspec(noinline) void insert(Rva008BD5B0Item *item);

	Rva008BD5B0Item *items[32];
	int count;
};

void Rva008BD5B0::insert(Rva008BD5B0Item *item)
{
	int index = 0;
	if (count > 0)
	{
		int value = item->key->value;
		while (index < count && items[index]->key->value >= value)
			++index;
	}
	for (int i = count; i > index; --i)
		items[i] = items[i - 1];
	items[index] = item;
	++count;
}

class BfmeB1038
{
public:
	void bfmeDone1038(void);
};

class BfmeA1038
{
public:
	virtual void bfmeVA01038();
	virtual void bfmeVA11038();
	virtual void bfmeVA21038();
	virtual void bfmeVA31038();
	virtual void bfmeVA41038();
	virtual void bfmeVA51038();
	virtual void bfmeVA61038();
	virtual void bfmeVA71038();
	virtual void bfmeVA81038();
	virtual void bfmeVA91038();
	virtual void bfmeVA101038();
	virtual void bfmeVA111038();
	virtual void bfmeVA121038();
	virtual void bfmeVA131038();
	virtual void bfmeVA141038();
	virtual void bfmeVA151038();
	virtual void bfmeVA161038();
	virtual void bfmeVA171038();
	virtual void bfmeVA181038();
	virtual void bfmeVA191038();
	virtual void bfmeVA201038();
	virtual void bfmeVA211038();
	virtual void bfmeVA221038();
	virtual void bfmeVA231038();
	virtual void bfmeVA241038();
	virtual void bfmeVA251038();
	virtual void bfmeVA261038();
	virtual void bfmeVA271038();
	virtual void bfmeVA281038();
	virtual void bfmeVA291038();
	virtual void bfmeVA301038();
	virtual void bfmeVA311038();
	virtual void bfmeVA321038();
	virtual void bfmeVA331038();
	virtual void bfmeVA341038();
	virtual void bfmeVA351038();
	virtual void bfmeVA361038();
	virtual void bfmeVA371038();
	virtual void bfmeVA381038();
	virtual void bfmeVA391038();
	virtual void bfmeVA401038();
	virtual void bfmeVA411038();
	virtual void bfmeVA421038();
	virtual void bfmeVA431038();
	virtual void bfmeVA441038();
	virtual void bfmeVA451038();
	virtual void bfmeVA461038();
	virtual void bfmeVA471038();
	virtual void bfmeVA481038();
	virtual char bfmeAsk1038();
	void bfmeGo1038A(void);
	void bfmeStep1038(void);
};

void BfmeA1038::bfmeGo1038A(void)
{
	bfmeStep1038();

	if (bfmeAsk1038() != 0)
		((BfmeB1038 *)((char *)this - 0x20))->bfmeDone1038();
}

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void report(const char *message);
};

extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *h);
Rva007EB810Diag *Rva007EB810Get(void);

class BfmeD1038
{
public:
	void bfmeGo1038D(void);

	char m_bfmePad[4];
	void *m_bfmeHandle;
};

void BfmeD1038::bfmeGo1038D(void)
{
	if (ReleaseMutex(m_bfmeHandle) == 0)
		Rva007EB810Get()->report("Error leaving critical section\n");
}

class BfmeY1038
{
public:
	int bfmeVal1038(void);
};

BfmeY1038 * __stdcall bfmeFind1038(int a);

int __stdcall bfmeGo1038E(int a)
{
	BfmeY1038 *y = bfmeFind1038(a);

	if (y == 0)
		return -1;

	return y->bfmeVal1038();
}

class Rva008BDBB0Child
{
public:
	int m_00;
	int m_04;
};

class Rva008BDBB0Node
{
public:
	void *m_00;
	unsigned int m_04;
	int m_08;
	char m_0c[0x44];
	Rva008BDBB0Child *m_50;
	int m_54;
	Rva008BDBB0Node *m_58;
};

class Rva008BDBB0List
{
public:
	Rva008BDBB0Node *m_00;
};

class BfmeSubF1038
{
public:
	void bfmeAdd1038(int a, int b);

	Rva008BDBB0List *m_00;
};

class BfmeAObj1038
{
public:
	void bfmeStop1038F(void);

	char m_bfmePad[0x122c];
	BfmeSubF1038 m_bfmeSub;
};

extern BfmeAObj1038 *g_bfmeA1038;
extern int g_bfmeB1038;
extern int g_bfmeC1038;
void bfmeFlush1038(void);

void bfmeGo1038F(void)
{
	if (g_bfmeA1038 == 0)
		return;

	g_bfmeA1038->bfmeStop1038F();
	bfmeFlush1038();
	g_bfmeA1038->m_bfmeSub.bfmeAdd1038(g_bfmeB1038, 0);
	g_bfmeC1038 -= 0x60;
}

class BfmeA1236;
class BfmeB1236;

void bfmeGo1236(BfmeA1236 *a, BfmeB1236 *b, void *c);
void bfmeTransform1236(void *a, BfmeB1236 *b, void *c);

class BfmeZero1236
{
public:
	BfmeZero1236();

	void *items[32];
	int count;
};

extern unsigned char g_bfmeExtra1282Flags;

class Rva008BDBB0Pending
{
public:
	void *volatile items[32];
	int count;
};

void BfmeSubF1038::bfmeAdd1038(int a, int b)
{
	void *context = (void *)a;
	Rva008BDBB0Node *node = m_00->m_00->m_58;
	BfmeZero1236 storage;
	Rva008BDBB0Pending &pending = (Rva008BDBB0Pending &)storage;
	void (__cdecl *emit)(void *, BfmeB1236 *, void *);

	if (g_bfmeExtra1282Flags & 4)
		emit = bfmeTransform1236;
	else
		emit = (void (__cdecl *)(void *, BfmeB1236 *, void *))bfmeGo1236;
	while (node)
	{
		if (!((unsigned char)(~(node->m_04 >> 15)) & 1) && (node->m_04 & 0x3f) != 0x13)
		{
			if (node->m_50->m_04 >= 0)
			{
				((Rva008BD5B0 *)&pending)->insert((Rva008BD5B0Item *)node);
				emit(context, (BfmeB1236 *)node, (void *)1);
			}
			else
			{
				while (pending.count > 0 && ((Rva008BDBB0Node *)pending.items[pending.count - 1])->m_50->m_04 < node->m_08)
				{
					emit(context, (BfmeB1236 *)pending.items[pending.count - 1], (void *)-1);
					--pending.count;
				}
				emit(context, (BfmeB1236 *)node, (void *)b);
			}
		}
		node = node->m_58;
	}
	while (pending.count > 0)
	{
		emit(context, (BfmeB1236 *)pending.items[0], (void *)-1);
		for (int i = 0; i < pending.count - 1; ++i)
			pending.items[i] = pending.items[i + 1];
		--pending.count;
	}
}

class BfmeI1038
{
public:
	void bfmeGo1038I(void);

	char m_bfmePad[0x508];
	void (__cdecl *m_bfmeFn)(int);
	char m_bfmeFlag;
};

void BfmeI1038::bfmeGo1038I(void)
{
	void (__cdecl *fn)(int) = m_bfmeFn;

	if (fn != 0) {
		fn(m_bfmeFlag != 0);
		m_bfmeFn = 0;
	}
}

inline __declspec(noinline) BfmeZero1236::BfmeZero1236() { count = 0; for (int i = 0; i < 32; ++i) items[i] = 0; }
