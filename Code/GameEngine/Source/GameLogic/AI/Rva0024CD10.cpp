// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Horde transport state tick, retail 0x0024CD10.

int rva0024CD10Message(int kind, int phase, int data, int size);

class BfmeRvaCD10Base
{
public:
	void first(void);
	void second(void);
};

class Rva0024CD10
{
public:
	void update(void);
	void tail(void);

	char m_head[0xd4];
	int m_count;
	unsigned char m_enabled;
};

void Rva0024CD10::update(void)
{
	if (m_enabled == 1)
	{
		if (m_count == -1000)
		{
			BfmeRvaCD10Base *base = (BfmeRvaCD10Base *)((char *)this - 0x10);
			m_count = rva0024CD10Message(3, 5, 0x010B0710, 0x350);
			base->first();
		}
		if (m_count <= 0)
		{
			((BfmeRvaCD10Base *)((char *)this - 0x10))->second();
			m_count = rva0024CD10Message(0, 4, 0x010B0710, 0x35d);
		}
		--m_count;
	}
	tail();
}
