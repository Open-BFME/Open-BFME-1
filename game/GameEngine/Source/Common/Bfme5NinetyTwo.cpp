// Four more: two comparisons answered the other way round, the generator again
// with its answer folded positive, and a global list lookup.

class BfmeVec2JE
{
public:
	float m_bfmeX;
	float m_bfmeY;
};

__forceinline int bfmeSamePoint(const BfmeVec2JE *a, const BfmeVec2JE *b)
{
	if (a->m_bfmeX == b->m_bfmeX && a->m_bfmeY == b->m_bfmeY)
		return 1;
	return 0;
}

bool bfmePointDiffers(const BfmeVec2JE *a, const BfmeVec2JE *b)
{
	unsigned char same = (unsigned char)bfmeSamePoint(a, b);
	return same == 0;
}

extern int g_rva012D4CB8;
extern int g_rva012D4CBC;

int bfmeRandomPositive(int range)
{
	int seed = g_rva012D4CB8;
	int carry = g_rva012D4CBC;

	int mix = seed * 0x3E322 + carry * 0x8149A;
	int next = mix % 0xF408B;

	g_rva012D4CBC = seed;
	g_rva012D4CB8 = next;

	int value = next % range;
	if (value < 0)
		value = -value;
	return value;
}

class BfmeRecJD
{
public:
	int m_bfmeWords[7];
};

extern BfmeRecJD *g_bfmeBeginJD;
extern BfmeRecJD *g_bfmeEndJD;

BfmeRecJD * __stdcall bfmeSlotAt(int index)
{
	if (index >= 0 && index < (int)(g_bfmeEndJD - g_bfmeBeginJD))
		return g_bfmeBeginJD + index;
	return 0;
}

extern "C" int memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

class BfmeStrIF
{
public:
	const char *m_bfmeBegin;					// +0x00
	const char *m_bfmeEnd;						// +0x04
};

__forceinline int bfmeSameText(const BfmeStrIF *a, const BfmeStrIF *b)
{
	int count = a->m_bfmeEnd - a->m_bfmeBegin;
	if (count == b->m_bfmeEnd - b->m_bfmeBegin && memcmp(a->m_bfmeBegin, b->m_bfmeBegin, count) == 0)
		return 1;
	return 0;
}

bool bfmeTextDiffers(const BfmeStrIF *a, const BfmeStrIF *b)
{
	unsigned char same = (unsigned char)bfmeSameText(a, b);
	return same == 0;
}
