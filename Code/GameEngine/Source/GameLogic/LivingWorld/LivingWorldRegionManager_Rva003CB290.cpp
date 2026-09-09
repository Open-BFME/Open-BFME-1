// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Retail 0x003CB290 (747 bytes).  The receiver is the LivingWorldRegionManager
// established by the 0x003C8880 constructor (vtable 0x010EE010 and name slot
// 0x003C88D0).  The GameClient callback at 0x003C2530 reaches this body through
// j_00028d08, and the body itself calls the matched manager member at 0x003C8B90.
// Its +4 region-holder pointer and holder+0x40 dispatcher are the same measured
// composition used by the manager's other members.  The method name remains
// address-derived: the callback does not provide a canonical source spelling.
//
// All string calls use the verified Rva003BAD00Owner ABI: AsciiString is passed
// by reference and the second argument is a 32-bit value.  The two generated
// manager routes are called through their existing ILT thunks with TU-local
// typed member-pointer views; no new pin, vtable, or alias is introduced.

#include "ascii_string.h"

class Glo012ED5C8Type
{
public:
	char m_pad00[0x8E];
	unsigned char m_flag8E;
	unsigned char m_flag8F;
};

extern Glo012ED5C8Type *TheWritableGlobalData;

class Glo012F1028Type
{
public:
	char m_pad00[0x34];
	void *m_at34;
	char m_pad38[0x40];
	unsigned char m_at78;
};

extern Glo012F1028Type *Glo012F1028;

class Rva003BF540
{
public:
	bool allowed();
	bool anyReady() const;
};

class Rva0060D480CampaignGate
{
public:
	bool isOpen() const;
};

class BfmeGameCW
{
};

extern BfmeGameCW *g_bfmeGameCW;

class Gen_00609320
{
public:
	unsigned char bfmeDisabled() const;
};

extern Gen_00609320 *g_bfmeStateDF;

class Rva003BAD00Owner
{
public:
	void notify08(const AsciiString &key, int value);
};

class BfmeW1108
{
public:
	void bfmeGo1108B();
};

extern void j_00016248();
extern void j_000483ba();

class LivingWorldRegionManager
{
public:
	void rva003CB290();
	void rva003C8B90();

private:
	void *m_vtable;
	void *m_regions;
	void *m_selectedRegion;
	int m_unmodelled0C;
	unsigned char m_enabled;
};

typedef void (LivingWorldRegionManager::*ManagerNoArgCall)();
typedef void (LivingWorldRegionManager::*ManagerIntCall)(int);

static __forceinline void callManagerNoArg(LivingWorldRegionManager *manager,
	void (*raw)())
{
	union
	{
		void (*plain)();
		ManagerNoArgCall member;
	} call;
	call.plain = raw;
	(manager->*call.member)();
}

static __forceinline void callManagerInt(LivingWorldRegionManager *manager,
	void (*raw)(), int value)
{
	union
	{
		void (*plain)();
		ManagerIntCall member;
	} call;
	call.plain = raw;
	(manager->*call.member)(value);
}

// ?rva003CB290@LivingWorldRegionManager@@QAEXXZ
void LivingWorldRegionManager::rva003CB290()
{
	void *regions = m_regions;
	if (regions == 0)
		return;

	Rva003BAD00Owner *owner =
		(Rva003BAD00Owner *)((char *)regions + 0x40);

	if (TheWritableGlobalData->m_flag8E == 0
		|| TheWritableGlobalData->m_flag8F != 0
		|| Glo012F1028->m_at34 != 0)
	{
		owner->notify08(AsciiString("MouseoverEffectFlareupOwned"), 1);
		owner->notify08(AsciiString("MouseoutEffectFlareupOwned"), 1);
		owner->notify08(AsciiString("MouseoverEffectFlareupContested"), 1);
		owner->notify08(AsciiString("MouseoutEffectFlareupContested"), 1);

		if (((Rva0060D480CampaignGate *)g_bfmeGameCW)->isOpen())
			rva003C8B90();
		callManagerInt(this, j_00016248, 0);

		((BfmeW1108 *)owner)->bfmeGo1108B();
		return;
	}

	if (!((Rva0060D480CampaignGate *)g_bfmeGameCW)->isOpen()
		|| !((Rva003BF540 *)Glo012F1028)->allowed()
		|| g_bfmeStateDF->bfmeDisabled()
		|| Glo012F1028->m_at34 != 0
		|| ((Rva003BF540 *)Glo012F1028)->anyReady())
	{
		if (Glo012F1028->m_at78 != 0)
		{
			owner->notify08(AsciiString("FriendlyBordersEffect"), 1);
			owner->notify08(AsciiString("EnemyBordersEffect"), 1);
		}
		else
		{
			owner->notify08(AsciiString("MouseoverEffectFlareupOwned"), 1);
			owner->notify08(AsciiString("MouseoutEffectFlareupOwned"), 1);
			owner->notify08(AsciiString("MouseoverEffectFlareupContested"), 1);
			owner->notify08(AsciiString("MouseoutEffectFlareupContested"), 1);
		}

		((BfmeW1108 *)owner)->bfmeGo1108B();
		return;
	}

	callManagerNoArg(this, j_000483ba);
	callManagerInt(this, j_00016248, 1);
	((BfmeW1108 *)owner)->bfmeGo1108B();
}
