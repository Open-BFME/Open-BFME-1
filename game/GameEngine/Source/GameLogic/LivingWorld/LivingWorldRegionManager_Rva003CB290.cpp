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
// The Rva003BAD00Owner ledger definition takes two 32-bit arguments. The
// caller forwards each AsciiString address in its first argument. The two
// generated manager routes use their existing ILT thunks with TU-local
// typed member-pointer views; no new pin, vtable, or alias is introduced.

#include "ascii_string.h"

class Glo012ED5C8Type
{
public:
	char m_pad00[0x8E];
	unsigned char m_flag8E;
	unsigned char m_flag8F;
};

// Retail 0x012ED5C8 is GlobalData *TheWritableGlobalData
// (game/GameEngine/Source/Common/GlobalData.cpp); this TU keeps its own view of
// the two flags it reads and casts at the use.
class GlobalData;

extern GlobalData *TheWritableGlobalData;

static __forceinline Glo012ED5C8Type *localWritableGlobalData()
{
	return (Glo012ED5C8Type *)TheWritableGlobalData;
}

class Glo012F1028Type
{
public:
	char m_pad00[0x34];
	void *m_at34;
	char m_pad38[0x40];
	unsigned char m_at78;
};

// Canonical datum at 0x012F1028; keep the measured field view above.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva003BDEC0
{
public:
	bool allowed();
};

class Rva003BD830Owner
{
public:
	bool anyReady() const;
};

class Rva0060D480CampaignGate
{
public:
	bool isOpen() const;
};

// Canonical datum at 0x012F706C.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Gen_00609320
{
public:
	// The body returns int; this caller tests only AL, so narrow at the use.
	int bfmeDisabled() const;
};

// Canonical datum at 0x012F7048, defined in GameClient/LivingWorld.cpp.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

class Rva003BAD00Owner
{
public:
	void notify08(int key, int value);
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

	if (localWritableGlobalData()->m_flag8E == 0
		|| localWritableGlobalData()->m_flag8F != 0
		|| ((Glo012F1028Type *)TheLivingWorldLogic)->m_at34 != 0)
	{
		{
			AsciiString key("MouseoverEffectFlareupOwned");
			owner->notify08((int)&key, 1);
		}
		{
			AsciiString key("MouseoutEffectFlareupOwned");
			owner->notify08((int)&key, 1);
		}
		{
			AsciiString key("MouseoverEffectFlareupContested");
			owner->notify08((int)&key, 1);
		}
		{
			AsciiString key("MouseoutEffectFlareupContested");
			owner->notify08((int)&key, 1);
		}

		if (((Rva0060D480CampaignGate *)TheLivingWorldManager)->isOpen())
			rva003C8B90();
		callManagerInt(this, j_00016248, 0);

		((BfmeW1108 *)owner)->bfmeGo1108B();
		return;
	}

	if (!((Rva0060D480CampaignGate *)TheLivingWorldManager)->isOpen()
		|| !((Rva003BDEC0 *)TheLivingWorldLogic)->allowed()
		|| (unsigned char)((Gen_00609320 *)g_rva012F7048LivingWorld)->bfmeDisabled()
		|| ((Glo012F1028Type *)TheLivingWorldLogic)->m_at34 != 0
		|| ((Rva003BD830Owner *)TheLivingWorldLogic)->anyReady())
	{
		if (((Glo012F1028Type *)TheLivingWorldLogic)->m_at78 != 0)
		{
			{
				AsciiString key("FriendlyBordersEffect");
				owner->notify08((int)&key, 1);
			}
			{
				AsciiString key("EnemyBordersEffect");
				owner->notify08((int)&key, 1);
			}
		}
		else
		{
			{
				AsciiString key("MouseoverEffectFlareupOwned");
				owner->notify08((int)&key, 1);
			}
			{
				AsciiString key("MouseoutEffectFlareupOwned");
				owner->notify08((int)&key, 1);
			}
			{
				AsciiString key("MouseoverEffectFlareupContested");
				owner->notify08((int)&key, 1);
			}
			{
				AsciiString key("MouseoutEffectFlareupContested");
				owner->notify08((int)&key, 1);
			}
		}

		((BfmeW1108 *)owner)->bfmeGo1108B();
		return;
	}

	callManagerNoArg(this, j_000483ba);
	callManagerInt(this, j_00016248, 1);
	((BfmeW1108 *)owner)->bfmeGo1108B();
}
