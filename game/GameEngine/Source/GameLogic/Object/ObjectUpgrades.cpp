// cl: /DNDEBUG /MD /EHsc
// stlport

// The four Object bodies that own the completed-upgrade state:
//
//   hasUpgradeMask               0x001C59C0  is one upgrade bit set?
//   bfmeMarkUpgradeCompleted     0x001C5B90  set one bit, then re-run the modules
//   bfmeRefreshCompletedUpgrades 0x001C48B0  re-fire every already-granted upgrade
//   bfmeResetAllUpgrades         0x001C36B0  clear the mask, reset every module
//
// They sat one to a file with four disagreeing accounts of Object.  Retail
// settles every one of them:
//
//   +0x1F0  m_behaviors                 read by refresh/reset (`mov [esi+0x1f0]`)
//   +0x1FC  m_contain                   read by hasUpgradeMask
//   +0x224  m_objectUpgradesCompleted   indexed by mask/set, cleared by reset
//   +0x23C  m_team                      read by refresh
//
// The mask's width was the loudest disagreement: markUpgradeCompleted spelled it
// `UnsignedInt[6]`, hasUpgradeMask `UnsignedInt[4]` and resetAllUpgrades
// `BitFlags<192>`.  192 bits is right, and retail proves it twice over -- reset
// zeroes exactly six dwords from +0x224, and m_team lands at +0x23C, which is
// +0x224 plus 24 bytes with nothing in between.  That is also the upstream
// member order (Object.h puts m_team immediately after m_objectUpgradesCompleted),
// so the two independent facts agree.
//
// The second disagreement was the delegate hasUpgradeMask asks first.  That file
// called it `BfmeUpgradeDelegate` at +0x1FC and gave it 27 slots.  It is
// m_contain: three other Object bodies read the same +0x1FC as
// ContainModuleInterface, and applyAttributeModifier, bfmeGetHordeMemberCount and
// hasUpgradeMask all call its slot 26 (+0x68) and then use what comes back.  One
// virtual has one return type, so those three reach the SAME interface -- it is
// named HordeContainInterface here and in ObjectContainQueries.cpp because slot
// 84 (getHordeMemberCount) is the only slot whose meaning retail pins down.
// hasUpgradeMask's use of it is slot 42 (+0xA8): ask the horde first, fall back to
// this object's own bit.
//
// Third, refresh and reset each named the interface behind a behaviour module's
// +0x0C sub-object differently (`BehaviorModuleInterface` vs
// `BFMEBehaviorUpgradeShim`) and each named the upgrade module it returns
// differently.  One of each below.

#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

class BehaviorModule;
class Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer() const;
};

struct AffectedByUpgradeMask
{
	UnsignedInt m_bits[6];

	AffectedByUpgradeMask() {}
	__forceinline AffectedByUpgradeMask(const AffectedByUpgradeMask &other)
	{
		for (UnsignedInt i = 0; i < 6; ++i)
			m_bits[i] = other.m_bits[i];
	}

	__forceinline AffectedByUpgradeMask &operator|=(const AffectedByUpgradeMask &other)
	{
		m_bits[0] |= other.m_bits[0];
		m_bits[1] |= other.m_bits[1];
		m_bits[2] |= other.m_bits[2];
		m_bits[3] |= other.m_bits[3];
		m_bits[4] |= other.m_bits[4];
		m_bits[5] |= other.m_bits[5];
		return *this;
	}

	__forceinline void set(UnsignedInt bit)
	{
		m_bits[bit >> 5] |= 1 << (bit & 31);
	}

	__forceinline Bool test(UnsignedInt bit) const
	{
		return (m_bits[bit >> 5] & (1 << (bit & 31))) != 0;
	}

	__forceinline void clear()
	{
		UnsignedInt *bits = m_bits;
		bits[0] = 0;
		bits[1] = 0;
		bits[2] = 0;
		bits[3] = 0;
		bits[4] = 0;
		bits[5] = 0;
	}
};

class Player
{
public:
	AffectedByUpgradeMask getCompletedUpgradeMask() const
	{
		return m_completedUpgrades;
	}

private:
	unsigned char m_unmodelled000[0x8c];
	AffectedByUpgradeMask m_completedUpgrades;
};

// The upgrade module every upgrade-bearing behaviour hands back.  The class name
// is not free: targets/game/reverse/functions.csv pins the reset helper below as
// ?Rva002D9A70Invoke@@YAXPAVRva002D9A70Object@@@Z, and that spelling is what makes
// its REL32 resolve, so the readable name is an alias rather than the definition.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class Rva002D9A70Object
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;	// slot 0
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void forceRefreshUpgrade() = 0;		// slot 5, +0x14
};

typedef Rva002D9A70Object UpgradeModuleInterface;

// Resets one upgrade module: its slots 7 (+0x1C) and 8 (+0x20), in that order.
void Rva002D9A70Invoke(Rva002D9A70Object *upgrade);

