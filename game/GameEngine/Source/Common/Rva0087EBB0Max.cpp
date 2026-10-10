// cl: /O2 /Ob0 /G6

struct BfmeCoordEB
{
	float m_x;
	float m_y;
	float m_z;
};

extern const float g_Va01132A80;

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class BfmeObjEB
{
public:
	unsigned char m_pad[0x44];
	BfmeCoordEB m_44;
	BfmeCoordEB m_50;
};

void bfmeApplyEB(BfmeObjEB *obj)
{
	BfmeCoordEB c;
	c.m_x = 0.0f;
	c.m_y = 0.0f;
	c.m_z = reinterpret_cast<const GeometryInfo *>(obj)->getMaxHeightAbovePosition() * g_Va01132A80;
	obj->m_50 = c;
	if (obj->m_44.m_z < c.m_z)
		obj->m_44 = c;
}

// Retail's fmul dword operand reads these four .rdata bytes: 1F 85 2B 3F.
const float g_Va01132A80 = 0.67f;
