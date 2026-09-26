// cl: /O2 /Ob0

class Rva0035EF60
{
	char m_pad[0x28];
	int m_count;
	struct Slot
	{
		char rest[0x61];
	} m_slots[1];

public:
	void *get(int index);
};

void *Rva0035EF60::get(int index)
{
	if (index < 0 || index >= m_count)
		return 0;
	return &m_slots[index];
}
