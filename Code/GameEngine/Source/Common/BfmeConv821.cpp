
class BfmeSub204_2C0
{
public:
	void doCall(int dummy);
};

struct BfmeOwner2C0
{
	unsigned char pad[0x204];
	BfmeSub204_2C0 *m_sub204;
};

struct BfmeThing2C0
{
	void doAction();
};

struct BfmeParent2C0
{
	BfmeOwner2C0 *m_owner;
	unsigned char pad[4];
	BfmeThing2C0 sub;
};

void BfmeThing2C0::doAction()
{
	BfmeParent2C0 *p = (BfmeParent2C0*)((char*)this - 8);
	if (p->m_owner->m_sub204)
		p->m_owner->m_sub204->doCall(0);
}

class BfmeTarget78E
{
public:
	void doUpdate(void *p);
};

class BfmeFinder78E
{
public:
	BfmeTarget78E* findTarget();
};

struct BfmeThing78E
{
	void doAction();
};

void BfmeThing78E::doAction()
{
	BfmeFinder78E *finder = *(BfmeFinder78E**)((char*)this - 8);
	char *ptr = *(char**)((char*)this - 0xc);
	BfmeTarget78E *target = finder->findTarget();
	if (target)
		target->doUpdate(ptr + 0x78);
}

class BfmeThingCEE
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void vfn6(void *a, void *b);
	void doCall(void *a, char *b);
};

void BfmeThingCEE::doCall(void *a, char *b)
{
	if (b && a)
		vfn6(a, b + 0x38);
}

class BfmeObj412
{
public:
	void call(void *b, void *c);
};

class BfmeMgr412
{
public:
	BfmeObj412* lookup(void *p);
};

extern BfmeMgr412 *g_mgr12F33F8;

void __cdecl bfmeHelper412(char *a, void *b, void *c)
{
	BfmeObj412 *obj = g_mgr12F33F8->lookup(a + 0x70);
	if (obj)
		obj->call(b, c);
}

class BfmeSubVfn46D
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
	virtual void vfn8(int val);
	virtual void vfn9();
};

struct BfmeSubE8_46D
{
	unsigned char pad[0x81];
	char m_flag81;
};

struct BfmeThing46D
{
	unsigned char pad[4];
	char m_flag4;
	void doAction();
};

void BfmeThing46D::doAction()
{
	BfmeSubE8_46D *subE8 = *(BfmeSubE8_46D**)((char*)this - 0x18);
	if (subE8->m_flag81) {
		BfmeSubVfn46D *sub = (BfmeSubVfn46D*)((char*)this - 0xc);
		sub->vfn9();
		sub->vfn8(1);
	}
	m_flag4 = 1;
}
