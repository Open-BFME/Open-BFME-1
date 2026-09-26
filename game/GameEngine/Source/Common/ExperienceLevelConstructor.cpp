// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// ExperienceLevel default constructor, retail 0x00380AB0 (267 bytes).
//
// The parser at 0x00382460 allocates a 0xd8 record, calls this constructor,
// then initializes it with the ExperienceLevel field table at 0x010EAB48.
// The existing 0x00380C00 destructor walks the same Overridable-derived
// record: the name at +0x0c, four vector members through +0x4c, the
// ModelConditionFlags value at +0x50, and the 0x30-byte SelectionDecal at
// +0x78.  The ten-word model-condition value is the real 320-bit
// ModelConditionFlags layout, not storage inserted to shape the frame.

#include <vector>
#include <string.h>

#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;

// BFME's one-pointer AsciiString is the vendor WWLib wrapper around
// StringBase<char>, not a derived StringBase subobject.  The existing
// ascii_string.h/string_base.h declarations model the real Header as
// { int ref_count; unsigned short length; unsigned short capacity; data[1] }
// and implement AsciiString::~AsciiString as one releaseBuffer call.  Using
// that declaration here is material: making the wrapper privately derive from
// StringBase would make the compiler call StringBase::~StringBase after the
// AsciiString release, which is a fabricated double release and changes the
// nested cleanup lifetime.

// upstream layout: Common/Overridable.h.  The derived record's vtable is the
// one-slot table at 0x010EA944; the adjacent 0x010EA948 table belongs to
// ExperienceLevelSystem and is not this object.
class Overridable
{
protected:
	Overridable() : m_nextOverride(0), m_isOverride(false) {}
	virtual ~Overridable();

	Overridable *m_nextOverride;
	Bool m_isOverride;
};

// upstream layout: GameClient/RadiusDecal.h.  BFME's member is 0x30 bytes;
// its real constructor is the pinned ILT 0x00029C71 -> body 0x00458830.
// The two StringBase-backed members and the four BFME tail words are present
// in the matched RadiusDecalTemplate constructor/dtor; they are declared here
// so the parent records the real subobject size/lifetime rather than an empty
// fake base.  The parent constructor does not destroy this subobject from its
// own unwind map: it sets state 5 immediately before the child ctor, and there
// are no later throwing object constructions.
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
	ModelConditionFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}
	UnsignedInt m_bits[10];
};

struct RGBColor
{
	// upstream layout and setFromInt semantics:
	// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h.
	// The retail constructor
	// uses setFromInt(0) for this default tint; keeping the real inline helper
	// also preserves the compiler's sequenced tail stores.
	Real red;
	Real green;
	Real blue;

	void setFromInt(Int value)
	{
		red = ((value >> 16) & 0xff) / 255.0f;
		green = ((value >> 8) & 0xff) / 255.0f;
		blue = (value & 0xff) / 255.0f;
	}
};

struct LevelUpFXInfo
{
    const void *fx;
    AsciiString boneName;
};

typedef std::vector<AsciiString> AsciiStringVector;
typedef std::vector<LevelUpFXInfo> LevelUpFXVector;

// The name is established by the ExperienceLevel parser/table and by the
// matched findLevel callers, rather than by adjacency to the generated dump.
class ExperienceLevel : public Overridable
{
public:
	ExperienceLevel();

private:
    AsciiString m_name;                            // +0x0c
	Int m_requiredExperience;                     // +0x10
	Int m_experienceAward;                        // +0x14
	Int m_experienceAwardOwnGuysDie;              // +0x18
	AsciiStringVector m_targetNames;               // +0x1c
	AsciiStringVector m_attributeModifiers;        // +0x28
	LevelUpFXVector m_levelUpFx;                   // +0x34
	Int m_levelUpOCL;                              // +0x40
	AsciiStringVector m_upgrades;                  // +0x44
	ModelConditionFlags m_modelConditionState;    // +0x50
	RadiusDecalTemplate m_selectionDecal;          // +0x78
	Bool m_showLevelUpTint;                        // +0xa8
	RGBColor m_levelUpTintColor;                   // +0xac
	Int m_levelUpTintPreColorTime;                 // +0xb8
	Int m_levelUpTintPostColorTime;                // +0xbc
	Int m_levelUpTintSustainColorTime;             // +0xc0
	Real m_levelUpTintFrequency;                  // +0xc4
	Real m_levelUpTintAmplitude;                  // +0xc8
	Int m_rank;                                    // +0xcc
	Bool m_informUpdateModule;                     // +0xd0
	Bool m_singlePlayerOnly;                       // +0xd1
	Bool m_multiPlayerOnly;                        // +0xd2
	Int m_emotionType;                             // +0xd4
};

// ??0ExperienceLevel@@QAE@XZ
ExperienceLevel::ExperienceLevel()
	: m_name((const char *)0x0107301c),
	  m_requiredExperience(0),
	  m_experienceAward(0),
	  m_experienceAwardOwnGuysDie(-1),
	  m_levelUpOCL(0),
	  m_modelConditionState()
{
	m_showLevelUpTint = false;
	m_levelUpTintPreColorTime = 0;
	m_levelUpTintPostColorTime = 0;
	m_levelUpTintSustainColorTime = 0;
	m_levelUpTintFrequency = 0.0f;
	m_levelUpTintAmplitude = 0.0f;
	m_rank = 0;
	m_informUpdateModule = false;
	m_singlePlayerOnly = false;
	m_multiPlayerOnly = false;
	m_emotionType = -1;
	m_levelUpTintColor.setFromInt(0);
}
