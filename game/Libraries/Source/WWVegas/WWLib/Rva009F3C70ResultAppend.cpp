// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// The 103-byte method appends one two-int record to the result payload.
// The body at 0x009F3C00 has the same layout and helper call, so this source
// keeps the candidate's separate address-derived identity.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class OCLSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		int m_bfmeFirst;
		int m_bfmeSecond;
	};
};

struct Rva009F3C70Payload
{
	_STL::vector<OCLSpecialPowerModuleData::Upgrades> m_upgrades;
	void *m_cursor;
	int m_refCount;
};

struct Rva009F3C70Result
{
	Rva009F3C70Payload *m_value;

	void append(int first, int second);
};

__declspec(noinline) void Rva009F3C70Result::append(int first, int second)
{
	m_value->m_upgrades.push_back();

	m_value->m_upgrades.end()[-1].m_bfmeFirst = first;
	m_value->m_upgrades.end()[-1].m_bfmeSecond = second;
	m_value->m_cursor = m_value->m_upgrades.begin();
}
