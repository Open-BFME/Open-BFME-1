// ?bfmeGoGX@BfmeThingGX@@QAEXXZ
// partial score=0.92 date=2026-09-04
// ?bfmeGoGX@BfmeThingGX@@QAEXXZ
// partial score=0.92 date=2026-09-03
// cl: /O2 /DNDEBUG /MD
// Advance: if the stashed next is empty, stop the current thing when its
// target is missing or says so, put current away, make the next, and start it.

class BfmeInnerGX
{
public:
	virtual void bfmeSpare000GZ(void) = 0;
	virtual void bfmeSpare001GZ(void) = 0;
	virtual void bfmeSpare002GZ(void) = 0;
	virtual void bfmeSpare003GZ(void) = 0;
	virtual void bfmeSpare004GZ(void) = 0;
	virtual void bfmeSpare005GZ(void) = 0;
	virtual void bfmeSpare006GZ(void) = 0;
	virtual void bfmeSpare007GZ(void) = 0;
	virtual bool bfmeAskGX(void) = 0;
};

class BfmeTargetGX
{
public:
	virtual void bfmeGoneGX(int how) = 0;
	virtual void bfmeSpare001GY(void) = 0;
	virtual void bfmeSpare002GY(void) = 0;
	virtual void bfmeSpare003GY(void) = 0;
	virtual void bfmeSpare004GY(void) = 0;
	virtual void bfmeSpare005GY(void) = 0;
	virtual void bfmeSpare006GY(void) = 0;
	virtual void bfmeStartGX(void) = 0;
	virtual void bfmeSpare008GY(void) = 0;
	virtual void bfmeSpare009GY(void) = 0;
	virtual void bfmeSpare010GY(void) = 0;
	virtual void bfmeSpare011GY(void) = 0;
	virtual void bfmeSpare012GY(void) = 0;
	virtual void bfmeStopGX(void) = 0;

	unsigned char m_bfmeHead[0x18];	// 0x04
	BfmeInnerGX *m_bfmeInner;	// 0x1C
};

