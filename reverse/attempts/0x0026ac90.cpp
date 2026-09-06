// ?bfmeGetFO@BfmeSecondFO@@QAEHXZ (identity unknown)
// partial score=0.9 date=2026-09-06
// 36/33; MSVC spills the entry pointer to esi (push/pop) where retail keeps
// holder in ecx and entry in eax with no callee-saved register.
// Pin: ?bfmeTouchFO@BfmeInnerFO@@QAEXXZ,0x00048C61
class BfmeInnerFO
{
public:
	void bfmeTouchFO(void);
};

class BfmeNodeFO
{
public:
	unsigned char m_bfmeHeadFO[4];
	BfmeNodeFO *m_bfmeNextFO;
	unsigned char m_bfmeMidFO[0x14];
	int m_bfmeValueFO;
};

class BfmePrimaryFO
{
public:
	unsigned char m_bfmeHeadFO[8];
	BfmeNodeFO *m_bfmeHolderFO;
};

class BfmeSecondFO
{
public:
	int bfmeGetFO(void);
};

int BfmeSecondFO::bfmeGetFO(void)
{
	char *base = (char *)this;
	BfmePrimaryFO *owner = *(BfmePrimaryFO **)(base - 0x20);
	BfmeNodeFO *holder = owner->m_bfmeHolderFO;

	BfmeNodeFO *entry = holder->m_bfmeNextFO;
	if (entry != 0)
	{
		BfmeInnerFO *inner = (BfmeInnerFO *)entry->m_bfmeNextFO;
		if (inner != 0)
			inner->bfmeTouchFO();

		return entry->m_bfmeValueFO;
	}

	return holder->m_bfmeValueFO;
}
