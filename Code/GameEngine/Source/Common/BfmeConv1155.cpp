// cl: /Od
// Open-BFME5 conversions.

extern "C" char *__cdecl bfmeSearch1155(char *f0, char *f1, const char *s0, const char *s1);

class BfmeS1155
{
public:
	unsigned int bfmeFind1155(const char *s, unsigned int pos, unsigned int n);
	char *m_bfme00;
	char *m_bfme04;
};

unsigned int BfmeS1155::bfmeFind1155(const char *s, unsigned int pos, unsigned int n)
{
	char *n1;
	const char *n2;
	const char *n3;

	if (pos > (unsigned int)(m_bfme04 - m_bfme00))
		return 0xffffffff;

	n2 = s;
	n3 = s + n;
	n1 = bfmeSearch1155(m_bfme00 + pos, m_bfme04, n2, n3);
	return (n1 != m_bfme04) ? (unsigned int)(n1 - m_bfme00) : 0xffffffff;
}
