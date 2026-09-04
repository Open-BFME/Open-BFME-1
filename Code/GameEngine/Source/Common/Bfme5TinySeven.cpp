// Three more tiny ones: two globals set from one value (the second is the
// first shifted down, and the function is cdecl, so there is no argument
// clean-up), three fields initialised from a global and a zero, and an offset
// built out of two counts with two leas.

extern unsigned int g_bfmeFullBX;				// retail 0x012D71AC
extern unsigned int g_bfmeHalfBX;				// retail 0x012D71A8

// ?bfmeSetSize@@YAXI@Z
void __cdecl bfmeSetSize(unsigned int value)
{
	g_bfmeFullBX = value;

	g_bfmeHalfBX = value >> 1;
}

extern int g_bfmeSeedBX;					// retail 0x0133F420

class Gen_0095C7F0
{
public:
	void bfmeInit(void);

private:
	int m_bfmeHead[11];					// +0x00
	int m_bfmeSeed;						// +0x2C
	int m_bfmeFirst;					// +0x30
	int m_bfmeSecond;					// +0x34
};

// ?bfmeInit@Gen_0095C7F0@@QAEXXZ
void Gen_0095C7F0::bfmeInit(void)
{
	m_bfmeSeed = g_bfmeSeedBX;

	m_bfmeFirst = 0;
	m_bfmeSecond = 0;
}
