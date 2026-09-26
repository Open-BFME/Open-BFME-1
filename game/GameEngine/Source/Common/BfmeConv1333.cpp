// Open-BFME5 conversions.

// Retail frees this array through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);

class BfmeElemUHA
{
public:
	~BfmeElemUHA();
	char m_bfmePad[4];
};

class BfmeThingUHA
{
public:
	void bfmeClearUHA();
	void *m_bfmeVft;
	BfmeElemUHA *m_bfmeArray;
	int m_bfmeCount;
	char m_bfmePad;
	char m_bfmeOwned;
};

void BfmeThingUHA::bfmeClearUHA()
{
	if (m_bfmeArray && m_bfmeOwned) {
		delete [] m_bfmeArray;
		m_bfmeArray = 0;
	}
	m_bfmeOwned = 0;
	m_bfmeCount = 0;
}
