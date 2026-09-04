// cl: /GS
// FESL LLST builder @ 0x00803BF0 (157B).
// NUM-LOBBIES=1, optional TID, submit, then bfmeGoVJH(TID).

class BfmeMsg803BF0
{
public:
	BfmeMsg803BF0(char *buf, int n) throw();
	~BfmeMsg803BF0() throw();
	void addInt(const char *k, int v) throw();

	char m_pad[0x1c];
	unsigned int m_category;
	char m_pad20[0x14];
};

class BfmeSrc803BF0
{
public:
	int getInt(const char *k, int d) throw();
};

class BfmeOwner803BF0
{
public:
	void go(BfmeSrc803BF0 *src);
	void send(BfmeMsg803BF0 *m) throw();
	void bfmeGoVJH(int a) throw();
};

extern char g_bfmeName1052[];
extern char g_bfmeNumLobbies803BF0[];

void BfmeOwner803BF0::go(BfmeSrc803BF0 *src)
{
	char buf[0x40];
	BfmeMsg803BF0 msg(buf, 0x40);
	msg.m_category = 'LLST';
	msg.addInt(g_bfmeNumLobbies803BF0, 1);
	int tid = src->getInt(g_bfmeName1052, -1);
	if (tid != -1)
		msg.addInt(g_bfmeName1052, tid);
	send(&msg);
	bfmeGoVJH(src->getInt(g_bfmeName1052, 0));
}
