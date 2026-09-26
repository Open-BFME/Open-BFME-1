// ?apply@Rva8CB8C0Bounds@@QAEXPAURva8CB8C0BoundsBlock@@0H@Z
// partial score=0.85 date=2026-09-02
// cl: /O2 /DNDEBUG /MD

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

int __stdcall daysInMonth(unsigned int month, int year);

class Rva8CB8C0Bounds
{
public:
	void apply(Rva8CB8C0BoundsBlock *first, Rva8CB8C0BoundsBlock *second,
		int offset);
};

void Rva8CB8C0Bounds::apply(Rva8CB8C0BoundsBlock *first,
	Rva8CB8C0BoundsBlock *second, int offset)
{
	int month;
	int year;
	int next;
	int day;
	int off;

	second->m_18 = first->m_18;
	second->m_14 = first->m_14;
	second->m_10 = first->m_10;
	off = offset;
	second->m_08 = first->m_08 - off;

	if (first->m_08 - off > 23)
	{
		int h = second->m_08;
		year = second->m_18;
		month = second->m_14;
		second->m_08 = h % 24;
		second->m_10++;
		if (second->m_10 > daysInMonth((unsigned int)month, year))
		{
			next = month + 1;
			second->m_10 = 1;
			second->m_14 = next;
			if (next > 11)
			{
				year++;
				second->m_14 = 0;
				second->m_18 = year;
			}
		}
	}
	else if (first->m_08 - off < 0)
	{
		second->m_08 = 24 - off;
		day = second->m_10 - 1;
		second->m_10 = day;
		if (day < 1)
		{
			second->m_14--;
			if (second->m_14 < 0)
			{
				year = second->m_18 - 1;
				second->m_14 = 11;
				second->m_18 = year;
			}
			second->m_10 = daysInMonth((unsigned int)second->m_14, second->m_18);
		}
	}

	second->m_04 = first->m_04;
	second->m_00 = first->m_00;
	second->m_1c = first->m_1c;
}
