// ?bfmeStepJC@BfmeOwnerJC@@QAEXXZ (identity unknown)
// partial score=0.85 date=2026-09-06
// 56/66 at exact size and exact structure. Two residue clusters, both pure
// register allocation:
//   +0x14/+0x00 the two vftable loads use eax then edx in retail and edx then
//               eax here (a straight swap at both call sites);
//   +0x25       retail loads m_bfmeCurJC into eax and stores it to
//               m_bfmePrevJC AFTER materialising ecx=this; MSVC loads into ecx
//               and stores before.
// Tried: inline condition without the sub local (68B, worse), a named cur
// local, an if/else with the inverted guard, a named next local, and the
// flags /G7 (65B), /Ob1, /Oy-, /GX. All give the identical 7-line diff.
// Slot map recovered from the bytes: BfmeSubJC slot 8 (+0x20) returns char;
// BfmeThingJC slot 7 (+0x1c) is the tail call and slot 13 (+0x34) the action;
// BfmeOwnerJC slot 134 (+0x218) returns the next BfmeThingJC.
class BfmeSubJC
{
public:
	virtual void bfmeSlot00JCS(void);
	virtual void bfmeSlot01JCS(void);
	virtual void bfmeSlot02JCS(void);
	virtual void bfmeSlot03JCS(void);
	virtual void bfmeSlot04JCS(void);
	virtual void bfmeSlot05JCS(void);
	virtual void bfmeSlot06JCS(void);
	virtual void bfmeSlot07JCS(void);
	virtual char bfmeCheckJC(void);
};

class BfmeThingJC
{
public:
	virtual void bfmeSlot00JCT(void);
	virtual void bfmeSlot01JCT(void);
	virtual void bfmeSlot02JCT(void);
	virtual void bfmeSlot03JCT(void);
	virtual void bfmeSlot04JCT(void);
	virtual void bfmeSlot05JCT(void);
	virtual void bfmeSlot06JCT(void);
	virtual void bfmeTailJC(void);
	virtual void bfmeSlot08JCT(void);
	virtual void bfmeSlot09JCT(void);
	virtual void bfmeSlot10JCT(void);
	virtual void bfmeSlot11JCT(void);
	virtual void bfmeSlot12JCT(void);
	virtual void bfmeDoJC(void);

	unsigned char m_bfmeHeadJC[0x18];
	BfmeSubJC *m_bfmeSubJC;
};

