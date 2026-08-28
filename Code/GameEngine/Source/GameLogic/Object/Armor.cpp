// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/namekeygenerator /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// ArmorStore -- the subsystem SubsystemLegend.ini feeds Armor.ini to. Ported
// from the Zero Hour reference (GeneralsMD/.../GameLogic/Object/Armor.cpp)
// against the NameKeyGenerator shim, because this TU needs the same AsciiString
// ABI that file established: an inline str() and an out-of-line release.
//
// parseArmorDefinition is what BFME's INI block table registers for the "Armor"
// keyword: a static node in .data holds {next, "Armor", &parse} and its parse
// slot points at 0x001B09B0. That binding is what identified this TU.
#include "PreRTS.h"
#include "Common/NameKeyGenerator.h"
#include "Common/STLTypedefs.h"

// BFME replaced Zero Hour's damage list wholesale. The 23 names below are read
// straight out of the scanIndexList table at 0x012ACC70 (NULL-terminated at
// [23]), and they are exactly the keys an Armor block accepts besides the
// "Default" wildcard. Three independent counts agree on 23: that table, the 23
// stores clear() emits at +0x00..+0x58, and the "Default" branch of
// parseArmorCoefficients, which writes those same 23 slots and stops.
enum DamageType
{
	DAMAGE_FORCE = 0,
	DAMAGE_CRUSH,
	DAMAGE_SLASH,
	DAMAGE_PIERCE,
	DAMAGE_SIEGE,
	DAMAGE_STRUCTURAL,
	DAMAGE_FLAME,
	DAMAGE_HEALING,
	DAMAGE_UNRESISTABLE,
	DAMAGE_WATER,
	DAMAGE_PENALTY,
	DAMAGE_FALLING,
	DAMAGE_TOPPLING,
	DAMAGE_REFLECTED,
	DAMAGE_PASSENGER,
	DAMAGE_MAGIC,
	DAMAGE_CHOP,
	DAMAGE_HERO,
	DAMAGE_SPECIALIST,
	DAMAGE_URUK,
	DAMAGE_HERO_RANGED,
	DAMAGE_FLY_INTO,
	DAMAGE_UNDEFINED,

	DAMAGE_NUM_TYPES		// keep last
};

extern const char *TheDamageNames[];		// 0x012ACC70

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfoInput
{
	char pad[12];
	DamageType m_damageType;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Armor.h
class ArmorTemplate
{
public:
	ArmorTemplate();
	void clear();
	Real getDamageCoefficient(const DamageInfoInput &damageInfo) const;
	static void parseArmorCoefficients( INI* ini, void *instance, void *store, const void* userData );
	static void parseDamageScalar( INI* ini, void *instance, void *store, const void* userData );
private:
	Real m_damageCoefficient[DAMAGE_NUM_TYPES];		// +0x00 .. +0x58
	Real m_damageScalar;							// +0x5C
	friend class ArmorStore;
};

Real ArmorTemplate::getDamageCoefficient(const DamageInfoInput &damageInfo) const
{
	return m_damageCoefficient[damageInfo.m_damageType];
}

ArmorTemplate::ArmorTemplate()
{
	clear();
}

// Retail always inlines this, so there is no standalone body to claim. It is
// here because parseArmorDefinition carries it, and it is what proves
// m_damageScalar is a separate member rather than a 24th coefficient: the loop
// stores through a base register copied out of the map lookup, while the
// trailing scalar store reuses the lookup's own result register.
void ArmorTemplate::clear()
{
	for (Int i = 0; i < DAMAGE_NUM_TYPES; ++i)
		m_damageCoefficient[i] = 1.0f;
	m_damageScalar = 1.0f;
}

// ?parseArmorCoefficients@ArmorTemplate@@SAXPAVINI@@PAX1PBX@Z
// One line of an Armor block: "<DamageType> <Percent>%". "Default" fills every
// coefficient; anything else is looked up positionally in TheDamageNames and
// overwrites that one slot. BFME resolves the name with INI::scanIndexList,
// where Zero Hour used the DamageTypeFlags bit lookup.
/*static*/ void ArmorTemplate::parseArmorCoefficients( INI* ini, void *instance, void * /* store */, const void * /* userData */ )
{
	ArmorTemplate* self = (ArmorTemplate*) instance;

	const char* damageName = ini->getNextToken();
	Real pct = INI::scanPercentToReal(ini->getNextToken());

	if (stricmp(damageName, "Default") == 0)
	{
		for (Int i = 0; i < DAMAGE_NUM_TYPES; i++)
		{
			self->m_damageCoefficient[i] = pct;
		}
		return;
	}

	DamageType dt = (DamageType)INI::scanIndexList(damageName, TheDamageNames);
	self->m_damageCoefficient[dt] = pct;
}

// ?parseDamageScalar@ArmorTemplate@@SAXPAVINI@@PAX1PBX@Z
// The "DamageScalar" field, which BFME added and Zero Hour has no counterpart
// for: a flat multiplier at +0x5C that sits alongside the per-type coefficients.
/*static*/ void ArmorTemplate::parseDamageScalar( INI* ini, void *instance, void * /* store */, const void * /* userData */ )
{
	ArmorTemplate* self = (ArmorTemplate*) instance;
	self->m_damageScalar = INI::scanPercentToReal(ini->getNextToken());
}

class ArmorStore;
extern ArmorStore *TheArmorStore;		// 0x012EF4E8

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Armor.h
class ArmorStore : public SubsystemInterface
{
public:
	void init() {}
	void reset() {}
	void update() {}
	const ArmorTemplate *findArmorTemplate(AsciiString name) const;
	static void parseArmorDefinition(INI *ini);
private:
	typedef std::hash_map< NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ArmorTemplateMap;
	ArmorTemplateMap m_armorTemplates;		// +0x08
};

// ?findArmorTemplate@ArmorStore@@QBEPBVArmorTemplate@@VAsciiString@@@Z
// nameToKey is called through the const char* overload, not the AsciiString
// one: retail inlines AsciiString::str() here (m_text ? m_text+8 : "") and
// passes the result, which is why this reads name.str() explicitly.
const ArmorTemplate *ArmorStore::findArmorTemplate(AsciiString name) const
{
	NameKeyType namekey = TheNameKeyGenerator->nameToKey(name.str());
	ArmorTemplateMap::const_iterator it = m_armorTemplates.find(namekey);
	if (it == m_armorTemplates.end())
		return NULL;
	return &(*it).second;
}

// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// The "Armor" INI block: name the armor, default every coefficient to 1.0, then
// let the field parser overwrite the ones the block lists.
/*static*/ void ArmorStore::parseArmorDefinition(INI *ini)
{
	static const FieldParse myFieldParse[] =
	{
		{ "DamageScalar", ArmorTemplate::parseDamageScalar, NULL, 0 },
		{ "Armor", ArmorTemplate::parseArmorCoefficients, NULL, 0 },
		{ NULL, NULL, NULL, 0 }
	};

	const char *c = ini->getNextToken();
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	ArmorTemplate& armorTmpl = TheArmorStore->m_armorTemplates[key];
	armorTmpl.clear();
	ini->initFromINI(&armorTmpl, myFieldParse);
}
