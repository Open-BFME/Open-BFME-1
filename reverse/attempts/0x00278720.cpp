// ?bfmeCheckBU@BfmeOwnBU@@QAEDXZ (identity unknown)
// partial score=0.95 date=2026-09-06
// 74/78 at exact size. Everything is settled: the 0x344 bit guard, the
// 0x20 flag plus two-link chain ending in virtual slot 96, and the tail jmp
// through virtual slot 7. Two lessons here, both needed:
//   - the middle chain DOES need locals (respelling it makes MSVC reload the
//     whole chain for the receiver, 97 bytes), unlike 0x00904BA0/0x0090E2A0;
//   - the last guard must be written positively (`if (ready) return
//     ready->slot7(); return 1;`) so the tail jmp lands inline and the
//     mov al,1 block goes last.
// Residue: retail loads the tail receiver's vftable into eax (reusing the
// dead register), MSVC into edx. Tried a local for the holder and the fully
// respelled form.
class BfmeDBU
{
public:
	virtual void bfmeDSlot00BU(void);
	virtual void bfmeDSlot01BU(void);
	virtual void bfmeDSlot02BU(void);
	virtual void bfmeDSlot03BU(void);
	virtual void bfmeDSlot04BU(void);
	virtual void bfmeDSlot05BU(void);
	virtual void bfmeDSlot06BU(void);
	virtual void bfmeDSlot07BU(void);
	virtual void bfmeDSlot08BU(void);
	virtual void bfmeDSlot09BU(void);
	virtual void bfmeDSlot10BU(void);
	virtual void bfmeDSlot11BU(void);
	virtual void bfmeDSlot12BU(void);
	virtual void bfmeDSlot13BU(void);
	virtual void bfmeDSlot14BU(void);
	virtual void bfmeDSlot15BU(void);
	virtual void bfmeDSlot16BU(void);
	virtual void bfmeDSlot17BU(void);
	virtual void bfmeDSlot18BU(void);
	virtual void bfmeDSlot19BU(void);
	virtual void bfmeDSlot20BU(void);
	virtual void bfmeDSlot21BU(void);
	virtual void bfmeDSlot22BU(void);
	virtual void bfmeDSlot23BU(void);
	virtual void bfmeDSlot24BU(void);
	virtual void bfmeDSlot25BU(void);
	virtual void bfmeDSlot26BU(void);
	virtual void bfmeDSlot27BU(void);
	virtual void bfmeDSlot28BU(void);
	virtual void bfmeDSlot29BU(void);
	virtual void bfmeDSlot30BU(void);
	virtual void bfmeDSlot31BU(void);
	virtual void bfmeDSlot32BU(void);
	virtual void bfmeDSlot33BU(void);
	virtual void bfmeDSlot34BU(void);
	virtual void bfmeDSlot35BU(void);
	virtual void bfmeDSlot36BU(void);
	virtual void bfmeDSlot37BU(void);
	virtual void bfmeDSlot38BU(void);
	virtual void bfmeDSlot39BU(void);
	virtual void bfmeDSlot40BU(void);
	virtual void bfmeDSlot41BU(void);
	virtual void bfmeDSlot42BU(void);
	virtual void bfmeDSlot43BU(void);
	virtual void bfmeDSlot44BU(void);
	virtual void bfmeDSlot45BU(void);
	virtual void bfmeDSlot46BU(void);
	virtual void bfmeDSlot47BU(void);
	virtual void bfmeDSlot48BU(void);
	virtual void bfmeDSlot49BU(void);
	virtual void bfmeDSlot50BU(void);
	virtual void bfmeDSlot51BU(void);
	virtual void bfmeDSlot52BU(void);
	virtual void bfmeDSlot53BU(void);
	virtual void bfmeDSlot54BU(void);
	virtual void bfmeDSlot55BU(void);
	virtual void bfmeDSlot56BU(void);
	virtual void bfmeDSlot57BU(void);
	virtual void bfmeDSlot58BU(void);
	virtual void bfmeDSlot59BU(void);
	virtual void bfmeDSlot60BU(void);
	virtual void bfmeDSlot61BU(void);
	virtual void bfmeDSlot62BU(void);
	virtual void bfmeDSlot63BU(void);
	virtual void bfmeDSlot64BU(void);
	virtual void bfmeDSlot65BU(void);
	virtual void bfmeDSlot66BU(void);
	virtual void bfmeDSlot67BU(void);
	virtual void bfmeDSlot68BU(void);
	virtual void bfmeDSlot69BU(void);
	virtual void bfmeDSlot70BU(void);
	virtual void bfmeDSlot71BU(void);
	virtual void bfmeDSlot72BU(void);
	virtual void bfmeDSlot73BU(void);
	virtual void bfmeDSlot74BU(void);
	virtual void bfmeDSlot75BU(void);
	virtual void bfmeDSlot76BU(void);
	virtual void bfmeDSlot77BU(void);
	virtual void bfmeDSlot78BU(void);
	virtual void bfmeDSlot79BU(void);
	virtual void bfmeDSlot80BU(void);
	virtual void bfmeDSlot81BU(void);
	virtual void bfmeDSlot82BU(void);
	virtual void bfmeDSlot83BU(void);
	virtual void bfmeDSlot84BU(void);
	virtual void bfmeDSlot85BU(void);
	virtual void bfmeDSlot86BU(void);
	virtual void bfmeDSlot87BU(void);
	virtual void bfmeDSlot88BU(void);
	virtual void bfmeDSlot89BU(void);
	virtual void bfmeDSlot90BU(void);
	virtual void bfmeDSlot91BU(void);
	virtual void bfmeDSlot92BU(void);
	virtual void bfmeDSlot93BU(void);
	virtual void bfmeDSlot94BU(void);
	virtual void bfmeDSlot95BU(void);
	virtual char bfmeBusyBU(void);
};

