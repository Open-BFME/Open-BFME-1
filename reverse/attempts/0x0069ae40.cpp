// ?bfmeCheckEQQ@@YGDPAUBfmeUnitEQQ@@@Z
// partial score=0.9 date=2026-09-15
// 86/90 bytes.  Writing the float test as !(health >= share) rather than
// health < share gives retail's fcomp / fnstsw / test ah,1 / je in place of
// test ah,5 / jp, so every byte up to +0x35 now matches.  The only residue is
// the redundant test eax,eax / je at retail +0x37, four bytes MSVC 7.1 removes
// here because the preceding null return already proved the pointer non-null.
// Tried and rejected: _ReadWriteBarrier between the two tests, static and
// __forceinline guard helpers, a ternary guard, a nested scope copy, and the
// flag sweep /Ob0 /Ob1 /Ob2 /Ox /O1 /Os /Ot /Oy- /Og- /Oi- /Gy- /GF- /Gs-.
// Pin needed: ?BfmeShareThirdEQQ@@3MB,0x00D1BB98  (float 33.333332)
typedef float Real;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern const Real BfmeShareThirdEQQ;

struct BfmeOwnerEQQ
{
	unsigned char m_bfmeHeadEQQ[0x41];
	char m_bfmeReadyEQQ;
	char m_bfmeDoneEQQ;
};

struct BfmeBodyEQQ
{
	unsigned char m_bfmeHeadEQQ[0x54];
	Real m_bfmeHealthEQQ;
};

struct BfmeUnitEQQ
{
	unsigned char m_bfmeHeadEQQ[4];
	BfmeBodyEQQ *m_bfmeBodyEQQ;
	unsigned char m_bfmeMidEQQ[4];
	BfmeOwnerEQQ *volatile m_bfmeOwnerEQQ;
	unsigned char m_bfmeTailEQQ[2];
	char m_bfmeFlagAEQQ;
	char m_bfmeFlagBEQQ;
	char m_bfmeFlagCEQQ;
};

char __stdcall bfmeCheckEQQ(BfmeUnitEQQ *unit)
{
	if (!unit->m_bfmeFlagAEQQ && !unit->m_bfmeFlagBEQQ && !unit->m_bfmeFlagCEQQ)
	{
		BfmeBodyEQQ *body = unit->m_bfmeBodyEQQ;
		if (body == 0 || !(body->m_bfmeHealthEQQ >= BfmeShareThirdEQQ))
		{
			BfmeOwnerEQQ *owner = unit->m_bfmeOwnerEQQ;
			if (owner == 0)
				return 1;
			_ReadWriteBarrier();
			if (owner != 0 && owner->m_bfmeReadyEQQ)
				return 1;
			BfmeOwnerEQQ *other = unit->m_bfmeOwnerEQQ;
			if (other == 0)
				return 1;
			_ReadWriteBarrier();
			if (other != 0 && other->m_bfmeDoneEQQ)
				return 1;
		}
	}
	return 0;
}
