// ?markReleased@Rva003527B0Tables@@QAEXXZ
// cl: /DNDEBUG /MD /O2

class Rva003527B0Tables
{
public:
	void markReleased();

private:
	char m_pad0[0x18];
	unsigned char *m_records0;
	char m_pad1[0x0C];
	int m_head0;
	char m_pad2[0x0C];
	unsigned char *m_records1;
	char m_pad3[0x0C];
	int m_head1;
};

void Rva003527B0Tables::markReleased()
{
	unsigned char mark = 1;
	int index = m_head0;
	if (index != -1)
	{
		unsigned int p = (unsigned int)m_records0;
		do
		{
			unsigned int i = (unsigned int)index * 20;
			*(unsigned char *)(i + p + 0xC) = mark;
			p = (unsigned int)m_records0;
			index = *(int *)(i + p);
		}
		while (index != -1);
	}

	index = m_head1;
	if (index != -1)
	{
		unsigned int p = (unsigned int)m_records1;
		do
		{
			unsigned int i = (unsigned int)index * 20;
			*(unsigned char *)(i + p + 0xC) = mark;
			p = (unsigned int)m_records1;
			index = *(int *)(i + p);
		}
		while (index != -1);
	}
}