class BfmeBBU
{
public:
	unsigned char m_bfmeHeadBU[0x204];
	BfmeDBU *m_bfmeDBU;
};

class BfmeABU
{
public:
	unsigned char m_bfmeHeadBU[0x94];
	unsigned char m_bfmeFlagsBU;
	unsigned char m_bfmeMidBU[0x17f];
	BfmeBBU *m_bfmeBBU;
	unsigned char m_bfmeMid2BU[0x12c];
	unsigned char m_bfmeStateBU;
};

class BfmeEBU
{
public:
	virtual void bfmeESlot00BU(void);
	virtual void bfmeESlot01BU(void);
	virtual void bfmeESlot02BU(void);
	virtual void bfmeESlot03BU(void);
	virtual void bfmeESlot04BU(void);
	virtual void bfmeESlot05BU(void);
	virtual void bfmeESlot06BU(void);
	virtual char bfmeReadyBU(void);
};

class BfmeFBU
{
public:
	unsigned char m_bfmeHeadBU[0x1c];
	BfmeEBU *m_bfmeEBU;
};

class BfmeOwnBU
{
public:
	char bfmeCheckBU(void);

	unsigned char m_bfmeHeadBU[8];
	BfmeABU *m_bfmeABU;
	unsigned char m_bfmeMidBU[0x24];
	BfmeFBU *m_bfmeFBU;
};

char BfmeOwnBU::bfmeCheckBU(void)
{
	BfmeABU *owner = m_bfmeABU;

	if (owner->m_bfmeStateBU & 1)
		return 1;

	if ((owner->m_bfmeFlagsBU & 0x20) != 0)
	{
		BfmeBBU *link = owner->m_bfmeBBU;

		if (link != 0)
		{
			BfmeDBU *target = link->m_bfmeDBU;

			if (target != 0 && target->bfmeBusyBU())
				return 1;
		}
	}

	BfmeEBU *ready = m_bfmeFBU->m_bfmeEBU;

	if (ready != 0)
		return ready->bfmeReadyBU();

	return 1;
}
