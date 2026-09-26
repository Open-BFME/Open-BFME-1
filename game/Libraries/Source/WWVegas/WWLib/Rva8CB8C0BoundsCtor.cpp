// ??0Rva8CB8C0Bounds@@QAE@HHHHHHH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable bounds constructor, retail 0x008CB8C0 (304 bytes).

class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	char m_base[0x1c];
};

struct Rva8CB8C0BoundsBlock
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
};

extern void (__cdecl *g_rva8CB8C0InitBounds)(Rva8CB8C0BoundsBlock *, int);

class Rva8CB8C0Bounds : public Rva899F00Base
{
public:
	Rva8CB8C0Bounds(int value18, int value14, int value10, int value08,
		int value04, int value00, int value1c);
	void apply(Rva8CB8C0BoundsBlock *first, Rva8CB8C0BoundsBlock *second,
		int offset);

private:
	Rva8CB8C0BoundsBlock m_first;
	Rva8CB8C0BoundsBlock m_second;
	int m_offset;
};

Rva8CB8C0Bounds::Rva8CB8C0Bounds(int value18, int value14, int value10,
	int value08, int value04, int value00, int value1c) :
	Rva899F00Base(reinterpret_cast<const char *>(0x1d), 8),
	m_offset(0)
{
	g_rva8CB8C0InitBounds(&m_first, 1);
	g_rva8CB8C0InitBounds(&m_second, 0);

	if (m_first.m_10 > m_second.m_10 ||
		(m_first.m_10 == m_second.m_10 && m_first.m_08 > m_second.m_08))
	{
		if (m_first.m_10 > m_second.m_10)
			m_offset = m_first.m_08 - m_second.m_08 + 24;
		else
			m_offset = m_first.m_08 - m_second.m_08;
	}
	else if (m_first.m_10 < m_second.m_10 ||
		(m_first.m_10 == m_second.m_10 && m_first.m_08 < m_second.m_08))
	{
		if (m_first.m_10 < m_second.m_10)
			m_offset = m_first.m_08 - m_second.m_08 - 24;
		else
			m_offset = m_first.m_08 - m_second.m_08;
	}

	m_first.m_18 = value18 == -1 ? m_first.m_18 : value18;
	m_first.m_14 = value14 == -1 ? m_first.m_14 : value14;
	m_first.m_10 = value10 == -1 ? m_first.m_10 : value10;
	m_first.m_08 = value08 == -1 ? m_first.m_08 : value08;
	m_first.m_04 = value04 == -1 ? m_first.m_04 : value04;
	m_first.m_00 = value00 == -1 ? m_first.m_00 : value00;
	m_first.m_1c = value1c == -1 ? m_first.m_1c : value1c;

	apply(&m_first, &m_second, m_offset);
}
