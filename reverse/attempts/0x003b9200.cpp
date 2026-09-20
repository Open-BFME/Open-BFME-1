// ?rva003B9200ContainsAny@Rva003B9100@@QBE_NPBV1@@Z
// partial score=0.15 date=2026-09-20
// The adjacent exact Rva003B9100::contains body proves both objects own the
// same vector<AsciiString> layout. Retail passes the address of each element
// to the other owner's contains method and returns on the first shared name.
// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

struct BfmeStringData;

class AsciiString
{
public:
	BfmeStringData *m_data;
};

class Rva003B9100
{
public:
	bool contains(const AsciiString &name) const;
	bool rva003B9200ContainsAny(const Rva003B9100 *other) const;

private:
	char m_pad[0x0C];
	_STL::vector<AsciiString> m_vec;
};

bool Rva003B9100::rva003B9200ContainsAny(const Rva003B9100 *other) const
{
	for (unsigned int i = 0; i < m_vec.size(); ++i)
	{
		if (other->contains(m_vec[i]))
			return true;
	}
	return false;
}
