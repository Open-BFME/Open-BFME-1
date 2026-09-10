// ?drop@Rva002AFFA0Owner@@QAEXPAX@Z
// Secondary base at this-0x20: ask the gate about the owner's unit, notify the
// unit's hook, kill the unit and run the finish routine.

class BfmeHookXG
{
public:
	void bfmeNoteXG();
};

class BfmeUnitXG
{
public:
	unsigned char m_bfmeHeadXG[0x204];
	BfmeHookXG *m_bfmeHookXG;
};

struct BfmeSubXG
{
	bool bfmeTestXG(BfmeUnitXG *unit, void *arg);
};

class Rva002AFFA0Holder
{
public:
	void *m_bfmeFrontXG[2];
	BfmeSubXG m_bfmeSubXG;
};

class BfmeLogicXG
{
public:
	void bfmeKillXG(BfmeUnitXG *unit, int reason, int flag);
};

extern BfmeLogicXG *TheBfmeLogicXG;

class BfmeOuterXG
{
public:
	void bfmeFinishXG(void *arg);

	unsigned char m_bfmeStartXG[4];
	Rva002AFFA0Holder *m_bfmeHolderXG;
	BfmeUnitXG *m_bfmeUnitXG;
};

class Rva002AFFA0Owner
{
public:
	void drop(void *arg);
};

// The holder and the unit must be named locals so the allocator claims eax for
// the holder and ecx for the unit; the three later unit reads must stay inline
// so the kill call loads its receiver global after the argument pushes.
void Rva002AFFA0Owner::drop(void *arg)
{
	Rva002AFFA0Holder *holder = ((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeHolderXG;
	BfmeUnitXG *unit = ((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG;

	if (holder->m_bfmeSubXG.bfmeTestXG(unit, arg))
	{
		if (((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG->m_bfmeHookXG != 0)
			((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG->m_bfmeHookXG->bfmeNoteXG();

		TheBfmeLogicXG->bfmeKillXG(((BfmeOuterXG *)((char *)this - 0x20))->m_bfmeUnitXG, 0xffff, 1);
		((BfmeOuterXG *)((char *)this - 0x20))->bfmeFinishXG(arg);
	}
}
