// cl: /O2 /Ob0

struct Rva00465CB0Slot
{
	int a;
	int b;
	int c;
	int d;
	int e;
};

class Rva00465CB0
{
	char pad[0xB0];
	Rva00465CB0Slot m_slots[12];

public:
	int get(unsigned i);
};

int Rva00465CB0::get(unsigned i)
{
	if (i >= 12)
		return 0;
	return m_slots[i].a;
}
