class BfmeThingERO;

class BfmeBaseERO
{
public:
	virtual void bfmeBase00ERO();
	virtual void bfmeBase01ERO();
	virtual void bfmeBase02ERO();
	virtual void bfmeBase03ERO();
	virtual void bfmeBase04ERO();
	virtual void bfmeBase05ERO();
	virtual void bfmeBase06ERO();
	virtual void bfmeBase07ERO();
	virtual void bfmeBase08ERO();
	virtual void bfmeBase09ERO();
	virtual void bfmeBase10ERO();
	virtual void bfmeBase11ERO();
	virtual void bfmeBase12ERO();
	virtual void bfmeBase13ERO();
};

class BfmeObjERO
{
public:
	virtual void bfmeSlot00ERO();
	virtual void bfmeSlot01ERO();
	virtual void bfmeSlot02ERO(BfmeThingERO *thing, void *extra);
	virtual void bfmeSlot03ERO();
	virtual void bfmeSlot04ERO();
	virtual void bfmeSlot05ERO();
	virtual void bfmeSlot06ERO();
	virtual void bfmeSlot07ERO();
	virtual void bfmeSlot08ERO();
	virtual void bfmeSlot09ERO();
	virtual void bfmeSlot10ERO();
	virtual void bfmeSlot11ERO();
};

class BfmeSrcERO
{
public:
	BfmeObjERO *bfmeMakeERO();
};

class BfmeThingERO
{
public:
	void *bfmeFindERO(int key);
};

class BfmeLogicERO
{
public:
	BfmeThingERO *bfmeFindByIdERO(int id);
};

extern BfmeLogicERO *g_bfmeLogicERO;

class BfmeKeyGenERO
{
public:
	int bfmeNameToKeyERO(const char *name);
};

extern BfmeKeyGenERO *g_bfmeKeyGenERO;

class BfmeHostERO
{
public:
	void bfmeGoERO(int unused);

	unsigned char m_bfmeHeadERO[0xb4];
	int m_bfmeIdERO;
};

void BfmeHostERO::bfmeGoERO(int unused)
{
	((BfmeBaseERO *)((char *)this - 4))->bfmeBase13ERO();

	BfmeObjERO *obj = (*(BfmeSrcERO **)((char *)this - 0x1c))->bfmeMakeERO();

	int id = m_bfmeIdERO;

	if (id != 0)
	{
		BfmeThingERO *thing = g_bfmeLogicERO->bfmeFindByIdERO(id);

		if (thing != 0)
		{
			static int s_bfmeKeyERO =
				g_bfmeKeyGenERO->bfmeNameToKeyERO("RespawnUpdate");

			void *mod = thing->bfmeFindERO(s_bfmeKeyERO);

			if (mod == 0)
				obj->bfmeSlot02ERO(thing, mod);
		}
	}

	if (obj != 0)
		obj->bfmeSlot11ERO();
}
