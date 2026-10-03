#define OBJECT_TU_MEMBERS \
	void *unidentified_001BFE20() const; \
	bool isLocallyControlled() const;
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class ClientRoot4120
{
public:
	unsigned char m_bfmePad[0xb4];
	int m_bfmeValue;
};

// The global is declared by its defining spelling so the object references
// ?TheGameClient@@3PAVGameClient@@A; ClientRoot4120 above is only the local
// +0xb4/+0xb8 layout view the body below needs.
class GameClient;
extern GameClient *TheGameClient;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// ILT 0x0002CA61 reaches this dump at 0x001CABE0: ECX is the only
// argument, and EAX holds the result. A one-argument fastcall has that ABI.
extern void d_001cabe0();
// ILT 0x0004067E reaches the one-stack-word thiscall body at 0x0041A2E0.
extern void d_0041a2e0();

class BfmeX1004
{
public:
	virtual void bfmeVX01004();
	virtual void bfmeVX11004();
	virtual void bfmeVX21004();
	virtual void bfmeVX31004();
	virtual void bfmeVX41004();
	virtual void bfmeVX51004();
	virtual void bfmeVX61004();
	virtual void bfmeVX71004();
	virtual void bfmeVX81004();
	virtual void bfmeVX91004();
	virtual void bfmeVX101004();
	virtual void bfmeVX111004();
	virtual void bfmeVX121004();
	virtual void bfmeVX131004();
	virtual void bfmeVX141004();
	virtual void bfmeVX151004();
	virtual void bfmeVX161004();
	virtual void bfmeVX171004();
	virtual void bfmeVX181004();
	virtual void bfmeVX191004();
	virtual void bfmeVX201004();
	virtual void bfmeVX211004();
	virtual void bfmeVX221004();
	virtual void bfmeVX231004();
	virtual void bfmeVX241004();
	virtual void bfmeVX251004();
	virtual void bfmeVX261004();
	virtual void bfmeVX271004();
	virtual void bfmeVX281004();
	virtual void bfmeVX291004();
	virtual void bfmeVX301004();
	virtual void bfmeVX311004();
	virtual void bfmeVX321004();
	virtual void bfmeVX331004();
	virtual void bfmeVX341004();
	virtual void bfmeVX351004();
	virtual void bfmeVX361004();
	virtual void bfmeVX371004();
	virtual void bfmeVX381004();
	virtual void bfmeVX391004();
	virtual void bfmeVX401004();
	virtual void bfmeVX411004();
	virtual void bfmeVX421004();
	virtual void bfmeVX431004();
	virtual void bfmeVX441004();
	virtual void bfmeVX451004();
	virtual void bfmeVX461004();
	virtual void bfmeVX471004();
	virtual void bfmeVX481004();
	virtual void bfmeVX491004();
	virtual void bfmeVX501004();
	virtual void bfmeVX511004();
	virtual void bfmeTail1004();
};

class BfmePreBXF;

class BfmeHold1004
{
public:
	unsigned char m_bfmePad[0x1fc];
	BfmePreBXF *m_bfmePre;
};

class BfmePreBXF
{
public:
	virtual void bfmeVX00();
	virtual void bfmeVX04();
	virtual void bfmeVX08();
	virtual void bfmeVX0c();
	virtual void bfmeVX10();
	virtual void bfmeVX14();
	virtual void bfmeVX18();
	virtual void bfmeVX1c();
	virtual void bfmeVX20();
	virtual void bfmeVX24();
	virtual void bfmeVX28();
	virtual void bfmeNotify();
};

class BfmeModuleBXF
{
public:
	virtual void bfmeVX00();
	virtual void bfmeVX04();
	virtual void bfmeVX08();
	virtual void bfmeVX0c();
	virtual void bfmeVX10();
	virtual void bfmeVX14();
	virtual void bfmeVX18();
	virtual void bfmeVX1c();
	virtual void bfmeVX20();
	virtual void bfmeVX24();
	virtual void bfmeVX28();
	virtual void bfmeVX2c();
	virtual void bfmeVX30();
	virtual void bfmeVX34();
	virtual void bfmeVX38();
	virtual void bfmeVX3c();
	virtual void bfmeVX40();
	virtual void bfmeVX44();
	virtual void bfmeVX48();
	virtual void bfmeVX4c();
	virtual void bfmeVX50();
	virtual void bfmeVX54();
	virtual void bfmeVX58();
	virtual void bfmeVX5c();
	virtual void bfmeNotify(int, int);
};

class BfmeThingBXF
{
public:
	void bfmeOnceBXF();
	void bfmeGoBXF();
	unsigned char m_bfmeHead[0xfc];
	BfmeHold1004 *m_bfmeHold;
	unsigned char m_bfmePad100[0x50];
	BfmeModuleBXF **m_bfmeModules;
	unsigned char m_bfmePad154[0x258];
	bool m_bfmeFlag;
};

void BfmeThingBXF::bfmeOnceBXF()
{
	BfmeHold1004 *hold = m_bfmeHold;
	if (!hold)
		return;

	reinterpret_cast<ClientRoot4120 *>(TheGameClient)->m_bfmeValue =
		*(int *)((char *)hold + 0x74);

	BfmePreBXF *pre = hold->m_bfmePre;
	if (pre)
		pre->bfmeNotify();

	if (!((const unsigned char *)TheWritableGlobalData)[0xa75])
		return;

	BfmeX1004 *x = (BfmeX1004 *)((Object *)hold)->unidentified_001BFE20();
	if (x)
		return x->bfmeTail1004();

	if (!((Object *)hold)->isLocallyControlled())
		return;

	int value = ((int (__fastcall *)(BfmeHold1004 *))d_001cabe0)(hold);

	BfmeModuleBXF *module = m_bfmeModules[0];
	if (module)
		module->bfmeNotify(1, value);
}

void BfmeThingBXF::bfmeGoBXF()
{
	if (!m_bfmeFlag)
	{
		m_bfmeFlag = true;
		bfmeOnceBXF();
	}
	// VC7.1 folds this member-pointer view to the retail direct call while
	// keeping the dump's defining symbol and the caller's thiscall ABI.
	union {
		void (*function)();
		void (BfmeThingBXF::*method)(int);
	} call;
	call.function = &d_0041a2e0;
	(this->*call.method)(0);
}
