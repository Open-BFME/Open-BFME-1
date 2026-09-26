// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// readable body of ?parseWeaponTemplateSet@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z: game/GameEngine/Source/Common/Thing/ThingTemplate.cpp

#include <map>
#include <vector>
#include <bitset>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const void *);
};

class ThingTemplate;
class WeaponTemplate;

struct BfmeElemVKN
{
	unsigned char m_bytes[0xec];
};

template <int Count>
class BitFlags
{
public:
	_STL::bitset<Count> m_bits;

	BitFlags() {}
};

typedef BitFlags<17> WeaponSetFlags;
typedef BitFlags<192> KindOfMask;

class WeaponTemplateSet
{
public:
	WeaponTemplateSet()
	{
		clear();
	}

	void clear();
	void parseWeaponTemplateSet(INI *, const ThingTemplate *);

private:
	const ThingTemplate *m_thingTemplate;
	WeaponSetFlags m_types;
	const WeaponTemplate *m_template[4];
	unsigned int m_autoChooseMask[4];
	KindOfMask m_preferredAgainst[4];
	KindOfMask m_shareAgainst[4];
	unsigned char m_isReloadTimeShared;
	unsigned char m_isWeaponLockSharedAcrossSets;
};

template <class Value, class Key>
class SparseMatchFinder
{
public:
	void clear()
	{
		m_map.clear();
	}

private:
	struct MapHelper
	{
		bool operator()(const Key &, const Key &) const;
	};

	_STL::map<const Key, const Value *, MapHelper> m_map;
};

class ThingTemplate
{
protected:
	static void __cdecl parseWeaponTemplateSet(INI *, void *, void *, const void *);

private:
	unsigned char m_pad000[0x2f8];
	_STL::vector<BfmeElemVKN> m_weaponTemplateSets;
	SparseMatchFinder<WeaponTemplateSet, WeaponSetFlags> m_weaponTemplateSetFinder;
	unsigned char m_padAfterFinder[0x17a];
	unsigned char m_weaponsCopiedFromDefault;
};

// ?parseWeaponTemplateSet@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parseWeaponTemplateSet(INI *ini, void *instance,
	void *, const void *)
{
	ThingTemplate *self = static_cast<ThingTemplate *>(instance);
	if (self->m_weaponsCopiedFromDefault == 1)
	{
		self->m_weaponsCopiedFromDefault = false;
		self->m_weaponTemplateSets.clear();
	}

	__declspec(align(8)) WeaponTemplateSet weaponSet;
	weaponSet.parseWeaponTemplateSet(ini, self);
	self->m_weaponTemplateSets.push_back(*(BfmeElemVKN *)&weaponSet);
	self->m_weaponTemplateSetFinder.clear();
}
