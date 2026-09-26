// cl: /O2 /Ob0

class Rva0016A270
{
	char m_pad[0x20];
	int m_slots[8];

public:
	int get(int index);
};

int Rva0016A270::get(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return m_slots[index];
}
