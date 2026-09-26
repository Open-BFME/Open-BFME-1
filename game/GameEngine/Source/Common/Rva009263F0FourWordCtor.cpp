// cl: /O2 /Ob0

struct Rva009263F0Triple
{
	unsigned first;
	unsigned second;
	unsigned third;
};

class Rva009263F0
{
	unsigned m_first;
	unsigned m_second;
	unsigned m_third;
	unsigned m_fourth;

public:
	Rva009263F0(const Rva009263F0Triple *triple, const unsigned *fourth);
};

Rva009263F0::Rva009263F0(const Rva009263F0Triple *triple, const unsigned *fourth)
	: m_first(triple->first), m_second(triple->second), m_third(triple->third), m_fourth(*fourth)
{
}
