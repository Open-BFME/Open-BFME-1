// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Include /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// Retail 0x002350C0 (99 bytes, ret 8).  The receiver's ECX passes unchanged
// to Rva00233F30::rotatedOffset (0x00233F30), so both share the owner.  It
// default-constructs a 16-byte record with 0x00233C80 (ILT 0x00033D39, the
// same constructor Rva00244E60::add uses before pushing into the +0x12C
// vector), stores the rotated +4 pair and the source record's +0xC float,
// and returns it through 0x00232470 (ILT 0x0003535F, whose only caller in the
// image is this body).  Both constructors keep their bodies visible here and
// __declspec(noinline) (docs/shape_levers.md: give the callee its real body in
// the TU): MSVC 7.1 then proves the local never escapes and hoists the +0xC
// load above the pair stores exactly as retail does.  A declaration-only
// constructor leaves the stores ahead of the load.  Owner, record and member
// names are unproven, so they keep address and offset tokens.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "Lib/BaseType.h"

// landed: Code/GameEngine/Source/GameLogic/Object/Contain/Rva00233F30RotatedOffset.cpp
struct Rva00233F30Offset
{
	Rva00233F30Offset() {}
	Rva00233F30Offset(const Rva00233F30Offset &that) : x(that.x), y(that.y) {}
	Real x;
	Real y;
};

struct BfmeRva44E60Record
{
	__declspec(noinline) BfmeRva44E60Record(void) : m_dword00(0), m_float0C(0.0f) {}
	__declspec(noinline) BfmeRva44E60Record(const BfmeRva44E60Record &other)
		: m_dword00(other.m_dword00), m_pair04(other.m_pair04), m_float0C(other.m_float0C) {}

	Int m_dword00;
	Rva00233F30Offset m_pair04;
	Real m_float0C;
};

class Rva00233F30
{
public:
	Rva00233F30Offset rotatedOffset(const Coord2D *direction);
	BfmeRva44E60Record rva002350c0(Int index);

	char m_gap00[0x12c];
	_STL::vector<BfmeRva44E60Record> m_records12C;
};

BfmeRva44E60Record Rva00233F30::rva002350c0(Int index)
{
	BfmeRva44E60Record record;
	record.m_pair04 = rotatedOffset((const Coord2D *)&m_records12C[index].m_pair04);
	record.m_float0C = m_records12C[index].m_float0C;
	return record;
}
