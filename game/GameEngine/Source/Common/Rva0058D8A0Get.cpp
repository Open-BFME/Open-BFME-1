// cl: /O2 /Ob0

struct Rva0058D8A0Slot
{
	int a;
	int b;
	int c;
	int d;
	int e;
	int f;
};

class Rva0058D8A0
{
	Rva0058D8A0Slot m_slots[17];

public:
	bool get(int i);
};

bool Rva0058D8A0::get(int i)
{
	if (i < 0 || i >= 17)
		return false;
	return m_slots[i].c != m_slots[0].b;
}
