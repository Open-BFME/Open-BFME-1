// cl: /O2 /Ob0

class Rva000E0AD0
{
	char m_pad[0x38];
	int m_slots[10];

public:
	void *get(int index);
};

void *Rva000E0AD0::get(int index)
{
	if (index < 0 || index >= 10)
		return (void *)0x01336E50;
	return &m_slots[index];
}
