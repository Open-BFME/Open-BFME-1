class BfmeThingYT;

class BfmeInnerYT
{
public:
	BfmeThingYT *bfmeResolveYT(void);
};

class BfmeThingYT
{
public:
	int m_bfmeSpareYT;
	BfmeInnerYT *m_bfmeInnerYT;
	unsigned char m_bfmeGapYT[0xcc];
	int m_bfmeFlagsYT;
};

char __cdecl bfmeFilterYT(void *item);

typedef char (__cdecl *BfmeFilterFnYT)(void *item);

class BfmeSinkYT
{
public:
	virtual void bfmeV0YT(void);
	virtual void bfmeV1YT(void);
	virtual void bfmeV2YT(void);
	virtual void bfmeV3YT(void);
	virtual void bfmeV4YT(void);
	virtual void bfmeV5YT(void);
	virtual void bfmeV6YT(void);
	virtual void bfmeV7YT(void);
	virtual void bfmeV8YT(void);
	virtual void bfmeV9YT(void);
	virtual void bfmeV10YT(void);
	virtual void bfmeV11YT(void);
	virtual void bfmeV12YT(void);
	virtual void bfmeV13YT(void);
	virtual void bfmeV14YT(void);
	virtual void bfmeV15YT(void);
	virtual void bfmeV16YT(void);
	virtual void bfmeV17YT(void);
	virtual void bfmeV18YT(void);
	virtual void bfmeV19YT(void);
	virtual void bfmeV20YT(void);
	virtual void bfmeV21YT(void);
	virtual void bfmeV22YT(void);
	virtual void bfmeV23YT(void);
	virtual void bfmeV24YT(void);
	virtual void bfmeV25YT(void);
	virtual void bfmeV26YT(void);
	virtual void bfmeV27YT(void);
	virtual void bfmeV28YT(void);
	virtual void bfmeV29YT(void);
	virtual void bfmeV30YT(void);
	virtual void bfmeV31YT(void);
	virtual void bfmeV32YT(void);
	virtual void bfmeV33YT(void);
	virtual void bfmeV34YT(void);
	virtual void bfmeV35YT(void);
	virtual void bfmeV36YT(void);
	virtual void bfmeV37YT(void);
	virtual void bfmeV38YT(void);
	virtual void bfmeV39YT(void);
	virtual void bfmeV40YT(void);
	virtual void bfmeV41YT(void);
	virtual void bfmeV42YT(void);
	virtual void bfmeV43YT(void);
	virtual void bfmeV44YT(void);
	virtual void bfmeV45YT(void);
	virtual void bfmeV46YT(void);
	virtual void bfmeV47YT(void);
	virtual void bfmeV48YT(void);
	virtual void bfmeV49YT(void);
	virtual void bfmeV50YT(void);
	virtual void bfmeV51YT(void);
	virtual void bfmeV52YT(void);
	virtual void bfmeV53YT(void);
	virtual void bfmeV54YT(void);
	virtual void bfmeV55YT(void);
	virtual void bfmeV56YT(void);
	virtual void bfmeV57YT(void);
	virtual void bfmeV58YT(void);
	virtual void bfmeV59YT(void);
	virtual void bfmeV60YT(void);
	virtual void bfmeV61YT(void);
	virtual void bfmeV62YT(void);
	virtual void bfmeVisitYT(BfmeFilterFnYT filter, void *param, int mode);
};

class BfmeUnitYT
{
public:
	int m_bfmeSpareYT;
	BfmeThingYT *m_bfmeThingYT;
	unsigned char m_bfmeGapYT[0x1f4];
	BfmeSinkYT *m_bfmeSinkYT;
};

void __cdecl bfmeNotifyYT(BfmeUnitYT *unit, void *param)
{
	if (unit)
	{
		BfmeThingYT *thing = unit->m_bfmeThingYT;

		if (thing && thing->m_bfmeInnerYT)
			thing = thing->m_bfmeInnerYT->bfmeResolveYT();

		if (thing->m_bfmeFlagsYT & 0x1000)
		{
			BfmeSinkYT *sink = unit->m_bfmeSinkYT;

			if (sink)
			{
				sink->bfmeVisitYT(bfmeFilterYT, param, 1);
				sink->bfmeVisitYT(bfmeFilterYT, param, 0x10);
			}
		}
	}
}
