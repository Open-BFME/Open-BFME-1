// ?bfmeForward@Gen_009EBB60Target@@QAEHXZ
// cl: /O2 /DNDEBUG /MD /EHs-c-
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <deque>

struct CRITICAL_SECTION
{
	unsigned char m_data[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	CRITICAL_SECTION *lock);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(
	CRITICAL_SECTION *lock);

class Gen_009EBB60Target
{
public:
	int bfmeForward(void);

private:
	char m_pad00[0x60];
	CRITICAL_SECTION m_lock;
	_STL::deque<int> m_q0;
	_STL::deque<int> m_q1;
	_STL::deque<int> m_q2;
	char m_pade8[0x1e0 - 0xf0];
	int m_1e0;
	int m_1e4;
};

int Gen_009EBB60Target::bfmeForward(void)
{
	if (m_1e0 == 0 && m_1e4 == 0)
		return 100;

	EnterCriticalSection(&m_lock);

	int result = m_q0.size() + m_q1.size() + m_q2.size();

	LeaveCriticalSection(&m_lock);

	if (result == 0)
		return 100;

	unsigned int total = (unsigned int)(m_1e0 + m_1e4);
	return 99 - (int)((unsigned int)(result * 99) / total);
}
