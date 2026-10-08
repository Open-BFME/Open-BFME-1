// cl: /GS
// FESL RLST builder @ 0x00803B60 (131B).
// NUM-REGIONS=0, optional TID from src, submit.

class BfmeC994
{
public:
	BfmeC994(char *buf, int n);

	char m_pad[0x1c];
	unsigned int m_category;
	char m_pad20[0x14];
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

class BfmeSrc803B60;

class BfmeOwner803B60
{
public:
	void go(BfmeSrc803B60 *src);
};

extern const char g_feslTransactionIdKey[4];

void BfmeOwner803B60::go(BfmeSrc803B60 *src)
{
	char buf[0x40];
	BfmeC994 msg(buf, 0x40);
	msg.m_category = 'RLST';
	((BfmeThingCIB *)&msg)->bfmeGoCIB((void *)"NUM-REGIONS", (void *)0);
	int tid = (int)((BfmeThingRF *)src)->bfmeGoRF((void *)g_feslTransactionIdKey, (void *)-1);
	if (tid != -1)
		((BfmeThingCIB *)&msg)->bfmeGoCIB((void *)g_feslTransactionIdKey, (void *)tid);
	((Rva008038F0Sender *)this)->send(&msg);
	((Gen_007e86c0 *)&msg)->m();
}
