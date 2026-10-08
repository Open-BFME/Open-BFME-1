// cl: /GS
// FESL HGAM/unsp request builder @ 0x00803C90 (123B).
// Local message, optional TID from src, submit via the 0x008038F0 sender.

class BfmeC994
{
public:
	BfmeC994(char *buf, int n);

	char m_pad[0x1c];
	unsigned int m_category;
	unsigned int m_sub;
	char m_pad20[0x10];
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *key, void *value);
};

class BfmeThingRF
{
public:
	void *bfmeGoRF(void *key, void *dflt);
};

class Rva008038F0Sender
{
public:
	void send(BfmeC994 *message);
};

class Gen_007e86c0
{
public:
	void m();
};

class BfmeSrc803C90;

class BfmeOwner803C90
{
public:
	void go(BfmeSrc803C90 *src);
};

extern const char g_feslTransactionIdKey[4];

void BfmeOwner803C90::go(BfmeSrc803C90 *src)
{
	char buf[0x40];
	BfmeC994 msg(buf, 0x40);
	msg.m_category = 'HGAM';
	msg.m_sub = 'unsp';
	int tid = (int)((BfmeThingRF *)src)->bfmeGoRF((void *)g_feslTransactionIdKey, (void *)-1);
	if (tid != -1)
		((BfmeThingCIB *)&msg)->bfmeGoCIB((void *)g_feslTransactionIdKey, (void *)tid);
	((Rva008038F0Sender *)this)->send(&msg);
	((Gen_007e86c0 *)&msg)->m();
}
