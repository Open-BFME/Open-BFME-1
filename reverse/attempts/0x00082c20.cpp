// ?rva00082C20JF@BfmeXfJF@@QAE_NHHM@Z
// partial score=0.88 date=2026-09-10
// The matched 0x00082AA0 sibling establishes this as the BFME GlobalData
// lighting record: time-of-day records are 0x6c bytes apart, begin at +0x224,
// and the active time is at +0x218.  The original source name of the second
// helper is not recovered, so its production name stays address-derived.
extern double g_bfmeSubB3;

class BfmeVec3JF
{
public:
	float m_bfmeXJF;
	float m_bfmeYJF;
	float m_bfmeZJF;
};

class BfmeSetJF
{
public:
	BfmeVec3JF m_bfmeGridJF[3][3];
};

class BfmeXfJF
{
public:
	bool bfmeLoadJF(int index);
	bool rva00082C20JF(int firstIndex, int secondIndex, float factor);

	unsigned char m_bfmeHeadJF[0x218];
	int m_bfmeIndexJF;
	unsigned char m_bfmeGap2JF[8];
	BfmeSetJF m_bfmeSetsJF[6];
	BfmeSetJF m_bfmeObjectSetsJF[6];
	BfmeSetJF m_bfmeThirdSetsJF[6];
	BfmeVec3JF m_bfmeOutJF[3][3];
};

bool BfmeXfJF::bfmeLoadJF(int index)
{
	if (index < 6 && index >= 1)
	{
		m_bfmeIndexJF = index;

		BfmeXfJF *sp = (BfmeXfJF *)((char *)this + index * 0x6c);

		m_bfmeOutJF[0][0] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[0][0];
		m_bfmeOutJF[1][0] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[0][1];
		m_bfmeOutJF[2][0] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[0][2];
		m_bfmeOutJF[0][1] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[1][0];
		m_bfmeOutJF[1][1] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[1][1];
		m_bfmeOutJF[2][1] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[1][2];
		m_bfmeOutJF[0][2] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[2][0];
		m_bfmeOutJF[1][2] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[2][1];
		m_bfmeOutJF[2][2] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[2][2];

		return true;
	}

	return false;
}

// Retail 0x00082C20 blends two time-of-day records into the fixed slot 5,
// then transposes that slot's three lighting groups into the active arrays.
// The repeated destination components are deliberate: they are the literal
// retail field writes, including the two unused component slots in this
// otherwise opaque BFME record.
bool BfmeXfJF::rva00082C20JF(int firstIndex, int secondIndex, float factor)
{
	if (firstIndex < 6 && firstIndex >= 1 &&
		secondIndex < 6 && secondIndex >= 1)
	{
		BfmeSetJF *secondSet =
			&((BfmeXfJF *)((char *)this + secondIndex * 0x6c))->m_bfmeSetsJF[0];
		BfmeSetJF *firstSet =
			&((BfmeXfJF *)((char *)this + firstIndex * 0x6c))->m_bfmeSetsJF[0];
		float *second = &secondSet->m_bfmeGridJF[0][0].m_bfmeYJF;
		float *first = &firstSet->m_bfmeGridJF[0][0].m_bfmeYJF;
		float oneMinusFactor = (float)(g_bfmeSubB3 - factor);
		float *out =
			(float *)((char *)this + 0x440);

#define BFME_BLEND(dst, lhs, rhs) \
		(dst) = oneMinusFactor * (lhs) + factor * (rhs)
#define BFME_BLEND_REVERSED(dst, lhs, rhs) \
		(dst) = factor * (rhs) + oneMinusFactor * (lhs)

		int i;
		for (i = 0; i < 3; ++i)
		{
			BFME_BLEND(out[0], first[-1], second[-1]);
			BFME_BLEND_REVERSED(out[1], first[0], second[0]);
			BFME_BLEND(out[0], first[1], second[1]);
			BFME_BLEND(out[0xc], first[2], second[2]);
			BFME_BLEND(out[0x10], first[3], second[3]);
			BFME_BLEND(out[0xc], first[4], second[4]);
			BFME_BLEND(out[0x18], first[5], second[5]);
			BFME_BLEND(out[0x1c], first[6], second[6]);
			BFME_BLEND(out[0x20], first[7], second[7]);

			BFME_BLEND(out[0xa5], first[0xa4], second[0xa4]);
			BFME_BLEND(out[0xa6], first[0xa5], second[0xa5]);
			BFME_BLEND(out[0xa5], first[0xa6], second[0xa6]);
			BFME_BLEND(out[0xa5], first[0xa4], second[0xa4]);
			BFME_BLEND(out[0xa6], first[0xa5], second[0xa5]);
			BFME_BLEND(out[0xa5], first[0xa6], second[0xa6]);
			BFME_BLEND(out[0xa8], first[0xa7], second[0xa7]);
			BFME_BLEND(out[0xa9], first[0xa8], second[0xa8]);
			BFME_BLEND(out[0xaa], first[0xa9], second[0xa9]);

			BFME_BLEND(out[0x144], first[0x143], second[0x143]);
			BFME_BLEND(out[0x145], first[0x144], second[0x144]);
			BFME_BLEND(out[0x144], first[0x145], second[0x145]);
			BFME_BLEND(out[0x147], first[0x146], second[0x146]);
			BFME_BLEND(out[0x148], first[0x147], second[0x147]);
			BFME_BLEND(out[0x147], first[0x148], second[0x148]);
			BFME_BLEND(out[0x149], first[0x149], second[0x149]);
			BFME_BLEND(out[0x14a], first[0x14a], second[0x14a]);
			BFME_BLEND(out[0x14c], first[0x14b], second[0x14b]);

			first += 9;
			second += 9;
			out += 9;
		}

#undef BFME_BLEND_REVERSED
#undef BFME_BLEND

		m_bfmeIndexJF = 5;

		m_bfmeOutJF[0][0] = *(BfmeVec3JF *)(out - 27);
		m_bfmeOutJF[1][0] = *(BfmeVec3JF *)(out - 24);
		m_bfmeOutJF[2][0] = *(BfmeVec3JF *)(out - 21);
		m_bfmeOutJF[0][1] = *(BfmeVec3JF *)(out - 18);
		m_bfmeOutJF[1][1] = *(BfmeVec3JF *)(out - 15);
		m_bfmeOutJF[2][1] = *(BfmeVec3JF *)(out - 12);
		m_bfmeOutJF[0][2] = *(BfmeVec3JF *)(out - 9);
		m_bfmeOutJF[1][2] = *(BfmeVec3JF *)(out - 6);
		m_bfmeOutJF[2][2] = *(BfmeVec3JF *)(out - 3);

		return true;
	}

	return false;
}
