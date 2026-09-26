// cl: /Od

class BfmeStrVME
{
public:
	void bfmeResizeVME(unsigned n, char c);
	void bfmeEraseVME(char *a, char *b);
	void bfmeAppendVME(unsigned n, char c);
	char *m_bfme00;
	char *m_bfme04;
};

void BfmeStrVME::bfmeResizeVME(unsigned n, char c)
{
	if (n <= (unsigned)(m_bfme04 - m_bfme00))
	{
		char *n1 = m_bfme04;
		char *n2;
		char *n3;
		char *n4 = m_bfme00;
		bfmeEraseVME(n4 + n, n1);
	}
	else
		bfmeAppendVME(n - (unsigned)(m_bfme04 - m_bfme00), c);
}
