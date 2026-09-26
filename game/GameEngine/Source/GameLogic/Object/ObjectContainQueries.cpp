// cl: /DNDEBUG /MD /EHsc

// The five small Object bodies that answer a question by asking something else:
//
//   applyAttributeModifier         0x001C1DA0  contain slot 26, then its slot 108
//   getAttributeModifierMultiplier 0x001BFDD0  the AttributeModifierPoolUpdate module
//   findAttributeModifierPoolUpdate 0x001BF830 that module's one-time lookup
//   bfmeGetHordeMemberCount        0x001BFDF0  contain slot 26, then its slot 84
//   bfmeGetCrewSpeedMultiplier     0x001BF020  contain slot 48
//
// All five read one member and no other: m_contain at +0x1FC (three of them) or
// nothing at all (the two that go through the module lookup).  They sat in five
// files, and the three that call the contain module gave the SAME interface three
// unrelated names and three different lengths:
//
//   applyAttributeModifier   `AttributeModifierRedirect`  109 slots
//   bfmeGetHordeMemberCount  `HordeContainInterface`       85 slots
//   hasUpgradeMask           `BfmeUpgradeSource`           43 slots
//
// One virtual has one return type, so all three reach the same class: each calls
// m_contain's slot 26 (+0x68) and then uses what comes back, at +0x1B0, +0x150
// and +0xA8 -- slots 108, 84 and 42 of one interface.  ObjectUpgrades.cpp names
// the same interface for hasUpgradeMask and ObjectDamageAndWeapons.cpp for slot
// 35.
//
// What slot 26 returns is settled, and the evidence is written out in
// ObjectTeamAndPlayer.cpp: HordeContain's ContainModuleInterface slot 26 is a
// null-guarded SELF-CAST (body 0x00230730, `lea eax,[ecx+0xC4]`) to a second
// interface on the same contain module at +0xE4, whose vtable (0x010AE8E0) runs
// to at least 129 entries and holds every slot these bodies call.  Object's own
// vtable has 28, so it was never that; OpenContain's slot 26 points at the shared
// abstract stub, which is the "I am not a horde contain" answer.
//
// HordeContainInterface is still a reconstructed NAME -- slot 84 taking a Bool and
// returning a count is what suggests it -- so it lives in the sources and not in
// any decorated row.
//
// The contain module itself was spelled three ways too -- empty, 26 slots and 49
// slots -- because each file declared only as far as the slot it needed.  One
// declaration here runs to slot 48, the furthest any of them reaches.

typedef int Int;
typedef bool Bool;
typedef float Real;

enum NameKeyType {};

class Module;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
struct AsciiStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	unsigned int length() const
	{
		return m_data ? m_data->m_length : 0;
	}

	AsciiStringData *m_data;
};

// Named by its own module-name key literal, which findAttributeModifierPoolUpdate
// below hands to the name-key generator, and by that class's matched
// getModuleNameKey.  The class name is load-bearing: it is inside the mangled
// name of the finder itself.
class AttributeModifierPoolUpdate
{
public:
	Bool applyAttributeModifier(const AsciiString &name, Int duration);
	Bool getAttributeModifierBonus(Int which, Real *out);
	Bool getAttributeModifierMultiplier(Int which, Real *out);
};

#define BFME_SLOT(N) virtual Int bfmeSlot##N() = 0

