extern "C" char *__cdecl strncpy(char *destination, const char *source,
	unsigned int count);

struct BfmeSubBLF
{
	unsigned char m_bfmeHead[4];
};

class BfmeThingBLF
{
public:
	void bfmeGoBLF(void *what);
	unsigned char m_bfmeHead[0x174];
	BfmeSubBLF m_bfmeSub;
};

void BfmeThingBLF::bfmeGoBLF(void *what)
{
	strncpy((char *)&m_bfmeSub, (const char *)what, 0x20);
}
