// Open-BFME5 conversions.

struct BfmeQ1206
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

extern "C" BfmeQ1206 g_bfmeD1206;

class BfmeA1206
{
public:
	void bfmeGet1206(BfmeQ1206 *out);
	char m_bfmePad0[0x20];
	BfmeQ1206 m_bfme20;
	char m_bfmePad1[0x384];
	int m_bfme3bc;
};

void BfmeA1206::bfmeGet1206(BfmeQ1206 *out)
{
	if (m_bfme3bc > 0) {
		*out = m_bfme20;
		return;
	}

	*out = g_bfmeD1206;
}
