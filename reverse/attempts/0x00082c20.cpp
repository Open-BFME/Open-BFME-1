// ?rva00082C20JF@BfmeXfJF@@QAE_NHHM@Z
// partial score=0.89 date=2026-09-20
// ?rva00082C20JF@BfmeXfJF@@QAE_NHHM@Z
extern double g_bfmeSubB3;

class BfmeVec3JF
{
public:
	float m_bfmeXJF;
	float m_bfmeYJF;
	float m_bfmeZJF;
};

class BfmeLightingJF
{
public:
	struct RGBColorJF
	{
		float red;
		float green;
		float blue;
	};
	struct Coord3DJF
	{
		float x;
		float y;
		float z;
	};
	RGBColorJF ambient;
	RGBColorJF diffuse;
	Coord3DJF lightPos;
};

class BfmeSetJF
{
public:
	BfmeLightingJF m_bfmeLightsJF[3];
};

class BfmeXfJF
{
public:
	bool rva00082C20JF(int firstIndex, int secondIndex, float factor);

	unsigned char m_bfmeHeadJF[0x218];
	int m_bfmeIndexJF;
	unsigned char m_bfmeGap2JF[8];
	BfmeSetJF m_bfmeSetsJF[6];
	BfmeSetJF m_bfmeObjectSetsJF[6];
	BfmeSetJF m_bfmeThirdSetsJF[6];
	BfmeVec3JF m_bfmeOutJF[3][3];
};

bool BfmeXfJF::rva00082C20JF(int firstIndex, int secondIndex, float factor)
{
	if (firstIndex < 6 && firstIndex >= 1 &&
		secondIndex < 6 && secondIndex >= 1)
	{
		float *second = &m_bfmeSetsJF[secondIndex].m_bfmeLightsJF[0].ambient.green;
		float *first = &m_bfmeSetsJF[firstIndex].m_bfmeLightsJF[0].ambient.green;
		float oneMinusFactor = (float)(g_bfmeSubB3 - factor);
		float *out = &m_bfmeSetsJF[5].m_bfmeLightsJF[0].ambient.red;

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
			BFME_BLEND(out[3], first[2], second[2]);
			BFME_BLEND(out[4], first[3], second[3]);
			BFME_BLEND(out[3], first[4], second[4]);
			BFME_BLEND(out[6], first[5], second[5]);
			BFME_BLEND(out[7], first[6], second[6]);
			BFME_BLEND(out[8], first[7], second[7]);

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
