// cl: /GS
// FESL CONN builder @ 0x00803A00 (147B).
// Two stamped ints, optional TID, submit. Calls pinned 0x008038F0.

// Matched callee rows (callees.py, direct calls): BfmeC994 ctor 0x007E8850,
// BfmeThingCIB::bfmeGoCIB 0x007E88D0, BfmeThingRF::bfmeGoRF 0x007E8900, Rva008038F0Sender::send 0x008038F0.
class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *k, void *v) throw();
};

class BfmeThingRF
{
public:
	void *bfmeGoRF(void *k, void *d) throw();
};

class Rva008038F0Sender
{
public:
	void send(class BfmeC994 *m) throw();
};

class BfmeC994
{
public:
	BfmeC994(char *buf, int n) throw();

	char m_pad[0x1c];
	unsigned int m_category;
	char m_pad20[0x14];
};

class Gen_007e86c0
{
public:
	void m();
};

class BfmeSrc803A00
{
public:
};

class BfmeOwner803A00
{
public:
	void go(BfmeSrc803A00 *src);
};

extern const char g_feslTransactionIdKey[4];

void BfmeOwner803A00::go(BfmeSrc803A00 *src)
{
	char buf[0x40];
	BfmeC994 msg(buf, 0x40);
	msg.m_category = 'CONN';
	((BfmeThingCIB *)&msg)->bfmeGoCIB("PROT", (void *)2);
	((BfmeThingCIB *)&msg)->bfmeGoCIB("TIME", 0);
	int tid = (int)((BfmeThingRF *)src)->bfmeGoRF((void *)g_feslTransactionIdKey, (void *)-1);
	if (tid != -1)
		((BfmeThingCIB *)&msg)->bfmeGoCIB((void *)g_feslTransactionIdKey, (void *)tid);
	((Rva008038F0Sender *)this)->send(&msg);
	((Gen_007e86c0 *)&msg)->m();
}
