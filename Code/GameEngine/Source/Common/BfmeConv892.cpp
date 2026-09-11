class BfmeSubFCB
{
public:
	void bfmeCallFCB(void *a, int z);
};

class Player;

class Object
{
public:
	virtual void bfmeVirtual00();
	virtual void bfmeVirtual01();
	virtual void bfmeVirtual02();
	virtual void bfmeVirtual03();
	virtual void bfmeVirtual04();
	virtual void bfmeVirtual05();
	virtual void bfmeVirtual06();
	virtual void bfmeVirtual07();
	virtual void bfmeVirtual08();
	virtual void bfmeVirtual09();
	virtual void *bfmeVirtual10();
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class PlayerList
{
public:
	char m_pad[0xc];
	Player *m_localPlayer;
};

extern void j_0000f763();

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define ThePlayers (*(PlayerList **)0x012ED748)

class BfmeOwnFCB
{
public:
	void bfmeAfterFCB();

	virtual void bfmeAnchorFCB();
	char m_pad0[4];
	Object *m_object;
	char m_pad1[0xd8];
	int m_objectID;
};

class BfmeAfterFCBTarget
{
public:
	void apply(int type, float x, float y, float z);
};

typedef void (BfmeAfterFCBTarget::*BfmeAfterFCBApply)(
	int, float, float, float);

void BfmeOwnFCB::bfmeAfterFCB()
{
	register BfmeOwnFCB &owner = *this;
	Object *found = TheBfmeGameLogic->findObjectByID(owner.m_objectID);
	if (found)
	{
		Object *object = owner.m_object;
		if (object)
		{
			Player *local = ThePlayers->m_localPlayer;
			Player *objectPlayer = object->getControllingPlayer();
			if (local && objectPlayer)
			{
				void *first;
				void *second;
				if (local == objectPlayer)
				{
					first = found->bfmeVirtual10();
					second = object->bfmeVirtual10();
				}
				else
				{
					first = object->bfmeVirtual10();
					second = found->bfmeVirtual10();
				}
				if (first)
				{
					union { void (*asFunction)(); BfmeAfterFCBApply asMember; } thunk;
					thunk.asFunction = j_0000f763;
					(reinterpret_cast<BfmeAfterFCBTarget *>(first)->*thunk.asMember)(
						5, 0.2f, 0.7f, 2.0f);
				}
				if (second)
				{
					union { void (*asFunction)(); BfmeAfterFCBApply asMember; } thunk;
					thunk.asFunction = j_0000f763;
					(reinterpret_cast<BfmeAfterFCBTarget *>(second)->*thunk.asMember)(
						0, 0.2f, 0.7f, 2.0f);
				}
			}
		}
	}
}

struct BfmeThingFCB
{
	void bfmeGoFCB(void *a);
};

void BfmeThingFCB::bfmeGoFCB(void *a)
{
	BfmeSubFCB *s = *(BfmeSubFCB **)((char *)this - 8);
	if (s)
	{
		s->bfmeCallFCB(a, 0);
		((BfmeOwnFCB *)((char *)this - 0x10))->bfmeAfterFCB();
	}
}

struct BfmePairFCD
{
	void *m_bfmeA;
	void *m_bfmeB;
	char m_bfmeFlag;
};

class BfmeObjFCD
{
public:
	char bfmeCallFCD(void *a, void *b);
};

void bfmeGoFCD(BfmeObjFCD *o, BfmePairFCD *p)
{
	char r = (o->bfmeCallFCD(p->m_bfmeA, p->m_bfmeB) == 0);
	p->m_bfmeFlag |= r;
}

struct BfmeItemFCE
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeV36();
	virtual void bfmeV37();
	virtual void bfmeV38();
	virtual void bfmeV39();
	virtual void bfmeV40();
	virtual void bfmeV41();
	virtual void bfmeV42();
	virtual void bfmeV43();
	virtual void bfmeV44();
	virtual void bfmeV45();
	virtual void bfmeV46();
	virtual void bfmeV47();
	virtual void bfmeV48();
	virtual void bfmeV49();
	virtual bool bfmeVirt50FCE(void *a, void *b);
};

struct BfmeSubFCE
{
	unsigned char m_bfmeHead[0x1fc];
	BfmeItemFCE *m_bfmeIt;
};

struct BfmeOwnFCE
{
	unsigned char m_bfmeHead[0x214];
	BfmeSubFCE *m_bfmeS;
};

struct BfmeThingFCE
{
	bool bfmeGoFCE(void *a, void *b);
};

bool BfmeThingFCE::bfmeGoFCE(void *a, void *b)
{
	BfmeSubFCE *s = (*(BfmeOwnFCE **)((char *)this - 0x18))->m_bfmeS;
	if (s)
	{
		BfmeItemFCE *it = s->m_bfmeIt;
		if (it)
			return it->bfmeVirt50FCE(a, b);
	}
	return false;
}

struct BfmeNodeFCH
{
	BfmeNodeFCH *m_bfmeNext;
	unsigned char m_bfmePad[4];
	void *m_bfmeVal;
};

struct BfmeThingFCH
{
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeV5();
	virtual void bfmeV6();
	virtual void bfmeV7();
	virtual void bfmeV8();
	virtual void bfmeV9();
	virtual void bfmeV10();
	virtual void bfmeV11();
	virtual void bfmeV12();
	virtual void bfmeV13();
	virtual void bfmeV14();
	virtual void bfmeV15();
	virtual void bfmeV16();
	virtual void bfmeV17();
	virtual void bfmeV18();
	virtual void bfmeV19();
	virtual void bfmeV20();
	virtual void bfmeV21();
	virtual void bfmeV22();
	virtual void bfmeV23();
	virtual void bfmeV24();
	virtual void bfmeV25();
	virtual void bfmeV26();
	virtual void bfmeV27();
	virtual void bfmeV28();
	virtual void bfmeV29();
	virtual void bfmeV30();
	virtual void bfmeV31();
	virtual void bfmeV32();
	virtual void bfmeV33();
	virtual void bfmeV34();
	virtual void bfmeV35();
	virtual void bfmeVirt36FCH(void *v, int f);
	void *bfmeGoFCH();
	unsigned char m_bfmeHead[0xc0];
	BfmeNodeFCH *m_bfmeList;
};

void *BfmeThingFCH::bfmeGoFCH()
{
	BfmeNodeFCH *head = m_bfmeList;
	BfmeNodeFCH *n = head->m_bfmeNext;
	if (n != head)
	{
		void *v = n->m_bfmeVal;
		bfmeVirt36FCH(v, 1);
		return v;
	}
	return 0;
}
