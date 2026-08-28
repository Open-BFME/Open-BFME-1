
class BfmeObjF62
{
public:
	void trigger(int a, int b);
};

class BfmeMgrF62
{
public:
	BfmeObjF62* find(int id);
};

extern BfmeMgrF62 *g_bfmeMgr12F0898;

class BfmeBaseF62
{
public:
	virtual void v0();
	virtual int getId();
};

struct BfmeSubF62
{
	void doAction(int dummy);
};

struct BfmeParentF62
{
	BfmeBaseF62 base;
	BfmeSubF62 sub;
};

void BfmeSubF62::doAction(int dummy)
{
	BfmeParentF62 *p = (BfmeParentF62*)((char*)this - 4);
	int id = p->base.getId();
	BfmeObjF62 *obj = g_bfmeMgr12F0898->find(id);
	if (obj)
		obj->trigger(8, 0);
}

class BfmeFilterC9E
{
public:
	bool filter(void *arg);
};

struct BfmeArgC9E
{
	unsigned char pad[0x344];
	char m_flag344;
};

struct BfmeThingC9E
{
	unsigned char pad[8];
	BfmeFilterC9E *m_filter;
	int check(BfmeArgC9E *arg);
};

int BfmeThingC9E::check(BfmeArgC9E *arg)
{
	if (m_filter && m_filter->filter(arg)) {
		if ((arg->m_flag344 & 1) == 0)
			return 1;
	}
	return 0;
}

class BfmeSubInnerD77
{
public:
	void* getFinal();
};

struct BfmeSubD77
{
	unsigned char pad[4];
	BfmeSubInnerD77 *m_inner;
};

struct BfmeArgD77
{
	unsigned char pad[4];
	BfmeSubD77 *m_sub;
};

class BfmeHelperD77
{
public:
	char query(void *p);
};

struct BfmeThingD77
{
	unsigned char pad[8];
	BfmeHelperD77 *m_helper;
	char m_flagC;
	bool matches(BfmeArgD77 *arg);
};

bool BfmeThingD77::matches(BfmeArgD77 *arg)
{
	BfmeSubD77 *s = arg->m_sub;
	if (s && s->m_inner)
		s = (BfmeSubD77*)s->m_inner->getFinal();
	return m_helper->query(s) == m_flagC;
}

class BfmeSubVfnD1B
{
public:
	virtual void v0();
	virtual void v1();
	virtual char vfn2();
};

struct BfmeArgD1B
{
	unsigned char pad[0x1fc];
	BfmeSubVfnD1B *m_sub;
};

struct BfmeThingD1B
{
	unsigned char pad[8];
	char m_flag8;
	bool matches(BfmeArgD1B *arg);
};

bool BfmeThingD1B::matches(BfmeArgD1B *arg)
{
	BfmeSubVfnD1B *sub = arg->m_sub;
	if (!sub)
		return m_flag8 == 0;
	return sub->vfn2() == m_flag8;
}

class BfmeItemVfn404
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void vfn8();
};

struct BfmeListNode404
{
	BfmeListNode404 *next;
	BfmeListNode404 *prev;
	BfmeItemVfn404 *item;
};

extern void *g_global12EF1D8;

struct BfmeThing404
{
	unsigned char pad[0x538];
	BfmeListNode404 *m_listHead;
	void notifyAll();
};

void BfmeThing404::notifyAll()
{
	if (g_global12EF1D8) {
		for (BfmeListNode404 *curr = m_listHead->next; curr != m_listHead; curr = curr->next) {
			curr->item->vfn8();
		}
	}
}
