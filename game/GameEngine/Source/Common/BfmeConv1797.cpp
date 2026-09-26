class BfmeThingLW;

class BfmeInnerLW
{
public:
	BfmeThingLW *bfmeResolveLW(void);
};

class BfmeThingLW
{
public:
	int m_bfmeSpareLW;
	BfmeInnerLW *m_bfmeInnerLW;
	unsigned char m_bfmeGapLW[0xc0];
	int m_bfmeFlagsLW;
};

class BfmeUnitLW
{
public:
	int m_bfmeSpareLW;
	BfmeThingLW *m_bfmeThingLW;
};

class BfmeHolderLW
{
public:
	unsigned char m_bfmeHeadLW[0xfc];
	BfmeUnitLW *m_bfmeUnitLW;
};

class BfmeNodeLW
{
public:
	BfmeNodeLW *m_bfmeNextLW;
	int m_bfmeSpareLW;
	BfmeHolderLW *m_bfmeHolderLW;
};

class BfmeListLW
{
public:
	BfmeNodeLW *m_bfmeSentinelLW;
};

class InGameUI
{
public:
	virtual void bfmeV0LW(void);
	virtual void bfmeV1LW(void);
	virtual void bfmeV2LW(void);
	virtual void bfmeV3LW(void);
	virtual void bfmeV4LW(void);
	virtual void bfmeV5LW(void);
	virtual void bfmeV6LW(void);
	virtual void bfmeV7LW(void);
	virtual void bfmeV8LW(void);
	virtual void bfmeV9LW(void);
	virtual void bfmeV10LW(void);
	virtual void bfmeV11LW(void);
	virtual void bfmeV12LW(void);
	virtual void bfmeV13LW(void);
	virtual void bfmeV14LW(void);
	virtual void bfmeV15LW(void);
	virtual void bfmeV16LW(void);
	virtual void bfmeV17LW(void);
	virtual void bfmeV18LW(void);
	virtual void bfmeV19LW(void);
	virtual void bfmeV20LW(void);
	virtual void bfmeV21LW(void);
	virtual void bfmeV22LW(void);
	virtual void bfmeV23LW(void);
	virtual void bfmeV24LW(void);
	virtual void bfmeV25LW(void);
	virtual void bfmeV26LW(void);
	virtual void bfmeV27LW(void);
	virtual void bfmeV28LW(void);
	virtual void bfmeV29LW(void);
	virtual void bfmeV30LW(void);
	virtual void bfmeV31LW(void);
	virtual void bfmeV32LW(void);
	virtual void bfmeV33LW(void);
	virtual void bfmeV34LW(void);
	virtual void bfmeV35LW(void);
	virtual void bfmeV36LW(void);
	virtual void bfmeV37LW(void);
	virtual void bfmeV38LW(void);
	virtual void bfmeV39LW(void);
	virtual void bfmeV40LW(void);
	virtual void bfmeV41LW(void);
	virtual void bfmeV42LW(void);
	virtual void bfmeV43LW(void);
	virtual void bfmeV44LW(void);
	virtual void bfmeV45LW(void);
	virtual void bfmeV46LW(void);
	virtual void bfmeV47LW(void);
	virtual void bfmeV48LW(void);
	virtual void bfmeV49LW(void);
	virtual void bfmeV50LW(void);
	virtual void bfmeV51LW(void);
	virtual void bfmeV52LW(void);
	virtual void bfmeV53LW(void);
	virtual void bfmeV54LW(void);
	virtual void bfmeV55LW(void);
	virtual void bfmeV56LW(void);
	virtual void bfmeV57LW(void);
	virtual void bfmeV58LW(void);
	virtual void bfmeV59LW(void);
	virtual void bfmeV60LW(void);
	virtual void bfmeV61LW(void);
	virtual void bfmeV62LW(void);
	virtual BfmeListLW *bfmeGetListLW(void);
};

extern InGameUI *TheInGameUI;

class BfmeOwnerLW
{
public:
	char bfmeAnyLW(void);
	char bfmeReadyLW(void);
};

char BfmeOwnerLW::bfmeAnyLW(void)
{
	if (this == 0)
		return 0;

	if (!bfmeReadyLW())
		return 0;

	BfmeNodeLW *sentinel = TheInGameUI->bfmeGetListLW()->m_bfmeSentinelLW;
	BfmeNodeLW *node;

	for (node = sentinel->m_bfmeNextLW; node != sentinel; node = node->m_bfmeNextLW)
	{
		BfmeHolderLW *holder = node->m_bfmeHolderLW;

		if (holder)
		{
			BfmeUnitLW *unit = holder->m_bfmeUnitLW;

			if (unit)
			{
				BfmeThingLW *thing = unit->m_bfmeThingLW;

				if (thing && thing->m_bfmeInnerLW)
					thing = thing->m_bfmeInnerLW->bfmeResolveLW();

				if (thing->m_bfmeFlagsLW & 0x80000)
					return 1;
			}
		}
	}

	return 0;
}
