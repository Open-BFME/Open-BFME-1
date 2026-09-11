// ?insert@?$vector@URva0006AA90Element@@V?$allocator@URva0006AA90Element@@@_STL@@@_STL@@QAEPAURva0006AA90Element@@PAU3@ABU3@@Z
// partial score=0.5 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc-
// stlport

#include <vector>

// Retail 0x0006AA90 inserts a 16-byte function-curve record into the sorted
// vector owned by Rva0006AB10Curve::set at 0x0006AB10.  The lower-bound call,
// vector-insert thunk, and the 97-byte retail body establish this ownership.

struct Rva0006AA90Element
{
	float m_time;
	float m_value;
	int m_inTangent;
	int m_outTangent;
};

namespace _STL
{
template <> void _Construct<Rva0006AA90Element, Rva0006AA90Element>(
	Rva0006AA90Element *destination,
	const Rva0006AA90Element &source);
}

#pragma comment(linker, "/alternatename:??$_Construct@URva0006AA90Element@@U1@@_STL@@YAXPAURva0006AA90Element@@ABU1@@Z=?j_0001f285@@YAXXZ")

struct Rva0006AA90InsertResult
{
	Rva0006AA90InsertResult() {}
	Rva0006AA90InsertResult(const Rva0006AA90InsertResult &other)
		: m_first(other.m_first), m_second(other.m_second) {}
	Rva0006AA90InsertResult(Rva0006AA90Element *const &first,
		const unsigned char &second)
	{
		m_second = second;
		m_first = first;
	}

	Rva0006AA90Element *m_first;
	bool m_second;
};

void *bfmeCurveFind(void *, void *, void *, unsigned int, int);
#pragma comment(linker, "/alternatename:?bfmeCurveFind@@YAPAXPAX00IH@Z=?bfmeSendEventA19@@YAXPAX00IH@Z")

class Rva0006AA90Vector
{
public:
	void *insert(void *position, const void *value);
	Rva0006AA90InsertResult insertUnique(const Rva0006AA90Element &value);

	Rva0006AA90Element *m_start;
	Rva0006AA90Element *m_finish;
	Rva0006AA90Element *m_end;
	unsigned char m_padding;
	unsigned char m_flag;
};

#pragma comment(linker, "/alternatename:?insert@Rva0006AA90Vector@@QAEPAXPAXPBX@Z=?j_00040566@@YAXXZ")

void *Rva0006AA90Vector::insert(void *position, const void *value)
{
	typedef _STL::vector<Rva0006AA90Element> Vector;
	return (void *)((Vector *)this)->insert(
		(Rva0006AA90Element *)position,
		*(const Rva0006AA90Element *)value);
}

template class _STL::vector<Rva0006AA90Element>;

#pragma comment(linker, "/alternatename:?insert@?$vector@URva0006AA90Element@@V?$allocator@URva0006AA90Element@@@_STL@@@_STL@@QAEPAURva0006AA90Element@@PAU3@ABU3@@Z=?j_00040566@@YAXXZ")

Rva0006AA90InsertResult Rva0006AA90Vector::insertUnique(
	const Rva0006AA90Element &value)
{
	bool duplicate = true;
	unsigned char *flag = this ? &m_flag : 0;
	unsigned int code = *flag;
	Rva0006AA90Element *start = m_start;
	Rva0006AA90Element *finish = m_finish;
	Rva0006AA90Element *position = (Rva0006AA90Element *)bfmeCurveFind(
		start, finish, (void *)&value, code, 0);
	if (position == finish || value.m_time < position->m_time)
	{
		position = (Rva0006AA90Element *)insert(position, &value);
		duplicate = false;
	}
	bool inserted = !duplicate;
	Rva0006AA90InsertResult result(position, inserted);
	return result;
}
