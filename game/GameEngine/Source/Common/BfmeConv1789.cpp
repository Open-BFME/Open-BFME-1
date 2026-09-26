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
	BfmeInnerLU *m_bfmeInnerLU;
};

class BfmeOwnerLU
{
public:
	BfmeThingLU *bfmeThingLU(void)
	{
		BfmeThingLU *thing = m_bfmeSlotLU;

		if (thing && thing->m_bfmeInnerLU)
			thing = thing->m_bfmeInnerLU->bfmeResolveLU();

		return thing;
	}

	BfmeThingLU *bfmeTopLU(void);

	unsigned char m_bfmeHeadLU[0x1c];
	BfmeThingLU *m_bfmeSlotLU;
};

BfmeThingLU *BfmeOwnerLU::bfmeTopLU(void)
{
	if (!bfmeThingLU())
		return 0;

	BfmeThingLU *thing = bfmeThingLU();

	if (thing->m_bfmeInnerLU)
		return thing->m_bfmeInnerLU->bfmeResolveLU();

	return thing;
}
