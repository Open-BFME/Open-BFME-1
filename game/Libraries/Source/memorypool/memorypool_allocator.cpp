// Address-derived identity; this is the block-integrity helper called by
// MemoryPool::_VerifyIntegrity at 0x00882D50.
// cl: /O2 /DNDEBUG /MD /Oa

unsigned char bfmeAllSame(
	const unsigned int *data, unsigned int value, unsigned int bytes);
extern void __cdecl memset32(void *ptr, int value, unsigned int bytesToFill);
// Address-derived guard-word count global at 0x0130EA00.
extern int Rva0130EA00GuardWords;

class Rva008838F0Owner
{
public:
	void rva008836F0(void *block, char *diagnostic, unsigned int limit);
};

class Rva00882580Block
{
public:
	unsigned char check(void);
	void setUsed(int used);
	void *guardStart(void);
private:
	void *m_field00;
	void *m_field04;
	unsigned int m_size08;
};

unsigned char Rva00882580Block::check(void)
{
	char diagnostic[0x1000];
	unsigned char good = 1;
	unsigned int guardWords = *(volatile unsigned int *)0x0130EA00;

	if (guardWords != 0)
	{
		unsigned int guardBytes = guardWords * 4;
		if (bfmeAllSame(
			(const unsigned int *)((unsigned int)this - guardBytes),
			0x0BADF00D, guardBytes) == 0)
			good = 0;
		if (bfmeAllSame(
			(const unsigned int *)((unsigned int)this + m_size08 + 0x0c),
			0x0BADF00D, guardBytes) == 0)
			good = 0;
	}

	if (m_field00 == 0 && *(volatile unsigned int *)0x0130EA04 != 0)
	{
		if (bfmeAllSame(
			(const unsigned int *)((unsigned int)this + 0x0c),
			0xDEADC0DE, m_size08) == 0)
			goto report;
	}

	if (good != 0)
		return 1;

report:
	if (*(volatile unsigned char *)0x0130E9F9 != 0)
		((Rva008838F0Owner *)0x0130EA10)->rva008836F0(
			(unsigned char *)this + 0x0c, diagnostic, 0x1000);
	return 1;
}

void Rva00882580Block::setUsed(int used)
{
	m_size08 = used;
	if (Rva0130EA00GuardWords)
		memset32((char *)this + used + 0x0c, 0x0BADF00D, Rva0130EA00GuardWords * 4);
}

void *Rva00882580Block::guardStart(void)
{
	return (char *)this - Rva0130EA00GuardWords * 4;
}
