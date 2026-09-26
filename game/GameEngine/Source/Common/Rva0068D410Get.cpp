// cl: /O2 /Ob0

class Rva0068D410
{
	char m_pad[0x58];
	struct Slot
	{
		char rest[0x68];
	} m_slots[8];

public:
	void *get(int index);
};

void *Rva0068D410::get(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return &m_slots[index];
}
