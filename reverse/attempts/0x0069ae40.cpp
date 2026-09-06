// ?bfmeCheckEQQ@@YGDPAUBfmeUnitEQQ@@@Z (identity unknown)
// partial score=0.85 date=2026-09-06
// 86/90 bytes; missing only the redundant test eax,eax / je that MSVC propagates away.
// Pin needed: ?BfmeShareThirdEQQ@@3MB,0x00D1BB98  (float 33.333332)
typedef float Real;

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
		if (body == 0 || body->m_bfmeHealthEQQ < BfmeShareThirdEQQ)
		{
			BfmeOwnerEQQ *owner = unit->m_bfmeOwnerEQQ;
			if (owner == 0)
				return 1;
			if (owner != 0 && owner->m_bfmeReadyEQQ)
				return 1;
			BfmeOwnerEQQ *other = unit->m_bfmeOwnerEQQ;
			if (other == 0)
				return 1;
			if (other != 0 && other->m_bfmeDoneEQQ)
				return 1;
		}
	}
	return 0;
}
