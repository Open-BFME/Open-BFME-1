class BfmeThingLU;

class BfmeInnerLU
{
public:
	BfmeThingLU *bfmeResolveLU(void);
};

class BfmeThingLU
{
public:
	int m_bfmeSpareLU;
	BfmeInnerLU *m_nextOverride;
};

class BfmeOwnerLU
{
public:
	BfmeThingLU *bfmeThingLU(void)
	{
		BfmeThingLU *thing = m_bfmeSlotLU;

		if (thing && thing->m_nextOverride)
			thing = thing->m_nextOverride->bfmeResolveLU();

		return thing;
	}

	BfmeThingLU *getThingTemplate(void);

	unsigned char m_bfmeHeadLU[0x1c];
	BfmeThingLU *m_bfmeSlotLU;
};

BfmeThingLU *BfmeOwnerLU::getThingTemplate(void)
{
	if (!bfmeThingLU())
		return 0;

	BfmeThingLU *thing = bfmeThingLU();

	if (thing->m_nextOverride)
		return thing->m_nextOverride->bfmeResolveLU();

	return thing;
}
