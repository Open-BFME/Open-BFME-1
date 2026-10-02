// cl: /O2 /Ob0 /G6
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// 0x00887C90 is StringBase<char>::set (ledger:
// ?set@?$StringBase@D@@QAEXABV1@@Z), so the element's 0x1C tail member is a
// real string and the element copy goes through that body, not a local helper.
struct BfmeCoordE9
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElemE9
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoordE9 m_10;
	StringBase<char> m_1C;
	char m_20;
	char m_pad[3];
};

void bfmeFillE9(BfmeElemE9 *first, BfmeElemE9 *last, const BfmeElemE9 *src)
{
	for (; first != last; ++first)
	{
		first->m_00 = src->m_00;
		first->m_04 = src->m_04;
		first->m_08 = src->m_08;
		first->m_0C = src->m_0C;
		first->m_10 = src->m_10;
		first->m_1C.set(src->m_1C);
		first->m_20 = src->m_20;
	}
}