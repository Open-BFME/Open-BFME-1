// cl: /O2
// Three floats accumulated into a member vector. Written through the member
// directly, MSVC loads the delta first in all three pairs; bound once as a
// reference it loads the member first for x, which is retail. The remaining two
// pairs load the delta first either way -- fadd is commutative and the shorter
// addressing mode wins.

struct BfmeVec2BB990
{
	float m_x;
	float m_y;
	float m_z;
};

class BfmeThing2BB990
{
public:
	void bfmeAdd2BB990(const BfmeVec2BB990 *delta);

private:
	char m_pad[0x4a4];
	BfmeVec2BB990 m_total;
};

void BfmeThing2BB990::bfmeAdd2BB990(const BfmeVec2BB990 *delta)
{
	BfmeVec2BB990 &total = m_total;

	total.m_x += delta->m_x;
	total.m_y += delta->m_y;
	total.m_z += delta->m_z;
}
