// Callees (tools/callees.py 0x17D280 80): ILT 0x6EEC -> 0x0029A7A0
// Gen_0029A7A0::bfmeFlagged, ILT 0x22BB -> 0x00087A80 Overridable::getFinalOverride.
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class Gen_0029A7A0
{
public:
	bool bfmeFlagged(void) const;
};

class BfmeThingNW
{
public:
	int m_bfmeSpareNW;
	Overridable *m_bfmeInnerNW;
	unsigned char m_bfmeGapNW[0xc4];
	int m_bfmeFlagsNW;
};

class BfmeUnitNW
{
public:
	int m_bfmeSpareNW;
	BfmeThingNW *m_bfmeThingNW;
	unsigned char m_bfmeGapNW[0x88];
	int m_bfmeStateNW;
	unsigned char m_bfmeTailNW[0x174];
	Gen_0029A7A0 *m_bfmeCheckerNW;
};

char __cdecl bfmeReadyNW(BfmeUnitNW *unit)
{
	if (unit->m_bfmeCheckerNW && unit->m_bfmeCheckerNW->bfmeFlagged())
		return 0;

	BfmeThingNW *thing = unit->m_bfmeThingNW;

	if (thing && thing->m_bfmeInnerNW)
		thing = (BfmeThingNW *)thing->m_bfmeInnerNW->getFinalOverride();

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
