// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// readable body of ?parseArmorTemplateSet@ArmorTemplateSet@@: Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp
// readable body of ?parseArmorTemplateSet@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z: Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp

#include <map>
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *, const void *);
};

extern const unsigned char g_armorTemplateSetFieldParse[];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ArmorSet.h
class ArmorTemplateSet
{
public:
	ArmorTemplateSet() : m_types(0), m_template(0), m_fx(0) {}

	void parseArmorTemplateSet(INI *ini)
	{
		ini->initFromINI(this, g_armorTemplateSetFieldParse);
	}

private:
	void *m_types;
	void *m_template;
	void *m_fx;
};

template <int Count>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
private:
	unsigned int m_bits[(Count + 31) / 32];
};

template <class Value, class Key>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder
{
public:
	void clear() { m_map.clear(); }

private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
	struct MapHelper
	{
		bool operator()(const Key &, const Key &) const;
	};

	_STL::map<const Key, const Value *, MapHelper> m_map;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
protected:
	static void __cdecl parseArmorTemplateSet(INI *, void *, void *, const void *);

private:
	unsigned char m_pad000[0x310];
	_STL::vector<ArmorTemplateSet> m_armorTemplateSets;
	SparseMatchFinder<ArmorTemplateSet, BitFlags<11> > m_armorTemplateSetFinder;
	unsigned char m_padAfterFinder[0x161];
	unsigned char m_armorCopiedFromDefault;
};

// ?parseArmorTemplateSet@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parseArmorTemplateSet(INI *ini, void *instance,
	void *, const void *)
{
	ThingTemplate *self = static_cast<ThingTemplate *>(instance);
	if (self->m_armorCopiedFromDefault == 1)
	{
		self->m_armorCopiedFromDefault = false;
		self->m_armorTemplateSets.clear();
	}

	ArmorTemplateSet armorSet;
	armorSet.parseArmorTemplateSet(ini);
	self->m_armorTemplateSets.push_back(armorSet);
	self->m_armorTemplateSetFinder.clear();
}
