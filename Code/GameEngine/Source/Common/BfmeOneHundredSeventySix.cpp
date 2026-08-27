// The same question as its neighbour, asked of the next method along.

class BfmeTargetBU
{
public:
	virtual void bfmeSpare000BU(void) = 0;
	virtual void bfmeSpare001BU(void) = 0;
	virtual void bfmeSpare002BU(void) = 0;
	virtual void bfmeSpare003BU(void) = 0;
	virtual void bfmeSpare004BU(void) = 0;
	virtual void bfmeSpare005BU(void) = 0;
	virtual void bfmeSpare006BU(void) = 0;
	virtual void bfmeSpare007BU(void) = 0;
	virtual void bfmeSpare008BU(void) = 0;
	virtual void bfmeSpare009BU(void) = 0;
	virtual void bfmeSpare010BU(void) = 0;
	virtual void bfmeSpare011BU(void) = 0;
	virtual void bfmeSpare012BU(void) = 0;
	virtual void bfmeSpare013BU(void) = 0;
	virtual void bfmeSpare014BU(void) = 0;
	virtual void bfmeSpare015BU(void) = 0;
	virtual void bfmeSpare016BU(void) = 0;
	virtual void bfmeSpare017BU(void) = 0;
	virtual void bfmeSpare018BU(void) = 0;
	virtual void bfmeSpare019BU(void) = 0;
	virtual void bfmeSpare020BU(void) = 0;
	virtual void bfmeSpare021BU(void) = 0;
	virtual void bfmeSpare022BU(void) = 0;
	virtual void bfmeSpare023BU(void) = 0;
	virtual void bfmeSpare024BU(void) = 0;
	virtual void bfmeSpare025BU(void) = 0;
	virtual void bfmeSpare026BU(void) = 0;
	virtual void bfmeSpare027BU(void) = 0;
	virtual void bfmeSpare028BU(void) = 0;
	virtual void bfmeSpare029BU(void) = 0;
	virtual void bfmeSpare030BU(void) = 0;
	virtual void bfmeSpare031BU(void) = 0;
	virtual void bfmeSpare032BU(void) = 0;
	virtual void bfmeSpare033BU(void) = 0;
	virtual void bfmeSpare034BU(void) = 0;
	virtual void bfmeSpare035BU(void) = 0;
	virtual void bfmeSpare036BU(void) = 0;
	virtual void bfmeSpare037BU(void) = 0;
	virtual void bfmeSpare038BU(void) = 0;
	virtual void bfmeSpare039BU(void) = 0;
	virtual void bfmeSpare040BU(void) = 0;
	virtual void bfmeSpare041BU(void) = 0;
	virtual void bfmeSpare042BU(void) = 0;
	virtual void bfmeSpare043BU(void) = 0;
	virtual void bfmeSpare044BU(void) = 0;
	virtual void bfmeSpare045BU(void) = 0;
	virtual void bfmeSpare046BU(void) = 0;
	virtual void bfmeSpare047BU(void) = 0;
	virtual void bfmeSpare048BU(void) = 0;
	virtual void bfmeSpare049BU(void) = 0;
	virtual void bfmeSpare050BU(void) = 0;
	virtual void bfmeSpare051BU(void) = 0;
	virtual void bfmeSpare052BU(void) = 0;
	virtual void bfmeSpare053BU(void) = 0;
	virtual void bfmeSpare054BU(void) = 0;
	virtual void bfmeSpare055BU(void) = 0;
	virtual void bfmeSpare056BU(void) = 0;
	virtual void bfmeSpare057BU(void) = 0;
	virtual void bfmeSpare058BU(void) = 0;
	virtual void bfmeSpare059BU(void) = 0;
	virtual void bfmeSpare060BU(void) = 0;
	virtual void bfmeSpare061BU(void) = 0;
	virtual void bfmeSpare062BU(void) = 0;
	virtual void bfmeSpare063BU(void) = 0;
	virtual void bfmeSpare064BU(void) = 0;
	virtual void bfmeSpare065BU(void) = 0;
	virtual void bfmeSpare066BU(void) = 0;
	virtual void bfmeSpare067BU(void) = 0;
	virtual void bfmeSpare068BU(void) = 0;
	virtual void bfmeSpare069BU(void) = 0;
	virtual void bfmeSpare070BU(void) = 0;
	virtual void bfmeSpare071BU(void) = 0;
	virtual void bfmeSpare072BU(void) = 0;
	virtual void bfmeSpare073BU(void) = 0;
	virtual void bfmeSpare074BU(void) = 0;
	virtual void bfmeSpare075BU(void) = 0;
	virtual void bfmeSpare076BU(void) = 0;
	virtual void bfmeSpare077BU(void) = 0;
	virtual void bfmeSpare078BU(void) = 0;
	virtual void bfmeSpare079BU(void) = 0;
	virtual void bfmeSpare080BU(void) = 0;
	virtual void bfmeSpare081BU(void) = 0;
	virtual void bfmeSpare082BU(void) = 0;
	virtual void bfmeSpare083BU(void) = 0;
	virtual void bfmeSpare084BU(void) = 0;
	virtual void bfmeSpare085BU(void) = 0;
	virtual void bfmeSpare086BU(void) = 0;
	virtual void bfmeSpare087BU(void) = 0;
	virtual void bfmeSpare088BU(void) = 0;
	virtual void bfmeSpare089BU(void) = 0;
	virtual void bfmeSpare090BU(void) = 0;
	virtual void bfmeSpare091BU(void) = 0;
	virtual void bfmeSpare092BU(void) = 0;
	virtual void bfmeSpare093BU(void) = 0;
	virtual void bfmeSpare094BU(void) = 0;
	virtual void bfmeSpare095BU(void) = 0;
	virtual void bfmeSpare096BU(void) = 0;
	virtual void bfmeSpare097BU(void) = 0;
	virtual void bfmeSpare098BU(void) = 0;
	virtual void bfmeSpare099BU(void) = 0;
	virtual void bfmeSpare100BU(void) = 0;
	virtual unsigned char bfmeDoBU(void) = 0;
};

struct BfmeOwnerBU
{
	unsigned char m_bfmeHead[0x204];	// 0x000
	BfmeTargetBU *m_bfmeTarget;		// 0x204
};

class BfmeSubBU
{
public:
	unsigned char bfmeAskBU(void) const;

	unsigned char m_bfmeHead[4];		// 0x0
};

struct BfmeHostBU
{
	BfmeOwnerBU *m_bfmeOwner;		// 0x000
	unsigned char m_bfmeGap[0xd8];		// 0x004
	BfmeSubBU m_bfmeSub;			// 0x0dc
};

unsigned char BfmeSubBU::bfmeAskBU(void) const
{
	const BfmeHostBU *host = (const BfmeHostBU *)((const char *)this - 0xdc);
	BfmeTargetBU *target = host->m_bfmeOwner->m_bfmeTarget;

	if (target == 0)
		return 0;

	return target->bfmeDoBU();
}

