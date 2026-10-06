// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The 103-byte method appends one two-int record to the shared result payload.
// The constructor at 0x009F39F0 establishes the three vector pointers and the
// cursor at offset 0x0C. Callers at 0x009F6600 and 0x009F4130 provide the two
// record values. The overflow call reaches the library's own two-int vector
// _M_insert_overflow at 0x009F36F0, not the OCL Upgrades instance at 0x00262FE0,
// so the two-int record keeps a type of its own.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct IntPairRecord009F39F0
{
	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct Rva009F39F0Payload
{
	_STL::vector<IntPairRecord009F39F0> m_upgrades;
	void *m_cursor;
	int m_refCount;
};

struct Rva009F39F0Result
{
	Rva009F39F0Payload *m_value;

	void append(int first, int second);
};

__declspec(noinline) void Rva009F39F0Result::append(int first, int second)
{
	m_value->m_upgrades.push_back();

	m_value->m_upgrades.end()[-1].m_bfmeFirst = first;
	m_value->m_upgrades.end()[-1].m_bfmeSecond = second;
	m_value->m_cursor = m_value->m_upgrades.begin();
}
