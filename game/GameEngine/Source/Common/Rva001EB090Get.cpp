// cl: /O2 /Ob0

struct Rva001EB090Slot
{
	int a[6];
};

class Rva001EB090
{
	char pad[0x88];
	Rva001EB090Slot m_slots[1];

public:
	void *get(int i);
};

void *Rva001EB090::get(int i)
{
	return &m_slots[i];
}
