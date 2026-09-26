// ?bfmeExtentTY@BfmeShapeTY@@QBEMXZ
// partial score=0.98 date=2026-09-08
extern "C" double sqrt(double x);
extern "C" double fabs(double x);

#pragma intrinsic(sqrt, fabs)

class BfmeShapeTY
{
public:
	float bfmeExtentTY() const;

	int m_bfmeKindTY;
	int m_bfmePadTY;
	float m_bfmeATY;
	float m_bfmeBTY;
	float m_bfmeXTY;
	float m_bfmeYTY;
};

float BfmeShapeTY::bfmeExtentTY() const
{
	float x = m_bfmeXTY;
	float y = m_bfmeYTY;
	volatile float r = 0.0f;

	switch (m_bfmeKindTY)
	{
		case 0:
			return m_bfmeATY + (float)sqrt(x * x + y * y);

		case 1:
			return m_bfmeATY + (float)sqrt(x * x + y * y);

		case 2:
		{
			float a = (float)fabs(x) + m_bfmeATY;
			float b = (float)fabs(y) + m_bfmeBTY;

			return (float)sqrt(a * a + b * b);
		}

		default:
			return r;
	}
}
