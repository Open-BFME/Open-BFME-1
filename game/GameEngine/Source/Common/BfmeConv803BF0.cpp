// cl: /GS
// FESL LLST builder @ 0x00803BF0 (157B).
// NUM-LOBBIES=1, optional TID, submit, then bfmeGoVJH(TID).

// Matched callee rows (callees.py, via ILT): BfmeC994::BfmeC994 0x007E8850,
// BfmeThingCIB::bfmeGoCIB 0x007E88D0, BfmeThingRF::bfmeGoRF 0x007E8900,
// Rva008038F0Sender::send 0x008038F0, BfmeThingVJH::bfmeGoVJH 0x00803970.
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

class BfmeThingVJH
{
public:
	void bfmeGoVJH(int a) throw();
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

class BfmeSrc803BF0
{
public:
};

class Rva008038F0Sender
{
public:
	void send(BfmeC994 *m) throw();
};

class BfmeOwner803BF0
{
public:
	void go(BfmeSrc803BF0 *src);
};

extern const char g_feslTransactionIdKey[4];
// Retail .rdata VA 0x0112B4E8 holds this NUL-terminated key.
char g_bfmeNumLobbies803BF0[12] = "NUM-LOBBIES";

void BfmeOwner803BF0::go(BfmeSrc803BF0 *src)
{
	char buf[0x40];
	BfmeC994 msg(buf, 0x40);
	msg.m_category = 'LLST';
	((BfmeThingCIB *)&msg)->bfmeGoCIB(g_bfmeNumLobbies803BF0, (void *)1);
	int tid = (int)((BfmeThingRF *)src)->bfmeGoRF((void *)g_feslTransactionIdKey, (void *)-1);
	if (tid != -1)
		((BfmeThingCIB *)&msg)->bfmeGoCIB((void *)g_feslTransactionIdKey, (void *)tid);
	((Rva008038F0Sender *)this)->send(&msg);
	((BfmeThingVJH *)this)->bfmeGoVJH(
		(int)((BfmeThingRF *)src)->bfmeGoRF((void *)g_feslTransactionIdKey, 0));
	((Gen_007e86c0 *)&msg)->m();
}
