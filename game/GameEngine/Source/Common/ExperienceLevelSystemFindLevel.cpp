// ExperienceLevelSystem::findLevel, BFME retail 0x0037FF80 (315 bytes).
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
//
// The matched ScriptActions::doTeamGiveExperienceLevel at 0x002F5760 and
// ExperienceLevelSystem member at 0x00380790 both load
// TheExperienceLevelSystem into ECX, pass a const AsciiString reference, and
// call ILT 0x000335D2; that thunk is an E9 to this complete retail body.  The
// returned pointer is consumed as the real 0xD8-byte ExperienceLevel (not the
// old prefix-only BfmeExperienceLevelDefinition surrogate).
//
// The map/list ownership and layout are independently fixed by the matched
// ExperienceLevel constructor, copy constructor, destructor, parser table
// 0x010EAB48, and the typed list sort/merge family.  The map's begin call is
// ILT 0x00019B37 -> body 0x0037EBB0.  That complete body returns the genuine
// STLport hash iterator { node, owner }; each mapped value at node+8 is an
// owning list whose 0xE0-byte nodes contain ExperienceLevel at +8.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>
#include <vector>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef float Real;

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

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

	int compare(const AsciiString &that) const
	{
		const Int thatLength = that.m_data ? that.m_data->m_length : 0;
		const char *thatText = that.m_data ? that.m_data->m_text : g_bfmeEmptyAscii;
		const Int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : g_bfmeEmptyAscii;
		const Int result = memcmp(thisText, thatText,
			(UnsignedInt)(thisLength < thatLength ? thisLength : thatLength));
		if (result != 0)
			return result;
		return thisLength - thatLength;
	}

private:
	BfmeAsciiStringData *m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

class Overridable
{
public:
	Overridable();
	virtual ~Overridable();

	Overridable *friend_getFinalOverride();

	Overridable *friend_getNextOverride()
	{
		return m_nextOverride;
	}

protected:
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
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
	ExperienceLevel *findLevel(const AsciiString &name);

private:
	unsigned char m_subsystemHead[8];
	ExperienceLevelMap m_levels;
};

ExperienceLevel *ExperienceLevelSystem::findLevel(const AsciiString &name)
{
	ExperienceLevelMap::iterator mapBegin = m_levels.begin();
	for (ExperienceLevelMap::iterator mapIt = mapBegin;
		mapIt != m_levels.end(); ++mapIt)
	{
		ExperienceLevelList &levels = mapIt->second;
		for (ExperienceLevelList::iterator levelIt = levels.begin();
			levelIt != levels.end(); ++levelIt)
		{
			if (levelIt->m_name == name)
			{
				ExperienceLevel *level = &(*levelIt);
				// This is the real recursive Overridable operation, exposed as
				// its first two source-level steps because retail inlines those
				// two loads and leaves only the deeper recursion as ILT
				// 0x00048C61 -> Overridable::friend_getFinalOverride at 0x00097880.
				// If the first override is final, it is the answer; the old bank
				// incorrectly returned null on that path.
				Overridable *next = level->friend_getNextOverride();
				if (next != 0)
				{
					Overridable *final = next->friend_getNextOverride();
					if (final == 0)
						return static_cast<ExperienceLevel *>(next);
					return static_cast<ExperienceLevel *>(
						final->friend_getFinalOverride());
				}
				return level;
			}
		}
	}

	return 0;
}
