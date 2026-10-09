// cl: /GS
// BfmeH1052::bfmeDo1052 @ 0x00800BD0 (164B).

void *Rva007F93E0(void *a, void *b, void *c) throw();

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *k, void *v) throw();
};

class BfmeC994
{
public:
	BfmeC994(char *buf, int n) throw();

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	char m_pad10[0x0c];
	int m_1c;
	int m_20;
	char m_pad24[0x10];
};

class Gen_007e86c0
{
public:
	void m();
};

class BfmeI1052
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
};

struct BfmeRecord00800C80
{
	int m_value;
	char m_pad[12];
	BfmeI1052 m_item;
};

extern const char g_feslTransactionIdKey[4];
extern const char g_feslTypeKey[5];

class BfmeH1052
{
public:
	void bfmeDo1052(int a, BfmeI1052 *p, int r);
	void forward00800C80(BfmeRecord00800C80 *record);

	char m_pad[0x10];
	void *m_10;
};

void BfmeH1052::bfmeDo1052(int a, BfmeI1052 *p, int r)
{
	char buf[0x20];
	char fa = (char)a;
	BfmeC994 msg(buf, 0x20);
	int f04 = p->m_04;
	int f08 = p->m_08;
	int f0c = p->m_0c;
	msg.m_04 = f04;
	msg.m_08 = f08;
	msg.m_0c = f0c;
	msg.m_1c = 0x50524F42;
	msg.m_20 = fa ? (int)0xC0000000 : 0;
	((BfmeThingCIB *)&msg)->bfmeGoCIB((void *)g_feslTransactionIdKey, (void *)r);
	((BfmeThingCIB *)&msg)->bfmeGoCIB((void *)const_cast<char *>(g_feslTypeKey), (void *)1);
	Rva007F93E0(&msg, "->D", m_10);
	((Gen_007e86c0 *)&msg)->m();
}

void BfmeH1052::forward00800C80(BfmeRecord00800C80 *record)
{
	bfmeDo1052(1, &record->m_item, record->m_value);
}
