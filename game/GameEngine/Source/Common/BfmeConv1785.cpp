class BfmeThingNW;

class BfmeInnerNW
{
public:
	BfmeThingNW *bfmeResolveNW(void);
};

class BfmeThingNW
{
public:
	int m_bfmeSpareNW;
	BfmeInnerNW *m_bfmeInnerNW;
	unsigned char m_bfmeGapNW[0xc4];
	int m_bfmeFlagsNW;
};

class BfmeCheckerNW
{
public:
	char bfmeBusyNW(void);
};

class BfmeUnitNW
{
public:
	int m_bfmeSpareNW;
	BfmeThingNW *m_bfmeThingNW;
	unsigned char m_bfmeGapNW[0x88];
	int m_bfmeStateNW;
	unsigned char m_bfmeTailNW[0x174];
	BfmeCheckerNW *m_bfmeCheckerNW;
};

char __cdecl bfmeReadyNW(BfmeUnitNW *unit)
{
	if (unit->m_bfmeCheckerNW && unit->m_bfmeCheckerNW->bfmeBusyNW())
		return 0;

	BfmeThingNW *thing = unit->m_bfmeThingNW;

	if (thing && thing->m_bfmeInnerNW)
		thing = thing->m_bfmeInnerNW->bfmeResolveNW();

	if (thing->m_bfmeFlagsNW & 0x200000)
		return 0;

	int state = unit->m_bfmeStateNW;

	if (state & 0x8000)
	{
		if ((state & 0x20000) == 0)
			return 0;
	}

	return 1;
}
