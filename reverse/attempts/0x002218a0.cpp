// ?bfmeTestEL@BfmeHostEL@@QBEDPBVBfmeMtxEL@@@Z
// partial score=0.93 date=2026-09-12
// Address-derived reconstruction of retail RVA 0x002218A0.
// ContestableContain secondary vtable 0x010AB140 slot 0xA8.
extern const float BfmeZeroRange;

class BfmeMtxEL
{
public:
	unsigned char m_bfmeHeadEL[8];
	float m_bfmeAEL;
	unsigned char m_bfmePad0EL[0xc];
	float m_bfmeBEL;
	unsigned char m_bfmePad1EL[0xc];
	float m_bfmeCEL;
	unsigned char m_bfmePad2EL[0xc];
	float m_bfmeXEL;
	float m_bfmeYEL;
	float m_bfmeZEL;
};

class BfmeInfoEL
{
public:
	unsigned char m_bfmeHeadEL[0x138];
	float m_bfmeRangeEL;
};

class BfmeOtherEL
{
public:
	unsigned char m_bfmeHeadEL[0x38];
	float m_bfmeXEL;
	float m_bfmeYEL;
	float m_bfmeZEL;
};

class BfmeBaseEL
{
public:
	BfmeInfoEL *m_bfmeInfoEL;
	BfmeOtherEL *m_bfmeOtherEL;
};

class BfmeHostEL
{
public:
	char bfmeTestEL(const BfmeMtxEL *m) const;
};

// ?bfmeTestEL@BfmeHostEL@@QBEDPBVBfmeMtxEL@@@Z
char BfmeHostEL::bfmeTestEL(const BfmeMtxEL *m) const
{
	const BfmeMtxEL *p = m;
	volatile float v[3];

	if (p == 0)
		return 0;

	const BfmeBaseEL *base = (const BfmeBaseEL *)((const char *)this - 0x1c);
	BfmeInfoEL *info = base->m_bfmeInfoEL;

	if (info->m_bfmeRangeEL < BfmeZeroRange)
		return 0;

	BfmeOtherEL *o = base->m_bfmeOtherEL;

	if (p->m_bfmeZEL - o->m_bfmeZEL > info->m_bfmeRangeEL)
		return 0;

	float a = p->m_bfmeAEL;
	float b = p->m_bfmeBEL;
	float c = p->m_bfmeCEL;
	float d = o->m_bfmeYEL - p->m_bfmeYEL;
	v[0] = o->m_bfmeXEL - p->m_bfmeXEL;

	if (a * v[0] + b * d + c * BfmeZeroRange < BfmeZeroRange)
		return 0;

	return 1;
}
