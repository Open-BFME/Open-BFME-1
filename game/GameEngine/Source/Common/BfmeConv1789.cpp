class ThingTemplate;

class Overridable
{
public:
	ThingTemplate *bfmeResolveLU(void);
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
		ThingTemplate *thing = m_bfmeSlotLU;

		if (thing && thing->m_nextOverride)
			thing = thing->m_nextOverride->bfmeResolveLU();

		return thing;
	}

	ThingTemplate *getThingTemplate(void);

	unsigned char m_bfmeHeadLU[0x1c];
	ThingTemplate *m_bfmeSlotLU;
};

ThingTemplate *BfmeOwnerLU::getThingTemplate(void)
{
	if (!bfmeThingLU())
		return 0;

	ThingTemplate *thing = bfmeThingLU();

	if (thing->m_nextOverride)
		return thing->m_nextOverride->bfmeResolveLU();

	return thing;
}
