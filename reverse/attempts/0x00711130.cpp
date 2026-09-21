// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// partial score=0.23 date=2026-09-21
struct Coord3D
{
	float x;
	float y;
	float z;
};

extern float g_bfmeK1253;	// retail 0x0107533C

class Rva00711130Target
{
public:
	char m_pad0[0xd8];
	Coord3D m_pos1;		// +0xd8
	Coord3D m_pos2;		// +0xe4
};

class Rva00711130Holder
{
public:
	void rva00711130(const Coord3D *point, bool subtract);

	char m_pad[0x12c];
	Rva00711130Target *m_target;
};

void Rva00711130Holder::rva00711130(const Coord3D *point, bool subtract)
{
	Rva00711130Target *target = m_target;

	float pos2y = target->m_pos2.y;
	float pos2x = target->m_pos2.x;
	float pos2z = target->m_pos2.z;
	float pos1x = target->m_pos1.x;
	float pos1y = target->m_pos1.y;
	float pos1z = target->m_pos1.z;

	if (subtract)
	{
		target->m_pos2.x = pos2x - point->x;
		target->m_pos2.y = pos2y - point->y;
		target->m_pos2.z = pos2z - point->z;
		target->m_pos1.x = pos1x - point->x * g_bfmeK1253;
		target->m_pos1.y = pos1y - point->y * g_bfmeK1253;
		target->m_pos1.z = pos1z - point->z * g_bfmeK1253;
	}
	else
	{
		target->m_pos2.x = pos2x + point->x;
		target->m_pos2.y = pos2y + point->y;
		target->m_pos2.z = pos2z + point->z;
		target->m_pos1.x = pos1x + point->x * g_bfmeK1253;
		target->m_pos1.y = pos1y + point->y * g_bfmeK1253;
		target->m_pos1.z = pos1z + point->z * g_bfmeK1253;
	}
}
