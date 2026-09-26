// cl: /O2 /Ob0 /G6

struct BfmeCoordEB
{
	float m_x;
	float m_y;
	float m_z;
};

extern float g_bfmeKeb;

class BfmeObjEB
{
public:
	float maxAbove() const;

	unsigned char m_pad[0x44];
	BfmeCoordEB m_44;
	BfmeCoordEB m_50;
};

void bfmeApplyEB(BfmeObjEB *obj)
{
	BfmeCoordEB c;
	c.m_x = 0.0f;
	c.m_y = 0.0f;
	c.m_z = obj->maxAbove() * g_bfmeKeb;
	obj->m_50 = c;
	if (obj->m_44.m_z < c.m_z)
		obj->m_44 = c;
}
