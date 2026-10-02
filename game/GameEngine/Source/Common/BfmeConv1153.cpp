// cl: /Od
// Open-BFME5 conversions.

extern "C" void __cdecl bfmeCopy1153(char *d0, char *d1, const char *s0, const char *s1);
extern "C" unsigned int __cdecl bfmeLen1153(const char *s);

// retail callee at 0x006434C0, reached through the ILT thunk at 0x000132CD;
// declaration only, the body is game/gen_small/fun_004.cpp
struct Gen_006434c0 { void m(); };

class BfmeS1153
{
public:
	void bfmeReplace1153(unsigned int pos, unsigned int n, const char *s);
	char *m_bfme00;
	char *m_bfme04;
};

void BfmeS1153::bfmeReplace1153(unsigned int pos, unsigned int n, const char *s)
{
	const unsigned int *n1;
	int n2;
	int n3;
	int n4;
	unsigned int n5;
	int n6;

	if (pos > (unsigned int)(m_bfme04 - m_bfme00))
		((Gen_006434c0 *)this)->m();

	n5 = (unsigned int)(m_bfme04 - m_bfme00) - pos;
	n1 = (n5 < n) ? &n5 : &n;
	bfmeCopy1153(m_bfme00 + pos, m_bfme00 + pos + *n1, s, s + bfmeLen1153(s));
}
