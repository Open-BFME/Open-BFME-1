// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME retail 0x0037E710.  The typed list<ExperienceLevel> sort at
// 0x0037F960 calls this merge specialization twice through ILT 0x00006BBD.
// Its 0xE0-byte nodes contain the proven 0xD8-byte ExperienceLevel at +8.
// The complete retail body resolves both values' Overridable chains and
// compares m_requiredExperience at ExperienceLevel+0x10.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

class Overridable
{
public:
	Overridable();
	virtual ~Overridable();

	const Overridable *friend_getFinalOverride() const
	{
		return m_nextOverride != 0
			? m_nextOverride->friend_getFinalOverride()
			: this;
	}

	const Overridable *getFinalOverride() const
	{
		// The two retail inlined walks leave their deeper recursion as the
		// const friend_getFinalOverride ILT 0x00048C61.
		return m_nextOverride != 0
			? m_nextOverride->friend_getFinalOverride()
			: this;
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

	bool operator<(const ExperienceLevel &that) const
	{
		const ExperienceLevel *left = static_cast<const ExperienceLevel *>(
			getFinalOverride());
		const ExperienceLevel *right = static_cast<const ExperienceLevel *>(
			that.getFinalOverride());

		if (left == 0 || right == 0)
			return false;

		return left->m_requiredExperience < right->m_requiredExperience;
	}

private:
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

namespace _STL
{

template void _S_merge<ExperienceLevel, allocator<ExperienceLevel>,
	less<ExperienceLevel> >(
	list<ExperienceLevel, allocator<ExperienceLevel> > &left,
	list<ExperienceLevel, allocator<ExperienceLevel> > &right,
	less<ExperienceLevel> compare);

}
