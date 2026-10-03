// ?bfmeNextToken@Gen009D1C50@@QAEDPAVBfmeLayoutVHH@@@Z
// cl: /DNDEBUG /MD /O2
// Byte-exact C++ reconstruction of the tokeniser at retail RVA 0x009D1C50.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl isspace(int c);

class Gen009D1C50;

class BfmeLayoutVHH
{
friend class Gen009D1C50;

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
	// Through the base: AsciiString::clear would emit a non-retail COMDAT.
	static_cast<StringBase<char> &>(out->m_string).clear();
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
		static_cast<StringBase<char> &>(out->m_string).concat(&ch, 1);
		++m_pos;
		if (m_pos >= m_end)
			break;
	}
	while (isspace(static_cast<signed char>(m_buf[m_pos])) == 0);
	return 1;
}
