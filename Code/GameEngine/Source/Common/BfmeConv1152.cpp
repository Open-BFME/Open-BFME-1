// cl: /Od
// Open-BFME5 conversions.

extern "C" void __cdecl bfmeCopy1152(char *d0, char *d1, char *s0, char *s1);

class BfmeR1152
{
public:
	char *m_bfme00;
	char *m_bfme04;
};

class BfmeS1152
{
public:
	void bfmeReplace1152(unsigned int pos, unsigned int n, BfmeR1152 *s);
	void bfmeThrow1152(void);
	char *m_bfme00;
	char *m_bfme04;
};

void BfmeS1152::bfmeReplace1152(unsigned int pos, unsigned int n, BfmeR1152 *s)
{
	const unsigned int *n1;
	int n2;
	int n3;
	int n4;
	unsigned int n5;
	int n6;

	if (pos > (unsigned int)(m_bfme04 - m_bfme00))
		bfmeThrow1152();

	n5 = (unsigned int)(m_bfme04 - m_bfme00) - pos;
	n1 = (n5 < n) ? &n5 : &n;
	bfmeCopy1152(m_bfme00 + pos, m_bfme00 + pos + *n1, s->m_bfme00, s->m_bfme04);
}
