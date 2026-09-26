// cl: /O2 /Ob0

class Rva006962F0
{
	char m_lead[0x84];
	int m_count;

public:
	int postInc();
};

int Rva006962F0::postInc()
{
	return m_count++;
}
