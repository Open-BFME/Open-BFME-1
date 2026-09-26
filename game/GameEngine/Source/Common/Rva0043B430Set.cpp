// cl: /O2 /Ob0

struct Rva0043B430Slot
{
	int m_00;
	char m_04;
	char pad[15];
};

class Rva0043B430
{
	char pad[0x44];
	Rva0043B430Slot m_slots[25];

public:
	void set(int flag, unsigned i);
};

void Rva0043B430::set(int flag, unsigned i)
{
	if (!flag)
	{
		if (i < 25)
		{
			m_slots[i].m_00 = 0;
			m_slots[i].m_04 = 1;
		}
	}
}
