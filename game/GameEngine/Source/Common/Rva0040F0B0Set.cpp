// cl: /DNDEBUG /MD /O2 /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Retail assigns the live member at +0xAC with ?set@?$StringBase@G@@QAEXABV1@@Z
// (0x00888530), not with the copy ctor.  StringBase is declared here rather
// than pulled from inputs/reference/shims/stringinline because that shim's copy has no
// public set(), and a shim edit would take the full gate.

#include "string_base.h"

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString();
	UnicodeString( const UnicodeString &other );
	~UnicodeString();

};

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
	StringBase<unsigned short> *dst = &m_ac;
	dst->set( s );
	m_b0 = c;
	m_b4 = d;
	m_b8 = e;
	m_bc = a;
	m_c0 = b;
}
