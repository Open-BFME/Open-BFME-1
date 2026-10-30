// Open-BFME5 conversions.

extern "C" void *__identifier("??_7BfmeBaseVNH@@6B@");
#define g_bfmeVtaVNF __identifier("??_7BfmeBaseVNH@@6B@")
extern "C" void *__identifier("??_7Rva003BD6F0@@6B@");
#define g_bfmeVtcVNF __identifier("??_7Rva003BD6F0@@6B@")

struct BfmeVecVNF
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
};

// Retail 0x003BBD70 is a constructor (base then derived vftable, returns
// this), reached from the new-expression in Glo012F1024Item::j_0002a969,
// which passes the third argument from a float record field through an x87
// load/store temporary.
class BfmeBoxVNF
{
public:
	BfmeBoxVNF(unsigned w, const BfmeVecVNF *v, float n, unsigned h, char f);
	void *volatile m_bfme00;
	unsigned m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	float m_bfme18;
	unsigned m_bfme1c;
};

// ??0BfmeBoxVNF@@QAE@IPBUBfmeVecVNF@@MID@Z
BfmeBoxVNF::BfmeBoxVNF(unsigned w, const BfmeVecVNF *v, float n, unsigned h, char f)
{
	m_bfme00 = &g_bfmeVtaVNF;
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
	m_bfme00 = &g_bfmeVtcVNF;
	m_bfme0c = v->m_bfme00;
	m_bfme10 = v->m_bfme04;
	m_bfme14 = v->m_bfme08;
	m_bfme18 = n;
	m_bfme1c = (int)((float)h * 0.03f);
}
