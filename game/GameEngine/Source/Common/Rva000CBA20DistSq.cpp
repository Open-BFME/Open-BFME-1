// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva000CBA20Point
{
public:
	float x;
	float y;
};

class Rva000CBA20
{
	char m_pad[0x38];
	float m_x;
	float m_y;

public:
	float distSq(const Rva000CBA20Point *p);
};

float Rva000CBA20::distSq(const Rva000CBA20Point *p)
{
	float dx = m_x - p->x;
	float dy = m_y - p->y;
	return dx * dx + dy * dy;
}
