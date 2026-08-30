// Clean reconstruction of the guarded counter transfer at RVA 0x009EB940.

class Rva009EB940Counter
{
public:
	char m_padding[0x28];
	int m_value;
};

class Rva009EB940Receiver
{
public:
	void bump();

	char m_padding[0x10];
	int m_value;
};

extern "C" Rva009EB940Counter *g_bfmeCounterBZ;

void Rva009EB940Receiver::bump()
{
	if (g_bfmeCounterBZ)
	{
		int *counter = &g_bfmeCounterBZ->m_value;
		++*counter;
		m_value = *counter;
	}
}
