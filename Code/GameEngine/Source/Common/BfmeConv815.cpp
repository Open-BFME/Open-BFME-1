
struct BfmeThing174
{
	unsigned char pad[0x50c];
	int m_val50C;
	int toInt(int dummy);
};

int BfmeThing174::toInt(int dummy)
{
	return (int)(float)m_val50C;
}

struct BfmeArg171
{
	unsigned char pad[0x10];
	float f10;
};

struct BfmeThing171
{
	unsigned char pad[0x500];
	int m_val500;
	int scaleToInt(BfmeArg171 *arg);
};

int BfmeThing171::scaleToInt(BfmeArg171 *arg)
{
	return (int)((float)m_val500 * arg->f10);
}

class BfmeFinderD02
{
public:
	int find(int val);
};

struct BfmeThingD02
{
	unsigned char m_pad[0x8];
	int m_val8;
	bool contains(BfmeFinderD02 *finder);
};

bool BfmeThingD02::contains(BfmeFinderD02 *finder)
{
	return finder->find(m_val8) == 1;
}

class BfmeSub9BB
{
public:
	void doAction();
};

struct BfmeSub4_9BB
{
	unsigned char pad[0xc4];
	char m_flagC4;
};

struct BfmeThing9BB
{
	unsigned char pad[4];
	BfmeSub4_9BB *m_sub4;
	unsigned char pad2[0x34];
	char m_flag3C;
	char m_flag3D;
	void checkAndRun();
};

void BfmeThing9BB::checkAndRun()
{
	if (!m_flag3D) {
		if (m_sub4->m_flagC4 || m_flag3C)
			((BfmeSub9BB*)this)->doAction();
	}
}

class BfmeObjEB2
{
public:
	void trigger(int a, int b);
};

class BfmeMgrEB2
{
public:
	BfmeObjEB2* find(int id);
};

extern BfmeMgrEB2 *g_bfmeMgr12F0898;

struct BfmeSubEB2
{
	unsigned char m_pad[0x7c];
	int m_id;
};

struct BfmeThingEB2
{
	unsigned char m_pad[0x8];
	BfmeSubEB2 *m_sub;
	void doTrigger();
};

void BfmeThingEB2::doTrigger()
{
	if (m_sub) {
		BfmeObjEB2 *obj = g_bfmeMgr12F0898->find(m_sub->m_id);
		if (obj)
			obj->trigger(8, 0x16);
	}
}

class BfmeSubHelperCAB
{
public:
	int checkState(void *a, void *b, void *c);
};

struct BfmeThingCAB
{
	unsigned char m_pad[0x8];
	BfmeSubHelperCAB *m_helper;
	void *m_argC;
	void *m_arg10;
	bool isMatch(void *param);
};

bool BfmeThingCAB::isMatch(void *param)
{
	int res = m_helper->checkState(m_arg10, param, m_argC);
	if (res == 3 || res == 2)
		return true;
	return false;
}

struct BfmeItemE63
{
	unsigned char pad[0x14];
	void *m_p14;
	unsigned char pad2[0x24 - 0x18];
	char m_flag24;
	bool checkValid();
};

BfmeItemE63* __cdecl bfmeFindItemE63(int id);

struct BfmeThingE63
{
	unsigned char pad[8];
	int m_id;
	bool isValid();
};

bool BfmeThingE63::isValid()
{
	int id = m_id;
	BfmeItemE63 *item = bfmeFindItemE63(id);
	if (item && item->m_p14 && !item->m_flag24 && item->checkValid())
		return true;
	return false;
}
