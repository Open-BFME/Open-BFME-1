// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The 44-byte S4 record constructor at retail RVA 0x00754590.  The named
// owner is intentionally address-qualified: the parse callback at 0x007751A0
// and the complete destructor at 0x00753E80 establish the record family, but
// no shipped header supplies a semantic class name for this private record.
//
// Its three 12-byte members are STLport narrow strings.  The first two use
// the literal/allocator constructor reached through ILT 0x0003B318; the last
// uses the default constructor reached through ILT 0x0004048A.  The two
// trailing scalar fields are zero-initialized.  There is no vtable in this
// record.

#include <string>

typedef int Int;

class S4Elem007746E0
{
public:
	S4Elem007746E0();

	_STL::string m_first;
	_STL::string m_second;
	_STL::string m_unused;
	Int m_unusedValue;
	Int m_value;
};

// ??0S4Elem007746E0@@QAE@XZ
S4Elem007746E0::S4Elem007746E0()
	: m_first(""),
	  m_second(""),
	  m_unused(),
	  m_unusedValue(0),
	  m_value(0)
{
}
