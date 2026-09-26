// ?resetTables@Rva00826740Owner@@QAEXXZ
#include <string.h>
struct Rva00826740Big { int m_v[0x89]; };
struct Rva00826740Small { int m_v[0x20]; };
extern const Rva00826740Big Rva00826740BigInit;
extern const Rva00826740Small Rva00826740SmallInit;
struct Rva00826740Owner {
	Rva00826740Big* m_zeroed;
	Rva00826740Small m_small;
	Rva00826740Big* m_big;
	void resetTables();
};
void Rva00826740Owner::resetTables()
{
	memcpy(m_big, &Rva00826740BigInit, sizeof(Rva00826740Big));
	memcpy(&m_small, &Rva00826740SmallInit, sizeof(Rva00826740Small));
	memset(m_zeroed, 0, sizeof(Rva00826740Big));
}