class BfmeOwnerJC
{
public:
	virtual void bfmeSlot00JCO(void);
	virtual void bfmeSlot01JCO(void);
	virtual void bfmeSlot02JCO(void);
	virtual void bfmeSlot03JCO(void);
	virtual void bfmeSlot04JCO(void);
	virtual void bfmeSlot05JCO(void);
	virtual void bfmeSlot06JCO(void);
	virtual void bfmeSlot07JCO(void);
	virtual void bfmeSlot08JCO(void);
	virtual void bfmeSlot09JCO(void);
	virtual void bfmeSlot10JCO(void);
	virtual void bfmeSlot11JCO(void);
	virtual void bfmeSlot12JCO(void);
	virtual void bfmeSlot13JCO(void);
	virtual void bfmeSlot14JCO(void);
	virtual void bfmeSlot15JCO(void);
	virtual void bfmeSlot16JCO(void);
	virtual void bfmeSlot17JCO(void);
	virtual void bfmeSlot18JCO(void);
	virtual void bfmeSlot19JCO(void);
	virtual void bfmeSlot20JCO(void);
	virtual void bfmeSlot21JCO(void);
	virtual void bfmeSlot22JCO(void);
	virtual void bfmeSlot23JCO(void);
	virtual void bfmeSlot24JCO(void);
	virtual void bfmeSlot25JCO(void);
	virtual void bfmeSlot26JCO(void);
	virtual void bfmeSlot27JCO(void);
	virtual void bfmeSlot28JCO(void);
	virtual void bfmeSlot29JCO(void);
	virtual void bfmeSlot30JCO(void);
	virtual void bfmeSlot31JCO(void);
	virtual void bfmeSlot32JCO(void);
	virtual void bfmeSlot33JCO(void);
	virtual void bfmeSlot34JCO(void);
	virtual void bfmeSlot35JCO(void);
	virtual void bfmeSlot36JCO(void);
	virtual void bfmeSlot37JCO(void);
	virtual void bfmeSlot38JCO(void);
	virtual void bfmeSlot39JCO(void);
	virtual void bfmeSlot40JCO(void);
	virtual void bfmeSlot41JCO(void);
	virtual void bfmeSlot42JCO(void);
	virtual void bfmeSlot43JCO(void);
	virtual void bfmeSlot44JCO(void);
	virtual void bfmeSlot45JCO(void);
	virtual void bfmeSlot46JCO(void);
	virtual void bfmeSlot47JCO(void);
	virtual void bfmeSlot48JCO(void);
	virtual void bfmeSlot49JCO(void);
	virtual void bfmeSlot50JCO(void);
	virtual void bfmeSlot51JCO(void);
	virtual void bfmeSlot52JCO(void);
	virtual void bfmeSlot53JCO(void);
	virtual void bfmeSlot54JCO(void);
	virtual void bfmeSlot55JCO(void);
	virtual void bfmeSlot56JCO(void);
	virtual void bfmeSlot57JCO(void);
	virtual void bfmeSlot58JCO(void);
	virtual void bfmeSlot59JCO(void);
	virtual void bfmeSlot60JCO(void);
	virtual void bfmeSlot61JCO(void);
	virtual void bfmeSlot62JCO(void);
	virtual void bfmeSlot63JCO(void);
	virtual void bfmeSlot64JCO(void);
	virtual void bfmeSlot65JCO(void);
	virtual void bfmeSlot66JCO(void);
	virtual void bfmeSlot67JCO(void);
	virtual void bfmeSlot68JCO(void);
	virtual void bfmeSlot69JCO(void);
	virtual void bfmeSlot70JCO(void);
	virtual void bfmeSlot71JCO(void);
	virtual void bfmeSlot72JCO(void);
	virtual void bfmeSlot73JCO(void);
	virtual void bfmeSlot74JCO(void);
	virtual void bfmeSlot75JCO(void);
	virtual void bfmeSlot76JCO(void);
	virtual void bfmeSlot77JCO(void);
	virtual void bfmeSlot78JCO(void);
	virtual void bfmeSlot79JCO(void);
	virtual void bfmeSlot80JCO(void);
	virtual void bfmeSlot81JCO(void);
	virtual void bfmeSlot82JCO(void);
	virtual void bfmeSlot83JCO(void);
	virtual void bfmeSlot84JCO(void);
	virtual void bfmeSlot85JCO(void);
	virtual void bfmeSlot86JCO(void);
	virtual void bfmeSlot87JCO(void);
	virtual void bfmeSlot88JCO(void);
	virtual void bfmeSlot89JCO(void);
	virtual void bfmeSlot90JCO(void);
	virtual void bfmeSlot91JCO(void);
	virtual void bfmeSlot92JCO(void);
	virtual void bfmeSlot93JCO(void);
	virtual void bfmeSlot94JCO(void);
	virtual void bfmeSlot95JCO(void);
	virtual void bfmeSlot96JCO(void);
	virtual void bfmeSlot97JCO(void);
	virtual void bfmeSlot98JCO(void);
	virtual void bfmeSlot99JCO(void);
	virtual void bfmeSlot100JCO(void);
	virtual void bfmeSlot101JCO(void);
	virtual void bfmeSlot102JCO(void);
	virtual void bfmeSlot103JCO(void);
	virtual void bfmeSlot104JCO(void);
	virtual void bfmeSlot105JCO(void);
	virtual void bfmeSlot106JCO(void);
	virtual void bfmeSlot107JCO(void);
	virtual void bfmeSlot108JCO(void);
	virtual void bfmeSlot109JCO(void);
	virtual void bfmeSlot110JCO(void);
	virtual void bfmeSlot111JCO(void);
	virtual void bfmeSlot112JCO(void);
	virtual void bfmeSlot113JCO(void);
	virtual void bfmeSlot114JCO(void);
	virtual void bfmeSlot115JCO(void);
	virtual void bfmeSlot116JCO(void);
	virtual void bfmeSlot117JCO(void);
	virtual void bfmeSlot118JCO(void);
	virtual void bfmeSlot119JCO(void);
	virtual void bfmeSlot120JCO(void);
	virtual void bfmeSlot121JCO(void);
	virtual void bfmeSlot122JCO(void);
	virtual void bfmeSlot123JCO(void);
	virtual void bfmeSlot124JCO(void);
	virtual void bfmeSlot125JCO(void);
	virtual void bfmeSlot126JCO(void);
	virtual void bfmeSlot127JCO(void);
	virtual void bfmeSlot128JCO(void);
	virtual void bfmeSlot129JCO(void);
	virtual void bfmeSlot130JCO(void);
	virtual void bfmeSlot131JCO(void);
	virtual void bfmeSlot132JCO(void);
	virtual void bfmeSlot133JCO(void);
	virtual class BfmeThingJC *bfmeNextJC(void);

	void bfmeStepJC(void);

	unsigned char m_bfmeHeadJC[0x2c];
	BfmeThingJC *m_bfmeCurJC;
	unsigned char m_bfmeMidJC[4];
	BfmeThingJC *m_bfmePrevJC;
};

void BfmeOwnerJC::bfmeStepJC(void)
{
	if (m_bfmePrevJC)
		return;

	BfmeSubJC *sub = m_bfmeCurJC->m_bfmeSubJC;
	if (sub == 0 || sub->bfmeCheckJC())
		m_bfmeCurJC->bfmeDoJC();

	m_bfmePrevJC = m_bfmeCurJC;

	BfmeThingJC *next = bfmeNextJC();
	m_bfmeCurJC = next;
	next->bfmeTailJC();
}
