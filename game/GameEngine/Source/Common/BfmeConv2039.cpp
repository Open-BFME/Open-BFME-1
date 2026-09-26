extern "C" __declspec(dllimport) double BfmeFloorER(double x);

class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float v);

	float m_bfmeBaseER;
	unsigned char m_bfmeHeadER[0xe4];
	float m_bfmeInvER;
	unsigned int m_bfmeCountER;
};

unsigned int BfmeHostER::bfmeIndexER(float v)
{
	float t = (float)BfmeFloorER((v - m_bfmeBaseER) * m_bfmeInvER * (float)m_bfmeCountER);
	int i;

	__asm fld t
	__asm fistp i

	if (i < 0)
		return 0;

	if ((unsigned int)i >= m_bfmeCountER)
		i = m_bfmeCountER - 1;

	return i;
}
