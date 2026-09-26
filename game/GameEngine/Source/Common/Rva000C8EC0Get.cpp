// cl: /O2 /Ob0

class Rva000C8EC0
{
	char m_pad[0x32C];
	int m_count;
	struct Slot
	{
		char rest[24];
	} m_slots[1];

public:
	void *get(int index);
};

void *Rva000C8EC0::get(int index)
{
	if (index < 0 || index >= m_count)
		return 0;
	return &m_slots[index];
}
