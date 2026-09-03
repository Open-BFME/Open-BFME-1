// ?bfmeNextToken@Gen009D1C50@@QAEDPAVBfmeLayoutVHH@@@Z
// partial score=0.91 date=2026-09-02
// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the classifier tokeniser at retail RVA 0x009D1C50.

extern "C" int (__cdecl *g_bfmeFn1182)(int c);

class BfmeLayoutVHH
{
public:
	void releaseBuffer();
	void bfmeCatVHH(const char *s, int n);
};

class Gen009D1C50
{
public:
	char bfmeNextToken(BfmeLayoutVHH *out);

private:
	unsigned char m_pad[0x14];
	const char *m_buf;
	int m_pos;
	int m_end;
};

char Gen009D1C50::bfmeNextToken(BfmeLayoutVHH *out)
{
	out->releaseBuffer();
	int (__cdecl *classify)(int) = g_bfmeFn1182;
	while (m_pos < m_end)
	{
		if (classify(static_cast<signed char>(m_buf[m_pos])) == 0)
			break;
		++m_pos;
	}
	if (m_pos >= m_end)
	{
		m_pos = m_end;
		return 0;
	}
	do
	{
		char ch = m_buf[m_pos];
		out->bfmeCatVHH(&ch, 1);
		++m_pos;
		if (m_pos >= m_end)
			break;
	}
	while (classify(static_cast<signed char>(m_buf[m_pos])) == 0);
	return 1;
}
