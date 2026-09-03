// ?markReleased@Rva003527B0Tables@@QAEXXZ
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD /O2
// Mark every 20-byte record on two active chains. Retail addresses each slot
// with the scaled index as SIB base and the table pointer as index.

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

#define BFME_SIB(i, p) (*(unsigned char *)((i) + (unsigned int)(p)))
#define BFME_SIB_INT(i, p) (*(int *)((i) + (unsigned int)(p)))

// ?markReleased@Rva003527B0Tables@@QAEXXZ
void Rva003527B0Tables::markReleased()
{
	unsigned char mark = 1;
	int index = m_head0;
	if (index != -1)
	{
		do
		{
			unsigned int i = (unsigned int)index * 20;
			unsigned int p = (unsigned int)m_records0;
			BFME_SIB(i + 0xC, p) = mark;
			index = BFME_SIB_INT(i, m_records0);
		}
		while (index != -1);
	}

	index = m_head1;
	if (index != -1)
	{
		do
		{
			unsigned int i = (unsigned int)index * 20;
			unsigned int p = (unsigned int)m_records1;
			BFME_SIB(i + 0xC, p) = mark;
			index = BFME_SIB_INT(i, m_records1);
		}
		while (index != -1);
	}
}
