// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Fill a 0x18-byte result from the cursor at +0x24/+0x28/+0x30 and the
// two dwords at +0x18FC/+0x1900. Scale the pair of ints by the float at
// 0x01075C74.

struct Rva006BE6A0Out
{
	int m_a;
	int m_b;
	int m_18fc;
	float m_x;
	float m_y;
	int m_1900;
};

class Rva006BE6A0
{
public:
	void fill(Rva006BE6A0Out *out);

private:
	struct Pair { int a; int b; };

	char m_pad24[0x24];
	Pair *m_cursor;
	Pair *m_end;
	char m_pad30[0x30 - 0x2C];
	int m_index;
	char m_pad18fc[0x18FC - 0x34];
	int m_18fc;
	int m_1900;
};

#define MAP_XY_FACTOR 10.0f

void Rva006BE6A0::fill(Rva006BE6A0Out *out)
{
	out->m_a = 0;
	out->m_b = 0;
	if (m_cursor != m_end)
	{
		out->m_x = m_cursor[m_index].a * MAP_XY_FACTOR;
		out->m_y = m_cursor[m_index].b * MAP_XY_FACTOR;
	}
	else
	{
		out->m_x = 0.0f;
		out->m_y = 0.0f;
	}
	out->m_18fc = m_18fc;
	out->m_1900 = m_1900;
}
