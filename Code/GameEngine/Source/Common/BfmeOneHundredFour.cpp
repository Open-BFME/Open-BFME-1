// Three more: two sibling record copies with three names each, and a search
// over eight slots for the one that already matches.

extern "C" char *strcpy(char *dst, const char *src);
#pragma intrinsic(strcpy)

class BfmeRecOA
{
public:
	int m_bfmeGap;								// +0x000
	int m_bfmeId;								// +0x004
	char m_bfmeName[82];						// +0x008
	char m_bfmeSecond[205];						// +0x05a
	char m_bfmeThird[64];						// +0x127
};

class BfmeRecOB
{
public:
	int m_bfmeGap;								// +0x00
	int m_bfmeId;								// +0x04
	int m_bfmeGap2;								// +0x08
	char m_bfmeName[31];						// +0x0c
	char m_bfmeSecond[51];						// +0x2b
	char m_bfmeThird[64];						// +0x5e
};

void bfmeCopyRec(int unused, const BfmeRecOA *src, BfmeRecOB *dst)
{
	dst->m_bfmeId = src->m_bfmeId;

	strcpy(dst->m_bfmeName, src->m_bfmeName);
	strcpy(dst->m_bfmeSecond, src->m_bfmeSecond);
	strcpy(dst->m_bfmeThird, src->m_bfmeThird);
}

void bfmeCopyRecAgain(int unused, const BfmeRecOA *src, BfmeRecOB *dst)
{
	dst->m_bfmeId = src->m_bfmeId;

	strcpy(dst->m_bfmeName, src->m_bfmeName);
	strcpy(dst->m_bfmeSecond, src->m_bfmeSecond);
	strcpy(dst->m_bfmeThird, src->m_bfmeThird);
}

class BfmeThingOC
{
public:
	int m_bfmeGap;								// +0x00
	int m_bfmeKind;								// +0x04
	int m_bfmeGap2[10];							// +0x08
	int m_bfmeOwner;							// +0x30
	unsigned short m_bfmeTag;					// +0x34
};

class Gen_0061E920
{
public:
	int bfmeFindSlot(void) const;
	__forceinline BfmeThingOC *bfmeSlotAt(int index) const
	{
		if (index < 0 || index >= 8)
			return 0;
		return m_bfmeSlots[index];
	}
private:
	int m_bfmeGap[3];							// +0x00
	unsigned char m_bfmeReady;					// +0x0c
	unsigned char m_bfmeGap2[7];				// +0x0d
	BfmeThingOC *m_bfmeSlots[8];				// +0x14
	int m_bfmeOwner;							// +0x34
	unsigned short m_bfmeTag;					// +0x38
};

int Gen_0061E920::bfmeFindSlot(void) const
{
	if (!m_bfmeReady)
		return -1;

	for (int index = 0; index < 8; ++index)
	{
		BfmeThingOC *thing = bfmeSlotAt(index);
		if (thing != 0 && thing->m_bfmeKind == 5 && thing->m_bfmeOwner == m_bfmeOwner
			&& thing->m_bfmeTag == m_bfmeTag)
			return index;
	}
	return -1;
}
