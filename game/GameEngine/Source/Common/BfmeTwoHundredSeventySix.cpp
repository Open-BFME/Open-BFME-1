// cl: /Od
// Two runs, this record's own and the one the caller brought, passed on as four
// ends. Built without optimisation; the frame holds more than this body names.
// The callee is pinned by address.
// stlport

#include <string>

extern template int _STL::basic_string<char>::_M_compare(
	const char *, const char *, const char *, const char *);

struct BfmeThingPQ
{
	void bfmeGoPQ(const BfmeThingPQ *other);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

void BfmeThingPQ::bfmeGoPQ(const BfmeThingPQ *other)
{
	unsigned char spare[0x10];

	_STL::basic_string<char>::_M_compare(
		m_bfmeAt, m_bfmeEnd, other->m_bfmeAt, other->m_bfmeEnd);
}
