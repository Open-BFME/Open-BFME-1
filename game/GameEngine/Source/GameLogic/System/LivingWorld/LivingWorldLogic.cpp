// ?bfmeRecentDelta@Rva003BEF70Owner@@QAEXPAURva003BEF70Range@@PAURva003BEF70Coord2D@@@Z
// cl: /DNDEBUG /MD /EHsc
// variant v3: OR-merged clamp; slot-address key args; count defined before self

class Rva003C9470Key;

struct Rva003C9470Output
{
	union
	{
		float m_x;
		unsigned int m_rawX;
	};
	union
	{
		float m_y;
		unsigned int m_rawY;
	};
};

class Rva003C9470Owner
{
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);
};

struct Rva003BEF70Range
{
	Rva003C9470Key **m_begin;
	Rva003C9470Key **m_end;
};

struct Rva003BEF70Coord2D
{
	union
	{
		float x;
		unsigned int m_rawX;
	};
	union
	{
		float y;
		unsigned int m_rawY;
	};
};

class Rva003BEF70Owner
{
public:
	void bfmeRecentDelta(Rva003BEF70Range *range, Rva003BEF70Coord2D *out);

private:
	char m_pad00[0x28];
	Rva003C9470Owner *m_owner;			// +0x28
};

// ?bfmeRecentDelta@Rva003BEF70Owner@@QAEXPAURva003BEF70Range@@PAURva003BEF70Coord2D@@@Z
void Rva003BEF70Owner::bfmeRecentDelta(Rva003BEF70Range *range, Rva003BEF70Coord2D *out)
{
	int count = (int)(range->m_end - range->m_begin);
	Rva003BEF70Owner *self = this;

	int last = count - 1;
	int secondLast = count - 2;
	if (last < 0 || secondLast < 0)
	{
		last = 0;
		secondLast = 0;
	}

	Rva003C9470Output lastFill;
	self->m_owner->fallback((Rva003C9470Key *)&range->m_begin[last], &lastFill);

	Rva003C9470Output secondLastFill;
	self->m_owner->fallback((Rva003C9470Key *)&range->m_begin[secondLast], &secondLastFill);

	out->m_rawX = secondLastFill.m_rawX;
	out->x -= lastFill.m_x;
	out->m_rawY = secondLastFill.m_rawY;
	out->y -= lastFill.m_y;
}
