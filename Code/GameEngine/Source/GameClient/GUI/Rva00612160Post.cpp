typedef unsigned (__cdecl *FadeCallback)(float, bool);
unsigned fade00565170(float, bool);
unsigned fade0060F010(float, bool);
unsigned fade005651F0(float, bool);
extern unsigned fadeQueueKey;
// cl: /DNDEBUG
//
// Same holder/wrapper as PostLoadGameFadeSteps.cpp, then Mouse::setCursor(1),
// AptPalantir::hide(true), InGameUI::freeMessageResources (ILT 0x0001DC82 ->
// 0x0043CDC0), and a byte store on TheLivingWorldLogic+0x28+0x10.

struct LoadGameFadeSlot
{
	LoadGameFadeSlot(FadeCallback fn) : m_fn(fn) {}
	FadeCallback m_fn;
};

class LoadGameFadeWrapperHead
{
public:
	LoadGameFadeWrapperHead() throw() : m_refCount(0) {}
	virtual ~LoadGameFadeWrapperHead() {}
	int m_refCount;
};

class LoadGameFadeWrapper : public LoadGameFadeWrapperHead
{
public:
	__forceinline LoadGameFadeWrapper(const LoadGameFadeSlot &slot) throw()
		: m_slot(slot) {}
	virtual ~LoadGameFadeWrapper() {}
	virtual unsigned invoke(float a, bool b) { return m_slot.m_fn(a,b); }
	LoadGameFadeSlot m_slot;
};

class LoadGameFadeHolder
{
public:
	__forceinline LoadGameFadeHolder(LoadGameFadeSlot binding) throw()
	{
		m_ptr = new LoadGameFadeWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
	~LoadGameFadeHolder() { if (m_ptr != 0 && --m_ptr->m_refCount <= 0) delete m_ptr; }
	LoadGameFadeWrapper *m_ptr;
};

bool postTimedOp(LoadGameFadeHolder holder, unsigned *key);

typedef int Int;

class BfmeVirtualMouseSetCursor
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setCursor(Int cursor) = 0;
};

class AptPalantir
{
public:
	void hide(bool immediate);
};

class InGameUI
{
public:
	void freeMessageResources();
};

struct Rva00612160LwSub
{
	unsigned char pad[0x10];
	unsigned char flag;
};

class CampaignObject
{
public:
	unsigned char pad[0x28];
	Rva00612160LwSub *sub;
};

class Mouse;
extern Mouse *TheMouse;
extern AptPalantir *TheAptPalantir;
extern InGameUI *TheInGameUI;
extern CampaignObject *TheLivingWorldLogic;

void rva00612160Post()
{
	postTimedOp(
		LoadGameFadeSlot(&fade00565170),
		&fadeQueueKey);
	postTimedOp(
		LoadGameFadeSlot(&fade0060F010),
		&fadeQueueKey);
	postTimedOp(
		LoadGameFadeSlot(&fade005651F0),
		&fadeQueueKey);
	((BfmeVirtualMouseSetCursor *)TheMouse)->setCursor(1);
	TheAptPalantir->hide(true);
	TheInGameUI->freeMessageResources();
	TheLivingWorldLogic->sub->flag = 1;
}
