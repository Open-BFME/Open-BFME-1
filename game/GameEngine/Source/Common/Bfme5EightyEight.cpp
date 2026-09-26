// Three more: a record pushed into the next slot, a pair of vectors handed in
// at once, and an owner lookup that answers through one accessor.

class BfmeRecHE
{
public:
	int m_bfmeWords[6];
};

class Gen_008D2C80
{
public:
	void bfmePush(void);
private:
	int m_bfmeGap[8];							// +0x000
	BfmeRecHE m_bfmeCurrent;					// +0x020
	int m_bfmeGap2[128];						// +0x038
	BfmeRecHE m_bfmeSlots[16];					// +0x238
	int m_bfmeGap3;								// +0x3b8
	int m_bfmeCount;							// +0x3bc
};

void Gen_008D2C80::bfmePush(void)
{
	m_bfmeSlots[m_bfmeCount] = m_bfmeCurrent;
	++m_bfmeCount;
}

class BfmeVecHF
{
public:
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class Gen_0094AC70
{
public:
	void bfmeSetPair(const BfmeVecHF *a, const BfmeVecHF *b);
private:
	unsigned char m_bfmeFlag;					// +0x000
	unsigned char m_bfmeGap[3];					// +0x001
	int m_bfmeState;							// +0x004
	BfmeVecHF m_bfmeA;							// +0x008
	int m_bfmeGap2[84];							// +0x014
	BfmeVecHF m_bfmeB;							// +0x164
};

void Gen_0094AC70::bfmeSetPair(const BfmeVecHF *a, const BfmeVecHF *b)
{
	m_bfmeState = 0;

	m_bfmeA.m_bfmeX = a->m_bfmeX;
	m_bfmeA.m_bfmeY = a->m_bfmeY;
	m_bfmeA.m_bfmeZ = a->m_bfmeZ;

	m_bfmeB.m_bfmeX = b->m_bfmeX;
	m_bfmeB.m_bfmeY = b->m_bfmeY;
	m_bfmeB.m_bfmeZ = b->m_bfmeZ;

	m_bfmeFlag = 0;
}

class BfmeThingHD;

class BfmeOwnerHD
{
public:
	int m_bfmeGap[4];							// +0x00
	BfmeThingHD *m_bfmeThing;					// +0x10
};

class Gen_008C4230
{
public:
	bool bfmeHasThing(void) const;
	__forceinline bool bfmeShown(void) const { return !m_bfmeQuiet; }
	__forceinline BfmeThingHD *bfmeOwnerThing(void) const
	{
		if (m_bfmeKind == 19 && !bfmeShown())
			return 0;

		BfmeOwnerHD *owner = m_bfmeOwner;
		if (owner == 0 || owner == (BfmeOwnerHD *)0xBAADF00D)
			return 0;
		return owner->m_bfmeThing;
	}
private:
	int m_bfmeGap;								// +0x00
	unsigned int m_bfmeKind : 6;				// +0x04 bits 0-5
	unsigned int m_bfmeMid : 9;					//       bits 6-14
	unsigned int m_bfmeQuiet : 1;				//       bit 15
	unsigned int m_bfmeRest : 16;				//       bits 16-31
	int m_bfmeGap2[18];							// +0x08
	BfmeOwnerHD *m_bfmeOwner;					// +0x50
};

// The one kind that hides itself never has an owner worth asking.
bool Gen_008C4230::bfmeHasThing(void) const
{
	return bfmeOwnerThing() != 0;
}
