// cl: /O2 /Ob0

class Rva00336C60
{
	char m_pad[0x10720];
	struct Slot { char rest[0x7C]; } m_slots[1];

public:
	void *get(int index);
};

void *Rva00336C60::get(int index)
{
	if (index < 0 || index >= 0xB8)
		index = 0;
	return &m_slots[index];
}
