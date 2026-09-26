// cl: /DNDEBUG /MD /EHsc-
// stlport

#include <vector>

// The 16-byte curve record is a one-word head followed by a trivially copied
// three-word tail.  Retail's 0x000699F0 constructor uses this nested layout;
// declaring four unrelated words changes the register schedule in insert().
struct Rva0006AA90ElementTail
{
	int m_value[3];
};

struct Rva0006AA90Element
{
	float m_time;
	Rva0006AA90ElementTail m_tail;

	Rva0006AA90Element() {}
	Rva0006AA90Element(const Rva0006AA90Element &other)
	{
		m_time = other.m_time;
		m_tail = other.m_tail;
	}
	~Rva0006AA90Element() {}
};

namespace _STL
{
	template <> void _Construct<Rva0006AA90Element, Rva0006AA90Element>(
		Rva0006AA90Element *destination,
		const Rva0006AA90Element &source);
}

#pragma comment(linker, "/alternatename:??$_Construct@URva0006AA90Element@@U1@@_STL@@YAXPAURva0006AA90Element@@ABU1@@Z=?j_0001f285@@YAXXZ")

template class _STL::vector<Rva0006AA90Element>;
