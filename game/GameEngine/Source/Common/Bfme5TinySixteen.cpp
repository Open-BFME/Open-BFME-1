// Four more tiny ones: a character written into a caller's word under two
// guards, a pair of floats stepped down by a global, two fields written
// through a member pointer read twice, and another pair handed back.

// ?bfmeWriteMark@@YAXHPAFE@Z
void __cdecl bfmeWriteMark(int unused, short *out, unsigned char skip)
{
	if (out && !skip)
		*out = 0x31;
}

extern float g_bfmeStepCG;					// retail 0x010F1BC8

class Gen_004223D0
{
public:
	void bfmeStepBack(void);

private:
	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
};

// ?bfmeStepBack@Gen_004223D0@@QAEXXZ
void Gen_004223D0::bfmeStepBack(void)
{
	m_bfmeX -= g_bfmeStepCG;
	m_bfmeY -= g_bfmeStepCG;
}

class BfmeThingCG
{
public:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeFirst;					// +0x08
	int m_bfmeSecond;					// +0x0C
};

class Gen_003F69C0
{
public:
	void bfmeSetPair(int *first, int second);

private:
	BfmeThingCG *m_bfmeThing;				// +0x00
};

class Gen_003D4E00
{
public:
	void bfmeGetPair(int *out) const;

private:
	char m_bfmeHead[0x2362C];				// +0x00000
	int m_bfmeFirst;					// +0x2362C
	int m_bfmeSecond;					// +0x23630
};

