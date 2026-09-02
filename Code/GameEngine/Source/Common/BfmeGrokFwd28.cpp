// cl: /O2

void bfmeHelpVML(int *p, int a, int b, int c);

class BfmeFwdVML
{
public:
	void grokFwd(int a);
	int m_bfme00;
	int m_bfme04;
};

void BfmeFwdVML::grokFwd(int a)
{
	bfmeHelpVML(&a, m_bfme00, m_bfme04, a);
}
