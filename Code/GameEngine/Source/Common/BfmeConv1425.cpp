// cl: /Od

struct BfmeFlagVMC
{
	char m_bfme00;
};

void bfmeCallVMC(int a, int b, int c);

void bfmeFwdVMC(int a, int b, int c)
{
	BfmeFlagVMC n1 = BfmeFlagVMC();
	BfmeFlagVMC n2 = BfmeFlagVMC();

	bfmeCallVMC(a, b, c);
}
