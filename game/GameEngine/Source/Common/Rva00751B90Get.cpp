// cl: /O2 /Ob0

struct Rva00751B90Slot
{
	char a[0x1C];
};

class Rva00751B90
{
	char pad[0xDC];
	Rva00751B90Slot m_slots[1];

public:
	void *get(int i);
};

void *Rva00751B90::get(int i)
{
	return &m_slots[i];
}
