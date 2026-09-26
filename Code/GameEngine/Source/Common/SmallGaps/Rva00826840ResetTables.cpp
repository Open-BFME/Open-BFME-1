// ?resetTables@Rva00826840Owner@@QAEXXZ
#include <string.h>
struct Rva00826740Big { int m_v[0x89]; };
struct Rva00826740Small { int m_v[0x20]; };
extern const Rva00826740Big Rva00826740BigInit;
extern const Rva00826740Small Rva00826740SmallInit;
// Volatile reset slots and destination pointer preserve retail reset/copy order.
struct Rva00826840Owner {
	int m_0;
	volatile int m_4;
	Rva00826740Big* m_zeroed;
	Rva00826740Small m_small;
	Rva00826740Big* volatile m_big;
	volatile int m_90;
	volatile int m_94;
	void resetTables();
};
void Rva00826840Owner::resetTables()
{
	m_94 = 0;
	m_90 = 0;
	m_4 = 0;
	memcpy(m_big, &Rva00826740BigInit, sizeof(Rva00826740Big));
	memcpy(&m_small, &Rva00826740SmallInit, sizeof(Rva00826740Small));
	memset(m_zeroed, 0, sizeof(Rva00826740Big));
}
