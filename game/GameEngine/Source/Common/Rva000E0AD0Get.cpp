// cl: /O2 /Ob0

class AsciiString;
extern AsciiString TheEmptyString;

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
		return (void *)&TheEmptyString;
	return &m_slots[index];
}
