// Three more: a constructor seeded from three globals, a two-level
// comparator, and an angle from an inline arctangent.

extern int g_bfmeFirstEG;					// retail 0x012B87AC
extern int g_bfmeSecondEG;					// retail 0x012B87B0
extern int g_bfmeThirdEG;					// retail 0x012B87B4

class Gen_005A7460
{
public:
	Gen_005A7460(void);

private:
	bool m_bfmeFlag;					// +0x00
	char m_bfmePad[3];					// +0x01
	int m_bfmeA;						// +0x04
	int m_bfmeB;						// +0x08
	int m_bfmeC;						// +0x0C
	int m_bfmeFirst;					// +0x10
	int m_bfmeSecond;					// +0x14
	int m_bfmeThird;					// +0x18
	int m_bfmeD;						// +0x1C
};

// ??0Gen_005A7460@@QAE@XZ
Gen_005A7460::Gen_005A7460(void)
{
	m_bfmeFirst = g_bfmeFirstEG;
	m_bfmeSecond = g_bfmeSecondEG;
	m_bfmeThird = g_bfmeThirdEG;

	m_bfmeFlag = false;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = 0;
	m_bfmeD = 0;
}

class BfmeItemEG
{
public:
	int m_bfmeHead[5];					// +0x00
	int m_bfmeMinor;					// +0x14
	int m_bfmeMajor;					// +0x18
};

// ?bfmeLess@@YA_NPBVBfmeItemEG@@0@Z
bool __cdecl bfmeLess(const BfmeItemEG *first, const BfmeItemEG *second)
{
	if (first->m_bfmeMajor < second->m_bfmeMajor)
		return true;

	if (first->m_bfmeMajor > second->m_bfmeMajor)
		return false;

	return first->m_bfmeMinor < second->m_bfmeMinor;
}

extern "C" double __cdecl atan(double value);

#pragma intrinsic(atan)

extern float g_bfmeZeroCY;					// retail 0x01075350
extern float g_bfmeScaleEG;					// retail 0x010F693C
extern float g_bfmeDefaultEG;					// retail 0x01097114

// ?bfmeAngle@@YGMM@Z
float __stdcall bfmeAngle(float value)
{
	if (value > g_bfmeZeroCY)
		return (float)(atan(g_bfmeScaleEG / value) * 2);

	return g_bfmeDefaultEG;
}
