extern "C" double sqrt(double x);

#pragma intrinsic(sqrt)

extern "C" __declspec(dllimport) double bfmeMathVE(double x);

class BfmeShapeEU
{
public:
	int m_bfmeKindEU;
	unsigned char m_bfmePadEU[4];
	float m_bfmeAEU;
	float m_bfmeBEU;
};

class BfmeHostEU
{
public:
	int bfmeStepsEU(const BfmeShapeEU *s);

	unsigned char m_bfmeHeadEU[0x20];
	float m_bfmeScaleEU;
};

int BfmeHostEU::bfmeStepsEU(const BfmeShapeEU *s)
{
	float t;
	int n;

	switch (s->m_bfmeKindEU)
	{
		case 0:
		case 1:
		{
			t = (float)bfmeMathVE((s->m_bfmeAEU + s->m_bfmeAEU) * m_bfmeScaleEU);

			__asm fld t
			__asm fistp n

			break;
		}

		case 2:
		{
			float d = (float)sqrt(s->m_bfmeAEU * s->m_bfmeAEU + s->m_bfmeBEU * s->m_bfmeBEU);
			t = (float)bfmeMathVE((d + d) * m_bfmeScaleEU);

			__asm fld t
			__asm fistp n

			break;
		}

		default:
			return 4;
	}

	int c = n + 1;

	if (c > 100)
		c = 100;

	return c * c;
}
