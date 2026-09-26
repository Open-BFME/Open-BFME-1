// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// BFME retail 0x00381DF0.  The matched range-insert specialization at
// 0x00381D10 allocates 0xE0-byte nodes and copies a 0xD8-byte value through
// 0x00381B60.  That value installs ExperienceLevel's proven 0x010EA944
// vtable and has the same subobject layout as ExperienceLevel's matched
// default constructor and destructor.

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
protected:
	Overridable();
	virtual ~Overridable();

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
	UnsignedInt m_bits[ 10 ];
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

typedef std::vector<AsciiString> AsciiStringVector;
typedef std::vector<LevelUpFXInfo> LevelUpFXVector;

class ExperienceLevel : public Overridable
{
public:
	ExperienceLevel();
	ExperienceLevel( const ExperienceLevel &that );
	~ExperienceLevel();

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

typedef char ExperienceLevelSizeMustBeD8[ sizeof( ExperienceLevel ) == 0xD8 ? 1 : -1 ];

// Instantiate only the genuine copy constructor.  Instantiating the whole
// container would manufacture unrelated comparison-dependent list methods.
template std::list<ExperienceLevel>::list(
	const std::list<ExperienceLevel> &source );
