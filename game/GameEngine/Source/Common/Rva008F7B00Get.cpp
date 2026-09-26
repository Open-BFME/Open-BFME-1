// cl: /O2 /Ob0

class Rva008F7B00
{
	char m_pad[0xA4];
	char m_slots[16];

public:
	char get(int index);
};

char Rva008F7B00::get(int index)
{
	if (index < 0 || index >= 16)
		return 0;
	return m_slots[index];
}