class BfmeMakerGX
{
public:
	virtual void bfmeSpare000GW(void) = 0;
	virtual void bfmeSpare001GW(void) = 0;
	virtual void bfmeSpare002GW(void) = 0;
	virtual void bfmeSpare003GW(void) = 0;
	virtual void bfmeSpare004GW(void) = 0;
	virtual void bfmeSpare005GW(void) = 0;
	virtual void bfmeSpare006GW(void) = 0;
	virtual void bfmeSpare007GW(void) = 0;
	virtual void bfmeSpare008GW(void) = 0;
	virtual void bfmeSpare009GW(void) = 0;
	virtual void bfmeSpare010GW(void) = 0;
	virtual void bfmeSpare011GW(void) = 0;
	virtual void bfmeSpare012GW(void) = 0;
	virtual void bfmeSpare013GW(void) = 0;
	virtual void bfmeSpare014GW(void) = 0;
	virtual void bfmeSpare015GW(void) = 0;
	virtual void bfmeSpare016GW(void) = 0;
	virtual void bfmeSpare017GW(void) = 0;
	virtual void bfmeSpare018GW(void) = 0;
	virtual void bfmeSpare019GW(void) = 0;
	virtual void bfmeSpare020GW(void) = 0;
	virtual void bfmeSpare021GW(void) = 0;
	virtual void bfmeSpare022GW(void) = 0;
	virtual void bfmeSpare023GW(void) = 0;
	virtual void bfmeSpare024GW(void) = 0;
	virtual void bfmeSpare025GW(void) = 0;
	virtual void bfmeSpare026GW(void) = 0;
	virtual void bfmeSpare027GW(void) = 0;
	virtual void bfmeSpare028GW(void) = 0;
	virtual void bfmeSpare029GW(void) = 0;
	virtual void bfmeSpare030GW(void) = 0;
	virtual void bfmeSpare031GW(void) = 0;
	virtual void bfmeSpare032GW(void) = 0;
	virtual void bfmeSpare033GW(void) = 0;
	virtual void bfmeSpare034GW(void) = 0;
	virtual void bfmeSpare035GW(void) = 0;
	virtual void bfmeSpare036GW(void) = 0;
	virtual void bfmeSpare037GW(void) = 0;
	virtual void bfmeSpare038GW(void) = 0;
	virtual void bfmeSpare039GW(void) = 0;
	virtual void bfmeSpare040GW(void) = 0;
	virtual void bfmeSpare041GW(void) = 0;
	virtual void bfmeSpare042GW(void) = 0;
	virtual void bfmeSpare043GW(void) = 0;
	virtual void bfmeSpare044GW(void) = 0;
	virtual void bfmeSpare045GW(void) = 0;
	virtual void bfmeSpare046GW(void) = 0;
	virtual void bfmeSpare047GW(void) = 0;
	virtual void bfmeSpare048GW(void) = 0;
	virtual void bfmeSpare049GW(void) = 0;
	virtual void bfmeSpare050GW(void) = 0;
	virtual void bfmeSpare051GW(void) = 0;
	virtual void bfmeSpare052GW(void) = 0;
	virtual void bfmeSpare053GW(void) = 0;
	virtual void bfmeSpare054GW(void) = 0;
	virtual void bfmeSpare055GW(void) = 0;
	virtual void bfmeSpare056GW(void) = 0;
	virtual void bfmeSpare057GW(void) = 0;
	virtual void bfmeSpare058GW(void) = 0;
	virtual void bfmeSpare059GW(void) = 0;
	virtual void bfmeSpare060GW(void) = 0;
	virtual void bfmeSpare061GW(void) = 0;
	virtual void bfmeSpare062GW(void) = 0;
	virtual void bfmeSpare063GW(void) = 0;
	virtual void bfmeSpare064GW(void) = 0;
	virtual void bfmeSpare065GW(void) = 0;
	virtual void bfmeSpare066GW(void) = 0;
	virtual void bfmeSpare067GW(void) = 0;
	virtual void bfmeSpare068GW(void) = 0;
	virtual void bfmeSpare069GW(void) = 0;
	virtual void bfmeSpare070GW(void) = 0;
	virtual void bfmeSpare071GW(void) = 0;
	virtual void bfmeSpare072GW(void) = 0;
	virtual void bfmeSpare073GW(void) = 0;
	virtual void bfmeSpare074GW(void) = 0;
	virtual void bfmeSpare075GW(void) = 0;
	virtual void bfmeSpare076GW(void) = 0;
	virtual void bfmeSpare077GW(void) = 0;
	virtual void bfmeSpare078GW(void) = 0;
	virtual void bfmeSpare079GW(void) = 0;
	virtual void bfmeSpare080GW(void) = 0;
	virtual void bfmeSpare081GW(void) = 0;
	virtual void bfmeSpare082GW(void) = 0;
	virtual void bfmeSpare083GW(void) = 0;
	virtual void bfmeSpare084GW(void) = 0;
	virtual void bfmeSpare085GW(void) = 0;
	virtual void bfmeSpare086GW(void) = 0;
	virtual void bfmeSpare087GW(void) = 0;
	virtual void bfmeSpare088GW(void) = 0;
	virtual void bfmeSpare089GW(void) = 0;
	virtual void bfmeSpare090GW(void) = 0;
	virtual void bfmeSpare091GW(void) = 0;
	virtual void bfmeSpare092GW(void) = 0;
	virtual void bfmeSpare093GW(void) = 0;
	virtual void bfmeSpare094GW(void) = 0;
	virtual void bfmeSpare095GW(void) = 0;
	virtual void bfmeSpare096GW(void) = 0;
	virtual void bfmeSpare097GW(void) = 0;
	virtual void bfmeSpare098GW(void) = 0;
	virtual void bfmeSpare099GW(void) = 0;
	virtual void bfmeSpare100GW(void) = 0;
	virtual void bfmeSpare101GW(void) = 0;
	virtual void bfmeSpare102GW(void) = 0;
	virtual void bfmeSpare103GW(void) = 0;
	virtual void bfmeSpare104GW(void) = 0;
	virtual void bfmeSpare105GW(void) = 0;
	virtual void bfmeSpare106GW(void) = 0;
	virtual void bfmeSpare107GW(void) = 0;
	virtual void bfmeSpare108GW(void) = 0;
	virtual void bfmeSpare109GW(void) = 0;
	virtual void bfmeSpare110GW(void) = 0;
	virtual void bfmeSpare111GW(void) = 0;
	virtual void bfmeSpare112GW(void) = 0;
	virtual void bfmeSpare113GW(void) = 0;
	virtual void bfmeSpare114GW(void) = 0;
	virtual void bfmeSpare115GW(void) = 0;
	virtual void bfmeSpare116GW(void) = 0;
	virtual void bfmeSpare117GW(void) = 0;
	virtual void bfmeSpare118GW(void) = 0;
	virtual void bfmeSpare119GW(void) = 0;
	virtual void bfmeSpare120GW(void) = 0;
	virtual void bfmeSpare121GW(void) = 0;
	virtual void bfmeSpare122GW(void) = 0;
	virtual void bfmeSpare123GW(void) = 0;
	virtual void bfmeSpare124GW(void) = 0;
	virtual void bfmeSpare125GW(void) = 0;
	virtual void bfmeSpare126GW(void) = 0;
	virtual void bfmeSpare127GW(void) = 0;
	virtual void bfmeSpare128GW(void) = 0;
	virtual void bfmeSpare129GW(void) = 0;
	virtual void bfmeSpare130GW(void) = 0;
	virtual void bfmeSpare131GW(void) = 0;
	virtual void bfmeSpare132GW(void) = 0;
	virtual void bfmeSpare133GW(void) = 0;
	virtual BfmeTargetGX *bfmeMakeGX(void) = 0;
};

class BfmeThingGX
{
public:
	void bfmeGoGX(void);

	BfmeMakerGX *asMakerGX(void) { return (BfmeMakerGX *)this; }

private:
	unsigned char m_bfmeHead[0x30];	// 0x00
	BfmeTargetGX *m_bfmeCurrent;	// 0x30
	unsigned char m_bfmeGap[4];	// 0x34
	BfmeTargetGX *m_bfmeNext;	// 0x38
};

void BfmeThingGX::bfmeGoGX(void)
{
	if (m_bfmeNext != 0)
		return;

	BfmeInnerGX *inner = m_bfmeCurrent->m_bfmeInner;

	if (inner == 0 || inner->bfmeAskGX() != 0)
		m_bfmeCurrent->bfmeStopGX();

	m_bfmeNext = m_bfmeCurrent;
	m_bfmeCurrent = asMakerGX()->bfmeMakeGX();
	m_bfmeCurrent->bfmeStartGX();
}
