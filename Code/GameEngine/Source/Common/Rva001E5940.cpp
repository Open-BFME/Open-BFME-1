// cl: /EHsc -D_STLP_NO_EXCEPTIONS
// stlport
//
// Sibling of the nine 157-byte allocate-notify-and-link bodies in
// Q4MakeNotifyLink.cpp. Same owner offsets (0x34 / 0x54 / 0x528 / 0x538),
// plus a byte store at owner+0x4DC after the list splice. Allocation size
// 0xA4. Address-derived names: identity is not recovered.

#include <list>

class Q4Owner001E5940
{
public:
	char m_gap0[0x4DC];
	char m_ready;
	char m_gap1[0x528 - 0x4DD];
	char m_flag;
	char m_gap2[0x538 - 0x529];
	_STL::list<void *> m_list;
};

class Made001E5940
{
public:
	__declspec(noinline) Made001E5940();
	virtual void slot();

	char m_gap04[0x34 - 4];
	Q4Owner001E5940 *m_owner;
	char m_gap38[0x54 - 0x38];
	char m_flag;
	char m_tail55[0xA4 - 0x55];
};

class INI;

void q4Parse001E5940(INI *a, Made001E5940 *m, int c, int d);

void Rva001E5940(INI *a, Q4Owner001E5940 *b)
{
	Made001E5940 *m = new Made001E5940;
	m->m_owner = b;
	q4Parse001E5940(a, m, 0, 0);
	m->m_flag = b->m_flag;
	b->m_list.push_back(m);
	b->m_ready = 1;
}
