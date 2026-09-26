// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x007722F0 is an implicit assignment operator for a 32-byte value.
// Its only nontrivial member is this STLport string at +4; the callee is
// basic_string<char>::_M_assign_dispatch. No named caller or surviving symbol
// identifies the owner, so the class name deliberately remains address-based.
#include <string>

struct Rva007722F0StringMemberAssign
{
	struct Tail
	{
		int first;
		int second;
		int third;
	};

	Rva007722F0StringMemberAssign &operator=(
			const Rva007722F0StringMemberAssign &other);

	int m_head;
	_STL::basic_string<char> m_text;
	Tail m_tail;
	int m_tail3;
};

Rva007722F0StringMemberAssign &Rva007722F0StringMemberAssign::operator=(
		const Rva007722F0StringMemberAssign &other)
{
	m_head = other.m_head;
	m_text = other.m_text;
	m_tail = other.m_tail;
	m_tail3 = other.m_tail3;
	return *this;
}
