class ThingTemplate;

// The chain walk retail calls through ILT 0x000022BB is
// Overridable::getFinalOverride, the out-of-line copy of the recursive inline
// accessor in Overridable.h; its matched 26-byte body is at 0x00087A80
// (functions.csv row, source INIWater.cpp) and every TU that includes the real
// header emits the same COMDAT, so this reference resolves.
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
};

class ThingTemplate
{
public:
	int m_bfmeSpareLU;
	Overridable *m_nextOverride;
};

class BfmeOwnerLU
{
public:
	ThingTemplate *bfmeThingLU(void)
	{
		ThingTemplate *thing = m_thingTemplate;

		if (thing && thing->m_nextOverride)
			thing = (ThingTemplate *)thing->m_nextOverride->getFinalOverride();

		return thing;
	}

	ThingTemplate *getThingTemplate(void);

	unsigned char m_bfmeHeadLU[0x1c];
	ThingTemplate *m_thingTemplate;
};

ThingTemplate *BfmeOwnerLU::getThingTemplate(void)
{
	if (!bfmeThingLU())
		return 0;

	ThingTemplate *thing = bfmeThingLU();

	if (thing->m_nextOverride)
		return (ThingTemplate *)thing->m_nextOverride->getFinalOverride();

	return thing;
}
