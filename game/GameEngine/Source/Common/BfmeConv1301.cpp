// cl: /Od /Gy
// Open-BFME5 conversions.

class BfmeThingSUA
{
public:
	void bfmeOneSUA(char a);
	void bfmeTwoSUA(char a);
	void bfmeThreeSUA(char a, int b);
	void bfmeFourSUA(int a, int b);
	void bfmeFwdOneSUA(char a, int b);
	void bfmeFwdTwoSUA(int a, char b);
	void bfmeFwdThreeSUA(char a, int b);
	void bfmeFwdFourSUA(int a, int b);
};

void BfmeThingSUA::bfmeOneSUA(char a)
{
	bfmeFwdOneSUA(a, 0);
}

void BfmeThingSUA::bfmeTwoSUA(char a)
{
	bfmeFwdTwoSUA(1, a);
}

void BfmeThingSUA::bfmeThreeSUA(char a, int b)
{
	bfmeFwdThreeSUA(a, b);
}

void BfmeThingSUA::bfmeFourSUA(int a, int b)
{
	bfmeFwdFourSUA(a, b);
}
