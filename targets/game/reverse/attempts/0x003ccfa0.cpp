// ?bfmeAtABL@BfmeGridABL@@QAEPAUBfmeCellABL@@MM@Z
// partial score=0.9 date=2026-09-09
struct Rva003D1380Elem
{
	unsigned char m_body[0x3c];
};

struct Rva003D2B80Coord
{
	float x;
	float y;
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
	register Rva003D2B80Child *self = this;
	float fx = coord.x;
	fx -= self->m_originX;
	float cs = self->m_source->m_step;
	float fy = coord.y;
	fy -= self->m_originY;

	int col = (int)(fx / cs);

	if (col < 0)
		return 0;

	int w = self->m_count;

	if (col >= w)
		return 0;

	int idx = (int)(fy / cs) * w + col;

	if (idx < 0)
		return 0;

	if ((unsigned int)idx >= (unsigned int)self->m_entries.size())
		return 0;

	return self->m_entries.begin() + idx;
}
