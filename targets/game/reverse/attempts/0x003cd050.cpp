// ?update@Rva003D2B80Child@@QAEXPAV1@00@Z
// partial score=0.89 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc
// The refresh callback at 0x003D2B80 calls this method through the thunk at
// 0x0004AFCF.  The retail body updates each 60-byte entry from eight samples
// in the three neighbouring children, then passes those samples to the
// matched Rva003CBA90::setSlots body.

// ?update@Rva003D2B80Child@@QAEXPAV1@00@Z present-unmatched

struct Rva003D2B80Source
{
	char m_pad00[0x0c];
	volatile float m_step;
};

struct Rva003D1380Elem;

struct Rva003D2B80Coord
{
	float m_x;
	float m_y;

	Rva003D2B80Coord(void) throw() {}
	Rva003D2B80Coord(const Rva003D2B80Coord &that) throw()
		: m_x(that.m_x), m_y(that.m_y) {}
	~Rva003D2B80Coord(void) throw() {}
};

class Y1SlotArray
{
public:
	Rva003D1380Elem *m_slot[8];
};

class Rva003CBA90
{
public:
	void setSlots(Y1SlotArray *incoming);
};

struct Rva003D1380Elem
{
	float m_x;
	float m_y;
	char m_pad08[0x08];
	char m_body10[0x2c];
};

class Rva003D2B80Child
{
public:
	char m_pad00[0x08];
	Rva003D1380Elem *m_begin;
	Rva003D1380Elem *m_end;
	Rva003D1380Elem *m_capacity;
	Rva003D2B80Source *m_source;

	Rva003D1380Elem *lookup(const Rva003D2B80Coord point);
	void update(Rva003D2B80Child *first, Rva003D2B80Child *second,
		Rva003D2B80Child *third);
};

#define BFME_HALF (*(const float *)0x0107533c)

void Rva003D2B80Child::update(Rva003D2B80Child *first,
	Rva003D2B80Child *second, Rva003D2B80Child *third)
{
	float half = m_source->m_step;
	Rva003D1380Elem *entry = m_begin;
	if (entry != m_end)
	{
		half *= BFME_HALF;
		do
		{
			Y1SlotArray slots;
			Rva003D2B80Coord point;
			point.m_x = entry->m_x + half;
			point.m_y = entry->m_y;
			slots.m_slot[0] = first->lookup(point);
			point.m_x = entry->m_x - half;
			slots.m_slot[1] = first->lookup(point);
			point.m_x = entry->m_x;
			point.m_y = entry->m_y + half;
			slots.m_slot[2] = second->lookup(point);
			point.m_y = entry->m_y - half;
			slots.m_slot[3] = second->lookup(point);
			point.m_x = entry->m_x + half;
			point.m_y = entry->m_y + half;
			slots.m_slot[4] = third->lookup(point);
			point.m_y = entry->m_y - half;
			slots.m_slot[5] = third->lookup(point);
			point.m_x = entry->m_x - half;
			// the (-x,-y) sample fills slot 7 and the (-x,+y) sample slot 6
			slots.m_slot[7] = third->lookup(point);
			point.m_y = entry->m_y + half;
			slots.m_slot[6] = third->lookup(point);
			((Rva003CBA90 *)entry)->setSlots(&slots);
			++entry;
		} while (entry != m_end);
	}
}
