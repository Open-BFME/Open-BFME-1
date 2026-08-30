// ?d_00786b70@@YAXXZ
// partial score=0.95 date=2026-08-30
// cl: /O2 /Ob0
#include <string.h>
struct BfmeBlock786B70 { int m_a, m_b, m_c, m_d, m_e, m_f; };
class BfmeThing786B70
{
public:
	BfmeThing786B70();
	virtual ~BfmeThing786B70();

	int m_x;
	int m_y;
	int m_z;
	BfmeBlock786B70 m_block;
};
static void bfmeClearLeading786B70(BfmeThing786B70 *thing)
{
	thing->m_x = 0;
	thing->m_y = 0;
	thing->m_z = 0;
}
BfmeThing786B70::BfmeThing786B70()
{
	bfmeClearLeading786B70(this);
	memset(&m_block, 0, sizeof(m_block));
}
