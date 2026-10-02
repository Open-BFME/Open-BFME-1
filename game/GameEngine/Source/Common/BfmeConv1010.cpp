// Open-BFME5 conversions.

// Exact ledger spellings for the four retail callees. Keep the local layout
// views below: the subsystem headers do not expose these member declarations.
// The member-pointer calls preserve the retail thiscall ABI without defining
// another GameLogic or WeaponStore class.
extern "C" void __identifier("?destroyObject@GameLogic@@QAEXPAVObject@@@Z")();
extern "C" void __identifier("?onDelete@OpenContain@@UAEXXZ")();
extern "C" void __identifier("?loadAmmoNow@Weapon@@QAEXPBVObject@@@Z")();
extern "C" void __identifier("?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z")();

class BfmeItem1010;

// Retail global at 0x012F0898 is GameLogic *TheGameLogic (defined once in
// game_logic.cpp). This TU calls through a local view type, so keep the view
// and cast at the use; the global itself uses the canonical spelling.
class BfmeSink1010
{
};

class GameLogic;
extern GameLogic *TheGameLogic;

static inline BfmeSink1010 *localTheGameLogic(void)
{
	return reinterpret_cast<BfmeSink1010 *>(TheGameLogic);
}

struct BfmeNode1010
{
	BfmeNode1010 *m_bfmeNext;
	char m_bfmePad[4];
	BfmeItem1010 *m_bfmeItem;
};

class BfmeA1010
{
public:
	void bfmeGo1010A();

	char m_bfmePad[0x9bc];
	BfmeNode1010 *m_bfmeList;
};

void BfmeA1010::bfmeGo1010A()
{
	union {
		void (*function)();
		void (BfmeSink1010::*method)(BfmeItem1010 *);
	} destroy;
	destroy.function = &__identifier("?destroyObject@GameLogic@@QAEXPAVObject@@@Z");
	BfmeNode1010 *n = m_bfmeList->m_bfmeNext;

	while (n != m_bfmeList) {
		BfmeItem1010 *it = n->m_bfmeItem;

		n = n->m_bfmeNext;
		(localTheGameLogic()->*destroy.method)(it);
	}

	union {
		void (*function)();
		void (BfmeA1010::*method)();
	} finish;
	finish.function = &__identifier("?onDelete@OpenContain@@UAEXXZ");
	(this->*finish.method)();
}

struct BfmeOwner1010
{
	char m_bfmePad[0x74];
	int m_bfmeVal;
};

class BfmeHeld1010
{
public:
	virtual void bfmeRelease1010(int n);

	char m_bfmePad[4];
	int m_bfmeVal;
};

class BfmeMake1010
{
};

// Retail global at 0x012EF738 is EA's WeaponStore singleton, defined once in
// game/GameEngine/Source/GameLogic/Object/Weapon.cpp; this TU calls through its
// own BfmeMake1010 view, so the view is applied at the use and the global
// itself keeps the canonical spelling. Only ever used as a pointee, so a
// forward declaration is enough (the definition lives in
// Common/System/game_engine_subsystems.h).
class WeaponStore;

extern WeaponStore *TheWeaponStore;

class BfmeC1010
{
public:
	void bfmeGo1010C(void *a);

	char m_bfmePad[8];
	BfmeOwner1010 *m_bfmeOwner;
	char m_bfmePad2[0x14];
	BfmeHeld1010 *m_bfmeHeld;
};

void BfmeC1010::bfmeGo1010C(void *a)
{
	if (!a)
		return;

	BfmeHeld1010 *h = m_bfmeHeld;

	if (h)
		h->bfmeRelease1010(1);

	union {
		void (*function)();
		BfmeHeld1010 *(BfmeMake1010::*method)(void *, int) const;
	} allocate;
	allocate.function = &__identifier("?allocateNewWeapon@WeaponStore@@QBEPAVWeapon@@PBVWeaponTemplate@@W4WeaponSlotType@@@Z");
	m_bfmeHeld = (((const BfmeMake1010 *)TheWeaponStore)->*allocate.method)(a, 0);
	m_bfmeHeld->m_bfmeVal = m_bfmeOwner->m_bfmeVal;
	union {
		void (*function)();
		void (BfmeHeld1010::*method)(const BfmeOwner1010 *);
	} loadAmmo;
	loadAmmo.function = &__identifier("?loadAmmoNow@Weapon@@QAEXPBVObject@@@Z");
	(m_bfmeHeld->*loadAmmo.method)(m_bfmeOwner);
}
