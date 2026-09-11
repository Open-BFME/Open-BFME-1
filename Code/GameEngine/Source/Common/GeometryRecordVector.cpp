// cl: /EHsc
// stlport
// Open-BFME: canonical GeometryRecord vector specialization used by the
// GeometryInfo constructor at retail 0x00100580.
//
// The exact constructor supplies vector<GeometryRecord>'s +0x38 owner and
// calls erase through ILT 0x0001BD38.  The thunk routes to the 76-byte body at
// 0x000FF890.  Its 0x10-byte stride agrees with GeometryRecord's three scalar
// fields and one-pointer AsciiString member.

#include <vector>

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &other);
	~AsciiString();
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

template class _STL::vector<GeometryRecord>;
