// ?bfmeCheckEQQ@@YGDPAUBfmeUnitEQQ@@@Z
// partial score=0.5333 date=2026-10-03
// Bank only: retail90B through RET4 at69AE97 thenINT3 at69AE9A.
// An unsigned-address >0 comparison retains JBE using the first TEST flags:
// 88B/38dif (quality0.5333), versus served86B/36dif (quality0.5111).
// Retail still needs another TEST/JZ and false-before-true return blocks.
// Integer >=1 emits91B/40dif; bool/char merge temporaries leave86B/36dif.
// Inherited type/member names and the global binding need independent review
// before promotion; no production identity is claimed by this experiment.
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
			if ((unsigned int)owner > 0 && owner->m_bfmeReadyEQQ)
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
