extern "C" __declspec(dllimport) double BfmeFloorER(double x);

class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float v);

	unsigned char m_bfmeLeadES[4];
	float m_bfmeBaseES;
	unsigned char m_bfmeHeadES[0xe0];
	float m_bfmeInvES;
	unsigned int m_bfmeCountES;
};

unsigned int BfmeHostES::bfmeIndexES(float v)
{
	float t = (float)BfmeFloorER((v - m_bfmeBaseES) * m_bfmeInvES * (float)m_bfmeCountES);
	int i;

	__asm fld t
	__asm fistp i

	if (i < 0)
		return 0;

	if ((unsigned int)i >= m_bfmeCountES)
		i = m_bfmeCountES - 1;

	return i;
}