// The one interface ContainModuleInterface's slot 26 hands back.  Only slot 84 is
// identified; 42 and 108 are numbered from the displacements their callers use.
class HordeContainInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29);
	BFME_SLOT(30); BFME_SLOT(31); BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34);
	BFME_SLOT(35); BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41);
	// slot 42, +0xA8 -- ObjectUpgrades.cpp calls it from hasUpgradeMask
	virtual Bool bfmeHasUpgrade(unsigned int bit) = 0;
	BFME_SLOT(43); BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51); BFME_SLOT(52);
	BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55); BFME_SLOT(56); BFME_SLOT(57);
	BFME_SLOT(58); BFME_SLOT(59); BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62);
	BFME_SLOT(63); BFME_SLOT(64); BFME_SLOT(65); BFME_SLOT(66); BFME_SLOT(67);
	BFME_SLOT(68); BFME_SLOT(69); BFME_SLOT(70); BFME_SLOT(71); BFME_SLOT(72);
	BFME_SLOT(73); BFME_SLOT(74); BFME_SLOT(75); BFME_SLOT(76); BFME_SLOT(77);
	BFME_SLOT(78); BFME_SLOT(79); BFME_SLOT(80); BFME_SLOT(81); BFME_SLOT(82);
	BFME_SLOT(83);
	// slot 84, +0x150
	virtual Int getHordeMemberCount(Bool countRiders) const = 0;
	BFME_SLOT(85); BFME_SLOT(86); BFME_SLOT(87); BFME_SLOT(88); BFME_SLOT(89);
	BFME_SLOT(90); BFME_SLOT(91); BFME_SLOT(92); BFME_SLOT(93); BFME_SLOT(94);
	BFME_SLOT(95); BFME_SLOT(96); BFME_SLOT(97); BFME_SLOT(98); BFME_SLOT(99);
	BFME_SLOT(100); BFME_SLOT(101); BFME_SLOT(102); BFME_SLOT(103);
	BFME_SLOT(104); BFME_SLOT(105); BFME_SLOT(106); BFME_SLOT(107);
	// slot 108, +0x1B0
	virtual void applyAttributeModifier(const AsciiString &name, Bool unknown, Int duration) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25);
	// slot 26, +0x68
	virtual HordeContainInterface *getHordeContainInterface() = 0;
	BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35); BFME_SLOT(36);
	BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39); BFME_SLOT(40); BFME_SLOT(41);
	BFME_SLOT(42); BFME_SLOT(43); BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46);
	BFME_SLOT(47);
	// slot 48, +0xC0.  OpenContain returns 1.0; SiegeEngineContain,
	// RiderChangeContain and HordeSiegeEngineContain scale by the crew count.
	virtual Real bfmeGetCrewSpeedMultiplier() const = 0;
};

#undef BFME_SLOT

#define OBJECT_TU_MEMBERS \
	Bool applyAttributeModifier(const AsciiString &name, Int duration); \
	Bool getAttributeModifierBonus(Int which, Real *out) const; \
	Bool getAttributeModifierMultiplier(Int which, Real *out) const; \
	Int bfmeGetHordeMemberCount() const; \
	Real bfmeGetCrewSpeedMultiplier() const; \
	protected: \
	Module *findModule(NameKeyType key) const; \
	private: \
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
#include "object.h"

// ?findAttributeModifierPoolUpdate@Object@@ABEPAVAttributeModifierPoolUpdate@@XZ
//
// The function-local static is what puts an EH frame on this body; the other four
// have none.
AttributeModifierPoolUpdate *Object::findAttributeModifierPoolUpdate() const
{
	static NameKeyType key_AttributeModifierPoolUpdate =
		TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return reinterpret_cast<AttributeModifierPoolUpdate *>(findModule(key_AttributeModifierPoolUpdate));
}

// ?applyAttributeModifier@Object@@QAE_NABVAsciiString@@H@Z
//
// A one-character name is refused outright; then the horde, if there is one,
// takes the modifier for the whole horde and this object's own pool never sees
// it.
Bool Object::applyAttributeModifier(const AsciiString &name, Int duration)
{
	if (name.length() == 1)
		return false;

	ContainModuleInterface *contain = m_contain;
	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde)
		{
			horde->applyAttributeModifier(name, false, duration);
			return true;
		}
	}

	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool)
	{
		Bool applied = pool->applyAttributeModifier(name, duration);
		return applied ? true : false;
	}
	return false;
}

// ?getAttributeModifierMultiplier@Object@@QBE_NHPAM@Z
//
// No module, no multiplier; otherwise the selector and the output pointer are
// tail-forwarded to the pool's accumulator.  The selector enum spelling is not
// recoverable from retail, so Int describes only what the bytes establish.
Bool Object::getAttributeModifierMultiplier(Int which, Real *out) const
{
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool == 0)
		return false;
	return pool->getAttributeModifierMultiplier(which, out);
}

// ?getAttributeModifierBonus@Object@@QBE_NHPAM@Z
Bool Object::getAttributeModifierBonus(Int which, Real *out) const
{
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (pool == 0)
		return false;
	return pool->getAttributeModifierBonus(which, out);
}

// ?bfmeGetHordeMemberCount@Object@@QBEHXZ
//
// The retail method and interface spellings are unrecovered.  The bytes prove
// both virtual slots, the false argument, and standalone objects counting as 1.
Int Object::bfmeGetHordeMemberCount() const
{
	ContainModuleInterface *contain = m_contain;
	if (contain != 0)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde != 0)
			return horde->getHordeMemberCount(false);
	}

	return 1;
}

// ?bfmeGetCrewSpeedMultiplier@Object@@QBEMXZ
//
// A no-argument thiscall body does not encode cv-qualification; const records the
// observed query-only behaviour rather than symbol metadata.
Real Object::bfmeGetCrewSpeedMultiplier() const
{
	ContainModuleInterface *contain = m_contain;
	if (contain == 0)
		return 1.0f;
	return contain->bfmeGetCrewSpeedMultiplier();
}
