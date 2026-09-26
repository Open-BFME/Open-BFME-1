// cl: /O2 /Ob0

class Rva003830A0
{
	char m_lead[0x108];
	int m_count;

public:
	int postInc();
};

int Rva003830A0::postInc()
{
	return m_count++;
}
