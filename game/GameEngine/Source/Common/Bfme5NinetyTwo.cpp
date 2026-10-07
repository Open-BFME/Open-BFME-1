// Point comparison, positive random remainder, and indexed global-list lookup.

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

#include "../../Include/GameClient/Video.h"
extern Video *g_bfmeVideoTableBegin;
extern Video *g_bfmeVideoTableEnd;

BfmeRecJD * __stdcall bfmeSlotAt(int index)
{
	if (index >= 0 && index < (int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin))
		return (BfmeRecJD *)(g_bfmeVideoTableBegin + index);
	return 0;
}