// Every BehaviorModule carries this interface at +0x0C, and both loops below
// reach it by that fixed displacement rather than by a cast the compiler knows
// about.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
	virtual void bfmeSlot2() = 0;
	virtual void bfmeSlot3() = 0;
	virtual void bfmeSlot4() = 0;
	virtual void bfmeSlot5() = 0;
	virtual void bfmeSlot6() = 0;
	virtual void bfmeSlot7() = 0;
	virtual void bfmeSlot8() = 0;
	virtual UpgradeModuleInterface *getUpgrade() = 0;	// slot 9, +0x24
};

// Reached through ContainModuleInterface slot 26; see ObjectContainQueries.cpp,
// which names the same interface for the two other Object bodies that ask for it.
class HordeContainInterface
{
public:
	virtual Bool bfmeSlot00() = 0; virtual Bool bfmeSlot01() = 0;
	virtual Bool bfmeSlot02() = 0; virtual Bool bfmeSlot03() = 0;
	virtual Bool bfmeSlot04() = 0; virtual Bool bfmeSlot05() = 0;
	virtual Bool bfmeSlot06() = 0; virtual Bool bfmeSlot07() = 0;
	virtual Bool bfmeSlot08() = 0; virtual Bool bfmeSlot09() = 0;
	virtual Bool bfmeSlot10() = 0; virtual Bool bfmeSlot11() = 0;
	virtual Bool bfmeSlot12() = 0; virtual Bool bfmeSlot13() = 0;
	virtual Bool bfmeSlot14() = 0; virtual Bool bfmeSlot15() = 0;
	virtual Bool bfmeSlot16() = 0; virtual Bool bfmeSlot17() = 0;
	virtual Bool bfmeSlot18() = 0; virtual Bool bfmeSlot19() = 0;
	virtual Bool bfmeSlot20() = 0; virtual Bool bfmeSlot21() = 0;
	virtual Bool bfmeSlot22() = 0; virtual Bool bfmeSlot23() = 0;
	virtual Bool bfmeSlot24() = 0; virtual Bool bfmeSlot25() = 0;
	virtual Bool bfmeSlot26() = 0; virtual Bool bfmeSlot27() = 0;
	virtual Bool bfmeSlot28() = 0; virtual Bool bfmeSlot29() = 0;
	virtual Bool bfmeSlot30() = 0; virtual Bool bfmeSlot31() = 0;
	virtual Bool bfmeSlot32() = 0; virtual Bool bfmeSlot33() = 0;
	virtual Bool bfmeSlot34() = 0; virtual Bool bfmeSlot35() = 0;
	virtual Bool bfmeSlot36() = 0; virtual Bool bfmeSlot37() = 0;
	virtual Bool bfmeSlot38() = 0; virtual Bool bfmeSlot39() = 0;
	virtual Bool bfmeSlot40() = 0; virtual Bool bfmeSlot41() = 0;
	virtual Bool bfmeHasUpgrade(UnsignedInt bit) = 0;	// slot 42, +0xA8
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual Bool bfmeSlot00() = 0; virtual Bool bfmeSlot01() = 0;
	virtual Bool bfmeSlot02() = 0; virtual Bool bfmeSlot03() = 0;
	virtual Bool bfmeSlot04() = 0; virtual Bool bfmeSlot05() = 0;
	virtual Bool bfmeSlot06() = 0; virtual Bool bfmeSlot07() = 0;
	virtual Bool bfmeSlot08() = 0; virtual Bool bfmeSlot09() = 0;
	virtual Bool bfmeSlot10() = 0; virtual Bool bfmeSlot11() = 0;
	virtual Bool bfmeSlot12() = 0; virtual Bool bfmeSlot13() = 0;
	virtual Bool bfmeSlot14() = 0; virtual Bool bfmeSlot15() = 0;
	virtual Bool bfmeSlot16() = 0; virtual Bool bfmeSlot17() = 0;
	virtual Bool bfmeSlot18() = 0; virtual Bool bfmeSlot19() = 0;
	virtual Bool bfmeSlot20() = 0; virtual Bool bfmeSlot21() = 0;
	virtual Bool bfmeSlot22() = 0; virtual Bool bfmeSlot23() = 0;
	virtual Bool bfmeSlot24() = 0; virtual Bool bfmeSlot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;	// slot 26, +0x68
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeTemplate
{
public:
	UnsignedInt getUpgradeIndex(void) const { return m_upgradeIndex; }

private:
	unsigned char m_unmodelled_00[0x20];
	UnsignedInt m_upgradeIndex;			// +0x20
};

class AffectedByUpgradeModuleInterface
{
public:
	virtual Bool bfmeSlot0() = 0;
	virtual void bfmeSlot1() = 0;
	virtual Bool wouldUpgrade(const AffectedByUpgradeMask &) const = 0;
	virtual void bfmeSlot3() = 0;
	virtual Bool isSubObjectsUpgrade() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <unsigned int NUMBITS>
class BitFlags
{
public:
	void clear() { m_bits.reset(); }

