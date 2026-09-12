// ?bfmeSame@@YAHPBVBfmeItemEJ@@0@Z
// The 12 byte record layout and the 0x01075C70 tolerance match the retail
// body at 0x0058B4E0. The function compares two record keys and their float.

#include <math.h>

class BfmeItemEJ
{
public:
	int m_bfmeKey0;
	int m_bfmeKey1;
	float m_bfmeValue;
};

extern float g_bfmeScaleBK; // retail 0x01075C70

int __cdecl bfmeSame(const BfmeItemEJ *first, const BfmeItemEJ *second)
{
	if (first->m_bfmeKey0 != second->m_bfmeKey0)
		return 0;

	if (first->m_bfmeKey1 != second->m_bfmeKey1)
		return 0;

	return fabs(first->m_bfmeValue - second->m_bfmeValue) < g_bfmeScaleBK;
}
