// Open-BFME5 conversions.

// Retail frees these arrays through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);
class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
};

class BfmeElemUJA
{
public:
	~BfmeElemUJA() { ((W3DRadarResetSurface *)this)->~W3DRadarResetSurface(); }
	char m_bfmePad[0x24];
};

class BfmeThingUJA
{
public:
	void bfmeClearUJA();
	void *m_bfmeVft;
	BfmeElemUJA *m_bfmeArray;
	int m_bfmeCount;
	char m_bfmePad;
	char m_bfmeOwned;
};

void BfmeThingUJA::bfmeClearUJA()
{
	if (m_bfmeArray && m_bfmeOwned) {
		delete [] m_bfmeArray;
		m_bfmeArray = 0;
	}
	m_bfmeOwned = 0;
	m_bfmeCount = 0;
}
