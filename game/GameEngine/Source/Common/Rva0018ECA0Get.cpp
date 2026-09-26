// cl: /O2 /Ob0

class Rva0018ECA0
{
	char pad[0x10];
	struct Slot { char rest[12]; } *m_base;
	int m_count;

public:
	void *get(int index);
};

void *Rva0018ECA0::get(int index)
{
	if (index < 0)
		index = 0;
	if (index >= m_count)
		index = m_count - 1;
	return &m_base[index];
}
