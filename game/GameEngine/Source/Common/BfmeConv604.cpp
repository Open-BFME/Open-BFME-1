class BfmeOneCHF
{
public:
	void bfmeOneCHF();
};

class BfmeTwoCHF
{
public:
	void bfmeTwoCHF();
	unsigned char m_bfmeHead[0x44];
	bool m_bfmeFlag;
};

extern BfmeOneCHF *bfmeTheOneCHF;

// 0x012F1028 is the one Glo012F1028 global.  BfmeTwoCHF above is this TU's
// view of that object (its member is the pinned bfmeTwoCHF callee), so the use
// casts rather than declaring a second name for the address.
class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

void bfmeGoCHF()
{
	BfmeTwoCHF *two = (BfmeTwoCHF *)Glo012F1028;
	if (two->m_bfmeFlag)
	{
		bfmeTheOneCHF->bfmeOneCHF();
		two->bfmeTwoCHF();
		((BfmeTwoCHF *)Glo012F1028)->m_bfmeFlag = false;
	}
}
