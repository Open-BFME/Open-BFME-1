// cl: /Od /Gy
// Open-BFME5 conversions.

class BfmeThingSVA
{
public:
	void bfmeOneSVA(int a);
	void bfmeTwoSVA(int a);
	void bfmeFwdOneSVA(int a, int b);
	void bfmeFwdTwoSVA(int a, int b);
};

void BfmeThingSVA::bfmeOneSVA(int a)
{
	char m_bfmeScratch[0x24];
	bfmeFwdOneSVA(a, 0);
}

void BfmeThingSVA::bfmeTwoSVA(int a)
{
	char m_bfmeScratch[0x10];
	bfmeFwdTwoSVA(a, 0);
}
