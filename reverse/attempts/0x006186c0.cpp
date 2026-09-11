// ?rva0001895d@Rva00615D50Object@@QAE?AUCoord3D@@XZ
// partial score=0.85 date=2026-09-11
// Authentic identity: the 0x00615D50 lookup is a named caller and its ILT
// 0x0001895D names this Rva00615D50Object world-position getter.  The body is
// an SRET Coord3D getter over the holder at this+0x0c and item coordinates at
// +0x24, +0x34 and +0x44.  This clean shape is 89/97 bytes: the remaining
// mismatch is the compiler's x87/register scheduling and y temporary spill.
extern const float BfmeZeroRange;

struct Coord3D
{
	Coord3D(float x, float y, float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}

	float m_x;
	float m_y;
	float m_z;
};

class Rva00615D50Item
{
public:
	virtual void d00();
	virtual void d04();
	virtual void d08();
	virtual void d0C();
	virtual void d10();
	virtual void d14();
	virtual void d18();
	virtual void d1C();
	virtual void d20();
	virtual void d24();
	virtual void d28();
	virtual void d2C();
	virtual void d30();
	virtual void d34();
	virtual void d38();
	virtual void d3C();
	virtual void d40();
	virtual void d44();
	virtual void d48();
	virtual void d4C();
	virtual void update();

	unsigned char m_at04[0x20];
	float m_x;
	unsigned char m_at28[0x0c];
	float m_y;
	unsigned char m_at38[0x0c];
	float m_z;
};

struct Rva00615D50Holder
{
	unsigned char m_at00[8];
	Rva00615D50Item *m_item;
};

struct Rva00615D50Object
{
	Coord3D rva0001895d();

	void *m_at00;
	void *m_type;
	int m_id;
	Rva00615D50Holder *m_holder;
};

Coord3D Rva00615D50Object::rva0001895d()
{
	float x = 0.0f;
	float y = BfmeZeroRange;
	float z = 0.0f;
	Rva00615D50Item *item = m_holder->m_item;

	if (item != 0)
	{
		item->update();
		x = item->m_x;
		y = item->m_y;
		z = item->m_z;
	}

	return Coord3D(x, y, z);
}
