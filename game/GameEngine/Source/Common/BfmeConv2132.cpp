extern float g_0107C64C;

class BfmeColourABK
{
public:
	void bfmeSetABK(int packed);

	unsigned char m_bfmeHeadABK[0x24];
	unsigned int m_bfme24ABK;
	unsigned int m_bfme28ABK;
	unsigned int m_bfme2CABK;
	unsigned char m_bfmeGapABK[4];
	unsigned int m_bfme34ABK;
};

void BfmeColourABK::bfmeSetABK(int packed)
{
	unsigned int flags = m_bfme34ABK;
	unsigned int rgb = packed & 0xffffff;

	m_bfme24ABK = rgb;

	if ((flags & 0x1420) != 0)
	{
		m_bfme28ABK = (m_bfme2CABK << 0x18) | rgb;
		return;
	}

	if ((flags & 0x840) == 0)
		return;

	float f = (float)m_bfme2CABK * g_0107C64C;

	int v = (int)((float)((packed >> 16) & 0xff) * f);

	v <<= 8;
	v |= (int)((float)((packed >> 8) & 0xff) * f);
	v <<= 8;
	v |= (int)((float)(packed & 0xff) * f);

	m_bfme28ABK = v;
}