	// Both single-bit paths reach the raw words: retail computes bit >> 5 and
	// 1 << (bit & 31) itself and never calls into a bitset helper.
	Bool test(UnsignedInt bit) const
	{
		return (word(bit) & mask(bit)) != 0;
	}

	void set(UnsignedInt bit)
	{
		reinterpret_cast<UnsignedInt *>(&m_bits)[bit >> 5] |= mask(bit);
	}

private:
	static UnsignedInt mask(UnsignedInt bit) { return 1 << (bit & 31); }
	UnsignedInt word(UnsignedInt bit) const
	{
		return reinterpret_cast<const UnsignedInt *>(&m_bits)[bit >> 5];
	}

	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> UpgradeMaskType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Bool hasUpgradeMask(UnsignedInt bit) const;
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	void bfmeMarkUpgradeCompleted(const UpgradeTemplate *upgrade);
	void bfmeRefreshCompletedUpgrades();
	void bfmeResetAllUpgrades();

	void updateUpgradeModules(void);

private:
	unsigned char m_unmodelled000[0x1f0];
	BehaviorModule **m_behaviors;			// +0x1F0
	unsigned char m_unmodelled1f4[0x1fc - 0x1f4];
	ContainModuleInterface *m_contain;		// +0x1FC
	unsigned char m_unmodelled200[0x224 - 0x200];
	UpgradeMaskType m_objectUpgradesCompleted;	// +0x224
	Team *m_team;					// +0x23C
};

// ?hasUpgradeMask@Object@@QBE_NI@Z
//
// The delegate goes into a local first.  Reading the member straight into the
// test leaves the compiler holding it in eax and copying it into ecx for the
// call, and shifts which of esi and edi carries this.
Bool Object::hasUpgradeMask(UnsignedInt bit) const
{
	ContainModuleInterface *contain = m_contain;

	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();

		if (horde && horde->bfmeHasUpgrade(bit))
			return true;
	}

	return m_objectUpgradesCompleted.test(bit);
}

// ?affectedByUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z
Bool Object::affectedByUpgrade(const UpgradeTemplate *upgradeT) const
{
	Player *player = m_team ? m_team->getControllingPlayer() : 0;
	if (!player)
		return false;

	player = reinterpret_cast<Player *>(
		reinterpret_cast<unsigned char *>(player) + 0x8c);
	AffectedByUpgradeMask mask =
		*reinterpret_cast<const AffectedByUpgradeMask *>(player);
	mask |= *reinterpret_cast<const AffectedByUpgradeMask *>(
		&m_objectUpgradesCompleted);
	mask.set(upgradeT->getUpgradeIndex());

	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		BehaviorModuleInterface *behavior = reinterpret_cast<BehaviorModuleInterface *>(
			reinterpret_cast<unsigned char *>(*module) + 0xc);
		AffectedByUpgradeModuleInterface *upgrade =
			reinterpret_cast<AffectedByUpgradeModuleInterface *>(behavior->getUpgrade());
		if (upgrade && upgrade->wouldUpgrade(mask) && !upgrade->isSubObjectsUpgrade())
			return true;
	}
	return false;
}

// ?bfmeMarkUpgradeCompleted@Object@@QAEXPBVUpgradeTemplate@@@Z
//
// Distinct from canonical Object::giveUpgrade at 0x001C9F70, which also handles
// null input and the contain-module upgrade sink; the original public spelling of
// this smaller path has not survived.
void Object::bfmeMarkUpgradeCompleted(const UpgradeTemplate *upgrade)
{
	m_objectUpgradesCompleted.set(upgrade->getUpgradeIndex());
	updateUpgradeModules();
}

// ?bfmeRefreshCompletedUpgrades@Object@@QAEXXZ
void Object::bfmeRefreshCompletedUpgrades()
{
	if (m_team == 0 || m_team->getControllingPlayer() == 0)
		return;

	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		BehaviorModuleInterface *behavior =
			reinterpret_cast<BehaviorModuleInterface *>(
				reinterpret_cast<unsigned char *>(*module) + 0xc);
		UpgradeModuleInterface *upgrade = behavior->getUpgrade();
		if (upgrade != 0 && upgrade->isAlreadyUpgraded())
			upgrade->forceRefreshUpgrade();
	}
}

// ?bfmeResetAllUpgrades@Object@@QAEXXZ
//
// Clear the full object mask, then reset every upgrade-bearing behavior.
void Object::bfmeResetAllUpgrades()
{
	m_objectUpgradesCompleted.clear();

	for (BehaviorModule **module = m_behaviors; *module; ++module)
	{
		BehaviorModuleInterface *behavior =
			reinterpret_cast<BehaviorModuleInterface *>(
				reinterpret_cast<char *>(*module) + 0x0c);
		UpgradeModuleInterface *upgrade = behavior->getUpgrade();
		if (upgrade)
			Rva002D9A70Invoke(upgrade);
	}
}
