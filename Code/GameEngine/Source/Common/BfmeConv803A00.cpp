// cl: /GS
// FESL CONN builder @ 0x00803A00 (147B).
// Two stamped ints, optional TID, submit. Calls pinned 0x008038F0.

class BfmeMsg803A00
{
public:
	BfmeMsg803A00(char *buf, int n) throw();
	~BfmeMsg803A00() throw();
	void addInt(const char *k, int v) throw();

	char m_pad[0x1c];
	unsigned int m_category;
	char m_pad20[0x14];
};

class BfmeSrc803A00
{
public:
	int getInt(const char *k, int d) throw();
};

class BfmeOwner803A00
{
public:
	void go(BfmeSrc803A00 *src);
	void send(BfmeMsg803A00 *m) throw();
};

extern char g_bfmeName1052[];
extern char g_bfmeKey803A00A[];
extern char g_bfmeKey803A00B[];

void BfmeOwner803A00::go(BfmeSrc803A00 *src)
{
	char buf[0x40];
	BfmeMsg803A00 msg(buf, 0x40);
	msg.m_category = 'CONN';
	msg.addInt(g_bfmeKey803A00A, 2);
	msg.addInt(g_bfmeKey803A00B, 0);
	int tid = src->getInt(g_bfmeName1052, -1);
	if (tid != -1)
		msg.addInt(g_bfmeName1052, tid);
	send(&msg);
}
