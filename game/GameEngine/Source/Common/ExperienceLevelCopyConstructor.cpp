// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME retail 0x00381B60.  The STLport node construction at 0x00381C30
// passes its 0xD8-byte value at node+8 to this copy constructor through ILT
// 0x00027084.  The same value layout is established by ExperienceLevel's
// matched default constructor, destructor, parser field table 0x010EAB48,
// and list copy/range-insert specializations.

#define _STLP_NO_EXCEPTIONS 1
#include <string.h>
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

class Overridable
{
protected:
	Overridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~Overridable();

	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();
	void operator=(const RadiusDecalTemplate &that);

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

#pragma comment(linker, "/alternatename:??4RadiusDecalTemplate@@QAEXABV0@@Z=??4Rva00458450@@QAEXABV0@@Z")

class UpgradeTemplate;

struct ModelConditionFlags
{
	ModelConditionFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

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

struct LevelUpFXVectorView
{
	LevelUpFXInfo *m_start;
	LevelUpFXInfo *m_finish;
	LevelUpFXInfo *m_endOfStorage;

	LevelUpFXInfo *begin()
	{
		return m_start;
	}

	LevelUpFXInfo *end()
	{
		return m_finish;
	}

	__forceinline LevelUpFXInfo *erase(
		LevelUpFXInfo *first, LevelUpFXInfo *last)
	{
		LevelUpFXInfo *source = last;
		LevelUpFXInfo *destination = first;
		int count = (int)(m_finish - last);
		while (count > 0)
		{
			*destination = *source;
			++source;
			++destination;
			--count;
		}

		LevelUpFXInfo *oldFinish = m_finish;
		for (LevelUpFXInfo *current = destination;
			current != oldFinish; ++current)
			current->~LevelUpFXInfo();
		m_finish = destination;
		return first;
	}

	__forceinline void clear()
	{
		erase(begin(), end());
	}
};

typedef std::vector<AsciiString> AsciiStringVector;
typedef std::vector<LevelUpFXInfo> LevelUpFXVector;
typedef std::vector<const UpgradeTemplate *> UpgradeVector;

class ExperienceLevel : public Overridable
{
public:
	ExperienceLevel(const ExperienceLevel &that);
	~ExperienceLevel();
	ExperienceLevel &operator=(const ExperienceLevel &that);

private:
	AsciiString m_name;
	Int m_requiredExperience;
	Int m_experienceAward;
	Int m_experienceAwardOwnGuysDie;
	AsciiStringVector m_targetNames;
	AsciiStringVector m_attributeModifiers;
	LevelUpFXVector m_levelUpFx;
	Int m_levelUpOCL;
	UpgradeVector m_upgrades;
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
	volatile Bool m_informUpdateModule;
	volatile Bool m_singlePlayerOnly;
	volatile Bool m_multiPlayerOnly;
	volatile Int m_emotionType;
};

typedef char ExperienceLevelSizeMustBeD8[
	sizeof(ExperienceLevel) == 0xD8 ? 1 : -1];

// The retail constructor first establishes every owning subobject, then uses
// ExperienceLevel::operator= at 0x00381690 to copy the complete value.  The
// scalar fields intentionally have no initializer: the assignment is their
// first write, exactly as in retail.
// Retail FuncInfo 0x0120BB24 has seven unwind states.  Its actions destroy,
// in construction order, Overridable, m_name, the four vectors, and
// m_selectionDecal; the compiled typed constructor produces the same state
// map and the same seven cleanup targets.
ExperienceLevel::ExperienceLevel(const ExperienceLevel &that)
	: m_name(),
	  m_targetNames(),
	  m_attributeModifiers(),
	  m_levelUpFx(),
	  m_upgrades(),
	  m_modelConditionState(),
	  m_selectionDecal()
{
	*this = that;
}

ExperienceLevel &ExperienceLevel::operator=(const ExperienceLevel &that)
{
	if (&that == this)
		return *this;

	m_name = that.m_name;
	m_requiredExperience = that.m_requiredExperience;
	m_experienceAward = that.m_experienceAward;
	m_experienceAwardOwnGuysDie = that.m_experienceAwardOwnGuysDie;
	m_targetNames = that.m_targetNames;
	m_selectionDecal = that.m_selectionDecal;
	m_levelUpTintColor = that.m_levelUpTintColor;
	m_levelUpOCL = that.m_levelUpOCL;
	m_modelConditionState = that.m_modelConditionState;
	m_selectionDecal = that.m_selectionDecal;
	m_showLevelUpTint = that.m_showLevelUpTint;
	AsciiStringVector *attributeModifiers = &m_attributeModifiers;
	m_levelUpTintPreColorTime = that.m_levelUpTintPreColorTime;
	m_levelUpTintPostColorTime = that.m_levelUpTintPostColorTime;
	m_levelUpTintSustainColorTime = that.m_levelUpTintSustainColorTime;
	m_levelUpTintFrequency = that.m_levelUpTintFrequency;
	m_levelUpTintAmplitude = that.m_levelUpTintAmplitude;
	m_rank = that.m_rank;
	m_informUpdateModule = that.m_informUpdateModule;
	m_singlePlayerOnly = that.m_singlePlayerOnly;
	m_multiPlayerOnly = that.m_multiPlayerOnly;
	m_emotionType = that.m_emotionType;
	_ReadWriteBarrier();
	attributeModifiers->erase(
		attributeModifiers->begin(), attributeModifiers->end());
	for (unsigned int i = 0; i < that.m_attributeModifiers.size(); ++i)
		attributeModifiers->push_back(that.m_attributeModifiers[i]);
	m_upgrades.clear();
	for (unsigned int i = 0; i < that.m_upgrades.size(); ++i)
		m_upgrades.push_back(that.m_upgrades[i]);
	((LevelUpFXVectorView *)&m_levelUpFx)->clear();
	for (unsigned int i = 0; i < that.m_levelUpFx.size(); ++i)
		m_levelUpFx.push_back(that.m_levelUpFx[i]);
	return *this;
}
