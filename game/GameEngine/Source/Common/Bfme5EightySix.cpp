// Two more: the pair that hides and shows the same flag.

class BfmeOwnerGW
{
public:
	int m_bfmeGap[7];							// +0x00
	int m_bfmeFlags;							// +0x1c
};

class BfmeThingGW
{
public:
	int m_bfmeGap;								// +0x00
	unsigned int m_bfmeKind : 6;				// +0x04 bits 0-5
	unsigned int m_bfmeMid : 9;					//       bits 6-14
	unsigned int m_bfmeQuiet : 1;				//       bit 15
	unsigned int m_bfmeRest : 16;				//       bits 16-31
public:
	__forceinline bool bfmeShown(void) const { return !m_bfmeQuiet; }
private:
	int m_bfmeGap2[18];							// +0x08
public:
	BfmeOwnerGW *m_bfmeOwner;					// +0x50
};

class BfmeStateGW;
extern BfmeStateGW *g_bfmeStateGW;

BfmeStateGW *bfmeHide(BfmeThingGW *thing)
{
	if ((thing->m_bfmeKind == 13 && !thing->bfmeShown()) ||
		(thing->m_bfmeKind == 18 && !thing->bfmeShown()))
	{
		thing->m_bfmeOwner->m_bfmeFlags &= ~0x2000000;
	}
	return g_bfmeStateGW;
}

BfmeStateGW *bfmeShow(BfmeThingGW *thing)
{
	if ((thing->m_bfmeKind == 13 && !thing->bfmeShown()) ||
		(thing->m_bfmeKind == 18 && !thing->bfmeShown()))
	{
		thing->m_bfmeOwner->m_bfmeFlags |= 0x2000000;
	}
	return g_bfmeStateGW;
}
