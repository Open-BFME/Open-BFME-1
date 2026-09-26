// ?bfmeNextToken@Gen009D1C50@@QAEDPAVBfmeLayoutVHH@@@Z
// cl: /DNDEBUG /MD /O2
// Byte-exact C++ reconstruction of the tokeniser at retail RVA 0x009D1C50.

__declspec(dllimport) int __cdecl isspace(int c);

class BfmeLayoutVHH;

class AsciiString
{
friend class BfmeLayoutVHH;

private:
	void releaseBuffer();
};

class BfmeLayoutVHH
{
public:
	void releaseBuffer()
	{
		m_string.releaseBuffer();
	}
	void bfmeCatVHH(const char *s, int n);

private:
	AsciiString m_string;
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
	while (m_pos < m_end)
	{
		if (isspace(static_cast<signed char>(m_buf[m_pos])) == 0)
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
	while (isspace(static_cast<signed char>(m_buf[m_pos])) == 0);
	return 1;
}
