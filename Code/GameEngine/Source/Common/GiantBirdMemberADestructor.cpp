// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
//
// Open-BFME5: GiantBirdMemberA::~GiantBirdMemberA, retail 0x0027AF40.
// The inline StringBase forwarding destructor is required for the retail
// MSVC 7.1 register allocation and STLport vector cleanup shape.

#include <vector>
#include "StringInline.h"

struct GiantBirdMemberARecord
{
	unsigned char m_bytes[12];
};

template class _STL::vector<GiantBirdMemberARecord>;
typedef _STL::vector<GiantBirdMemberARecord> GiantBirdRecordVector;

class GiantBirdMemberA
{
public:
	~GiantBirdMemberA();

private:
	unsigned char m_padding[0x1c];
	AsciiString m_name;
	AsciiString m_description;
	GiantBirdRecordVector m_records;
};

GiantBirdMemberA::~GiantBirdMemberA()
{
}
