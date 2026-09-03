// cl: /DNDEBUG /MD /O2 /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class BfmeObjEE
{
public:
	void bfmeSetF0B0(UnicodeString s, int a, int b, int c, int d, int e);

	char m_pad[0xAC];
	UnicodeString m_ac;
	int m_b0;
	int m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
};

void BfmeObjEE::bfmeSetF0B0(UnicodeString s, int a, int b, int c, int d, int e)
{
	m_ac.UnicodeString::UnicodeString(s);
	m_b0 = c;
	m_b4 = d;
	m_b8 = e;
	m_bc = a;
	m_c0 = b;
}
