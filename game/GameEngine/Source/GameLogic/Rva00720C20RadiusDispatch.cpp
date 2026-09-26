// cl: /DNDEBUG /MD /EHs-c-
//
// Address-derived companion to Rva00720BB0LookupDispatch.  The retail body
// scans the 0xA4-byte records at +0x1548, tests their position against a
// caller-supplied radius, and forwards an eligible record to the dispatch
// routine already matched at 0x00720BB0.

struct Rva00720C20Coord3D
{
	float x;
	float y;
	float z;

	void set(float ax, float ay, float az)
	{
		x = ax;
		y = ay;
		z = az;
	}

	void set(const Rva00720C20Coord3D *a)
	{
		x = a->x;
		y = a->y;
		z = a->z;
	}

	void sub(const Rva00720C20Coord3D *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}

	float lengthSqr(void) const
	{
		return x * x + y * y + z * z;
	}
};

struct Rva00720C20Record
{
	float m_x;
	float m_y;
	float m_z;
	unsigned char m_pad0c[0x2c];
	int m_status;
	unsigned char m_pad3c[0x18];
	int m_owner;
	unsigned char m_pad58[0x4c];
};

class Rva00720BB0Context
{
public:
	void dispatchC20(int owner, void *request);
	void scan(const Rva00720C20Coord3D &center, float radius, void *request);

private:
	unsigned char m_pad0000[0x1548];
	Rva00720C20Record m_records[1];
	unsigned char m_pad15ec[0x1e1cc8 - 0x15ec];
	int m_count;
};

void Rva00720BB0Context::scan(const Rva00720C20Coord3D &center,
	float radius, void *request)
{
	int index = 0;
	if (m_count > 0)
	{
		float *position = &m_records->m_z;
		do
		{
			if (*(int *)((char *)position + 0x38) >= 0)
			{
				Rva00720C20Coord3D delta;
				Rva00720C20Coord3D point;
				point.set(&center);
				delta.set(position[-2], position[-1], position[0]);
				delta.sub(&point);
				if (delta.lengthSqr() < radius * radius)
					dispatchC20(*(int *)((char *)position + 0x54), request);
			}
			++index;
			position = (float *)((char *)position + 0xa4);
		} while (index < m_count);
	}
}
