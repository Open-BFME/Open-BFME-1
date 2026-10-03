// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

// The call at +0x0019 goes through the ILT entry at 0x00003B52, which is
// Object::getProductionUpdateInterface()'s thunk; the body it reaches is
// matched at 0x001BF570.  Retail loads the list element into ecx and returns
// the interface in eax, which is what the thiscall member spells, so the call
// uses the real name.  The header is included for its declaration rather than
// redeclared; the local view below is only what this TU calls next.
#include "../../../../inputs/reference/shims/bfmeobject/GameLogic/Object.h"

class BfmeThingGA
{
public:
	virtual void bfmeSlot0GA(void);
	virtual void bfmeSlot1GA(void);
	virtual void bfmeSlot2GA(void);
	virtual void bfmeSlot3GA(void);
	virtual void bfmeHandleGA(void *payload);
};

class BfmeItemGA
{
public:
};

class BfmeNodeGA
{
public:
	BfmeNodeGA *m_bfmeNextGA;
	unsigned char m_bfmeMidGA[4];
	BfmeItemGA *m_bfmeItemGA;
};

class BfmeOwnerGA
{
public:
	void bfmeNotifyGA(void *payload);

	unsigned char m_bfmeHeadGA[4];
	BfmeNodeGA *m_bfmeListGA;
};

void BfmeOwnerGA::bfmeNotifyGA(void *payload)
{
	if (payload == 0)
		return;

	for (BfmeNodeGA *node = m_bfmeListGA->m_bfmeNextGA;
		node != m_bfmeListGA;
		node = node->m_bfmeNextGA)
	{
		BfmeThingGA *thing = (BfmeThingGA *)((Object *)node->m_bfmeItemGA)
			->getProductionUpdateInterface();
		if (thing != 0)
			thing->bfmeHandleGA(payload);
	}
}
