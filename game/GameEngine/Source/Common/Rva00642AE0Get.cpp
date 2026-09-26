// cl: /O2 /Ob0

class Rva00642AE0
{
	char m_pad[0x19C];
	int m_slots[8];

public:
	int get(int index);
};

int Rva00642AE0::get(int index)
{
	if (index < 0 || index >= 8)
		return 0;
	return m_slots[index];
}
