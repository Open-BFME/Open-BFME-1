// ?d_003caeb0@@YAXXZ
// partial score=0.9297 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
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

struct Coord3D;
class LivingWorldRegion;

class Rva003CAEB0State
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
	virtual void slot20(void *first, void *second) = 0;
};

extern int __cdecl Rva003C92A0(int first, int second);

class Rva003BAD00Owner
{
public:
	void notify04(const AsciiString &key, int value);
	void notify08(const AsciiString &key, int value);
	void notify0C(const AsciiString &key, const void *payload, int value);
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
	void rva003CAEB0();
	LivingWorldRegion *rva003C8160(Coord3D *position);

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

// The matched rva003CB290 caller sends its this pointer through ILT 0x000483BA.
// ?rva003CAEB0@LivingWorldRegionManager@@QAEXXZ
void LivingWorldRegionManager::rva003CAEB0()
{
	unsigned char *globalData = (unsigned char *)Glo012F1028;
	if (globalData[0x1c] == 0)
		return;

	unsigned int query[2];
	query[0] = *(unsigned int *)(globalData + 0x20);
	query[1] = *(unsigned int *)(globalData + 0x24);
	float position[3];
	((Rva003CAEB0State *)g_bfmeStateDF)->slot20(query, position);

	LivingWorldRegion *selected = rva003C8160((Coord3D *)position);
	LivingWorldRegion *previous = *(LivingWorldRegion **)((char *)this + 0x0c);
	if (selected == previous)
		return;

	Rva003BAD00Owner *owner =
		(Rva003BAD00Owner *)((char *)m_regions + 0x40);
	if (previous != 0)
	{
		owner->notify08(AsciiString("MouseoverEffectFlareupOwned"), 1);
		owner->notify08(AsciiString("MouseoutEffectFlareupOwned"), 1);

		int oldValue = *(int *)((char *)*(LivingWorldRegion **)(
			(char *)this + 0x0c) + 0xb4);
		if (Rva003C92A0(oldValue, oldValue) == 1)
		{
			owner->notify08(AsciiString("MouseoutEffectFlareupOwned"), 1);
			owner->notify0C(AsciiString("MouseoutEffectFlareupOwned"),
				(const void *)((char *)*(LivingWorldRegion **)(
					(char *)this + 0x0c) + 0x28), 1);
			owner->notify04(AsciiString("MouseoutEffectFlareupOwned"), 1);
		}
		else
		{
			owner->notify08(AsciiString("MouseoutEffectFlareupContested"), 1);
			owner->notify0C(AsciiString("MouseoutEffectFlareupContested"),
				(const void *)((char *)*(LivingWorldRegion **)(
					(char *)this + 0x0c) + 0x28), 1);
			owner->notify04(AsciiString("MouseoutEffectFlareupContested"), 1);
		}
	}

	if (selected != 0)
	{
		int newValue = *(int *)((char *)selected + 0xb4);
		if (Rva003C92A0(newValue, newValue) == 1)
		{
			owner->notify0C(AsciiString("MouseoverEffectFlareupOwned"),
				(const void *)((char *)selected + 0x28), 1);
			owner->notify04(AsciiString("MouseoverEffectFlareupOwned"), 0);
		}
		else
		{
			owner->notify0C(AsciiString("MouseoverEffectFlareupContested"),
				(const void *)((char *)selected + 0x28), 1);
			owner->notify04(AsciiString("MouseoverEffectFlareupContested"), 0);
		}
	}

	*(LivingWorldRegion **)((char *)this + 0x0c) = selected;
}
