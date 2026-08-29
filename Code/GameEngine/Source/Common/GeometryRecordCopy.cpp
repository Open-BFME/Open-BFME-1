// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME: STLport GeometryRecord placement-copy helper, retail 0x000FD650.
//
// GeometryInfo's record vector proves the 0x10-byte element shape: three
// scalar words followed by AsciiString at +0x0c.  Retail performs a guarded
// placement copy of exactly one such element; the guard is the STLport
// placement-new null check retained by this compiler.

#include <memory>

class AsciiString
{
private:
	void *m_data;

public:
	AsciiString(const AsciiString &other);
	~AsciiString();
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

// ??$_Construct@UGeometryRecord@@U1@@_STL@@YAXPAUGeometryRecord@@ABU1@@Z
template void _STL::_Construct(GeometryRecord *, const GeometryRecord &);
