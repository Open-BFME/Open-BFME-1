// Open-BFME5 conversions.

struct BfmeQ1210
{
	int m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14;
};

extern "C" __declspec(dllimport) void __cdecl bfmeNotify1210(BfmeQ1210 *a);

class BfmeA1210
{
public:
	void bfmePop1210();
	char m_bfmePad00[0x20];
	BfmeQ1210 m_bfme20;
	char m_bfmePad38[0x238 - 0x38];
	BfmeQ1210 m_bfme238[16];
	int m_bfme3b8;
	int m_bfme3bc;
};

void BfmeA1210::bfmePop1210()
{
	--m_bfme3bc;
	m_bfme20 = m_bfme238[m_bfme3bc];
	bfmeNotify1210(&m_bfme20);
}
