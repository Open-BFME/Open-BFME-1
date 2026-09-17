// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME retail 0x00380270.  The sole caller is the ExperienceLevel INI parser
// at 0x00382460: after constructing an override, parsing it with the proven
// ExperienceLevel field table 0x010EAB48, and linking it to the existing
// definition, the caller passes that ExperienceLevel to this system member.
// The body hashes ExperienceLevel::m_name, finds the existing
// list<ExperienceLevel> mapped by that key, and sorts the list.  STLport's
// empty less<ExperienceLevel> is why the generated call transports the level
// pointer as an otherwise-unused second dword.  Retail call +0x5D uses ILT
// 0x0000F8B7, whose E9 route reaches the 394-byte body at 0x0037F960; this
// genuine typed specialization independently compiles to that full body.
// Its retail merge route 0x00006BBD -> 0x0037E710 walks Overridable::+4 on
// both elements and compares the final ExperienceLevel's
// m_requiredExperience at +0x10.  Its clear route 0x0004278A -> 0x0037DCA0
// invokes the virtual destructor of each value at node+8.  Those complete
// helper bodies rule out the old padded basic_string identity.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern const char g_bfmeEmptyAscii[];

struct BfmeAsciiStringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	AsciiString();
	AsciiString(const AsciiString &that);
	~AsciiString();

	const char *str() const
	{
		return m_data != 0 ? m_data->m_text : g_bfmeEmptyAscii;
	}

private:
	BfmeAsciiStringData *m_data;
};

class Overridable
{
public:
	Overridable();
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();

protected:
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	RadiusDecalTemplate(const RadiusDecalTemplate &that);
	~RadiusDecalTemplate();

private:
	AsciiString m_name;
	AsciiString m_secondName;
	Int m_shadowType;
	Real m_minOpacity;
	Real m_maxOpacity;
	Real m_opacityThrobTime;
	UnsignedInt m_color;
	Bool m_onlyVisibleToOwningPlayer;
	UnsignedInt m_unmodelled20;
	UnsignedInt m_unmodelled24;
	UnsignedInt m_unmodelled28;
	UnsignedInt m_unmodelled2c;
};

struct ModelConditionFlags
{
	UnsignedInt m_bits[10];
};

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

struct LevelUpFXInfo
{
	const void *fx;
	AsciiString boneName;
};

typedef _STL::vector<AsciiString> AsciiStringVector;
typedef _STL::vector<LevelUpFXInfo> LevelUpFXVector;

class ExperienceLevel : public Overridable
{
public:
	ExperienceLevel();
	ExperienceLevel(const ExperienceLevel &that);
	~ExperienceLevel();

	bool operator<(const ExperienceLevel &that) const;

private:
	friend class ExperienceLevelSystem;

	AsciiString m_name;
	Int m_requiredExperience;
	Int m_experienceAward;
	Int m_experienceAwardOwnGuysDie;
	AsciiStringVector m_targetNames;
	AsciiStringVector m_attributeModifiers;
	LevelUpFXVector m_levelUpFx;
	Int m_levelUpOCL;
	AsciiStringVector m_upgrades;
	ModelConditionFlags m_modelConditionState;
	RadiusDecalTemplate m_selectionDecal;
	Bool m_showLevelUpTint;
	RGBColor m_levelUpTintColor;
	Int m_levelUpTintPreColorTime;
	Int m_levelUpTintPostColorTime;
	Int m_levelUpTintSustainColorTime;
	Real m_levelUpTintFrequency;
	Real m_levelUpTintAmplitude;
	Int m_rank;
	Bool m_informUpdateModule;
	Bool m_singlePlayerOnly;
	Bool m_multiPlayerOnly;
	Int m_emotionType;
};

typedef char ExperienceLevelSizeMustBeD8[
	sizeof(ExperienceLevel) == 0xD8 ? 1 : -1];

typedef _STL::list<ExperienceLevel> ExperienceLevelList;
typedef _STL::pair<const Int, ExperienceLevelList> ExperienceLevelMapPair;
typedef _STL::hash_map<Int, ExperienceLevelList, _STL::hash<Int>,
	_STL::equal_to<Int>, _STL::allocator<ExperienceLevelMapPair> > ExperienceLevelMap;

class ExperienceLevelSystem
{
public:
	void rva00380270(ExperienceLevel *level);

private:
	unsigned char m_subsystemHead[8];
	ExperienceLevelMap m_levels;
};

void ExperienceLevelSystem::rva00380270(ExperienceLevel *level)
{
	const Int key = (Int)TheNameKeyGenerator->nameToKey(level->m_name.str());
	ExperienceLevelMap::iterator found = m_levels.find(key);
	if (found != m_levels.end())
		found->second.sort();
}
