// cl: /O2

extern "C" void __cdecl __identifier("?j_0001d30e@@YAXXZ")();
typedef void (__cdecl *BfmeHelpVMLThunk)(int *p, int a, int b, int c);

class BfmeFwdVML
{
public:
	void grokFwd(int a);
	int m_bfme00;
	int m_bfme04;
};

void BfmeFwdVML::grokFwd(int a)
{
	((BfmeHelpVMLThunk)&__identifier("?j_0001d30e@@YAXXZ"))(
		&a, m_bfme00, m_bfme04, a);
}
