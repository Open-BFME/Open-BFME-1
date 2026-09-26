// cl: /O2 /Ob0

class Rva009036C0
{
	unsigned char m_before[0x1a7];
	unsigned char m_status[100];

public:
	unsigned char get(int index) const;
};

unsigned char Rva009036C0::get(int index) const
{
	if (index >= 0 && index < 100) {
		return m_status[index];
	}
	return 0;
}
