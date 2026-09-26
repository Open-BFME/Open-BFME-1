// Three more tiny ones: a product of two globals and an argument, a value two
// hops away with minus one as the fallback, and another table copied between
// two globals.

extern float g_bfmeFirstCF;					// retail 0x012B5628
extern float g_bfmeSecondCF;					// retail 0x010F6394

// ?bfmeScale@@YAMM@Z
float __cdecl bfmeScale(float value)
{
	return g_bfmeFirstCF * g_bfmeSecondCF * value;
}

class BfmeLinkCF
{
public:
	int m_bfmeTag;						// +0x00
	int m_bfmeNext;						// +0x04
};

class Gen_0028EF10
{
public:
	int bfmeValue(void) const;

private:
	char m_bfmeHead[0x8C];					// +0x00
	BfmeLinkCF *m_bfmeLink;					// +0x8C
};

// ?bfmeValue@Gen_0028EF10@@QBEHXZ
int Gen_0028EF10::bfmeValue(void) const
{
	BfmeLinkCF *link = m_bfmeLink;

	if (link)
		return *(int *)(link->m_bfmeNext + 4);

	return -1;
}

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);

#pragma intrinsic(memcpy)

extern int g_bfmeSrcCF[22];					// retail 0x012B5100
extern int g_bfmeDstCF[22];					// retail 0x012B5158

// ?bfmeCopySecond@@YAXXZ
void __cdecl bfmeCopySecond(void)
{
	memcpy(g_bfmeDstCF, g_bfmeSrcCF, sizeof(g_bfmeDstCF));
}
