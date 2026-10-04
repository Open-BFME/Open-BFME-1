// cl: /DNDEBUG /MD /O2 /EHsc
struct Rva003D1380Elem
{
	unsigned char m_body[0x3c];
};

struct Rva003D2B80Coord
{
	float x;
	float y;

	Rva003D2B80Coord &operator-=(const Rva003D2B80Coord &c)
	{
		x -= c.x;
		y -= c.y;
		return *this;
	}
};

template <typename T>
struct Rva003D2B80Entries
{
	T *m_begin;
	T *m_end;
	T *m_capacity;

	T *begin() const { return m_begin; }
	int size() const { return (int)(m_end - m_begin); }
};

class Rva003D2B80Source
{
public:
	unsigned char m_pad00[0xc];
	volatile float m_step;
};

class Rva003D2B80Child
{
public:
	float m_originX;
	float m_originY;
	Rva003D2B80Entries<Rva003D1380Elem> m_entries;
	Rva003D2B80Source *m_source;
	int m_count;

	Rva003D1380Elem *lookup(Rva003D2B80Coord coord);
};

Rva003D1380Elem *Rva003D2B80Child::lookup(Rva003D2B80Coord coord)
{
	coord -= *(const Rva003D2B80Coord *)&m_originX;
	volatile float cs = m_source->m_step;
	float colCoordinate = coord.x;
	colCoordinate /= cs;
	int col = (int)colCoordinate;
	if (col >= 0 && col < m_count)
	{
		float rowCoordinate = *(volatile float *)&coord.y;
		rowCoordinate /= cs;
		int idx = (int)rowCoordinate * m_count + col;
		if (idx >= 0 && (unsigned)idx < (unsigned)m_entries.size())
			return m_entries.begin() + idx;
	}
	return 0;
}
