// cl: /O2 /Ob0

class Rva00336C30
{
	char m_pad[0x1C];
	struct Slot { char rest[0x7C]; } m_slots[1];

public:
	void *get(int index);
};

void *Rva00336C30::get(int index)
{
	if (index < 0 || index >= 0x21F)
		index = 0;
	return &m_slots[index];
}
