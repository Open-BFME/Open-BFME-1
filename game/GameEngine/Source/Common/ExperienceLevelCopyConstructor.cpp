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

// These two retail routes disagree with the generic helper ledger homes.
// Inline the bindings without emitting competing helper definitions.
// See attempt_support/20261111-experiencelevel-helper-bindings.md.
void j_00007554();
void j_0003827b();
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Construct<AsciiString, AsciiString>(AsciiString *out, const AsciiString &value)
{
    typedef void (__cdecl *Construct)(AsciiString *, const AsciiString &);
    ((Construct)j_00007554)(out, value);
}
template <> __declspec(dllimport) __forceinline
void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(
    AsciiString *position, const AsciiString &value, const __false_type &,
    unsigned int count, bool atEnd)
{
    typedef void (vector<AsciiString, allocator<AsciiString> >::*Overflow)(AsciiString *, const AsciiString &, const __false_type &, unsigned int, bool);
    union { void (*raw)(); Overflow member; } overflow;
    overflow.raw = j_0003827b;
    // The empty tag has no value to initialize. Value-initializing the
    // forwarded temporary adds a store absent from the retail caller.
    __false_type nativeTag;
    (this->*overflow.member)(position, value, nativeTag, count, atEnd);
}
}


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

// Retail's selection-decal assignment lives at 0x00458450 and is reached from
// this constructor through ILT 0x00015744.  Its body and identity are the
// verified Rva00458450 assignment, so the call is spelled against that name
// directly instead of through a linker alias.
class Rva00458450
{
public:
	void operator=(const Rva00458450 &that);
};

// Retail's operator= clears m_attributeModifiers through the shared
// vector-of-strings range erase: ILT 0x00024C17 jumping to 0x00065960, the
// route CRCParameterCheck::clear and the EnragedBehavior module-data
// constructor already spell.  ilt_oracle CONFIRMS
// ?erase@?$vector@VAsciiString@@... at that thunk and CONTRADICTS it at the
// 0x006FA560 row's own thunk, so the name is pin-only; this TU-scoped view
// spells the call against its symbols.csv pin at 0x00024C17 and keeps this
// object from emitting vector<AsciiString>::erase's wrong-shaped copy.
class Rva00065960AttributeRange
{
public:
	void erase( void *first, void *last );

	void *m_begin;
	void *m_end;
	void *m_endOfStorage;
};

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

	// m_selectionDecal is assigned twice in retail; both calls reach the
	// assignment body at 0x00458450 through ILT 0x00015744.  The stand-in
	// RadiusDecalTemplate keeps its own constructor and destructor names, so
	// the assignment is called through the verified Rva00458450 identity.
	typedef void (Rva00458450::*SelectDecalAssign)(const Rva00458450 &source);
	SelectDecalAssign assignSelectionDecal = &Rva00458450::operator=;

	m_name = that.m_name;
	m_requiredExperience = that.m_requiredExperience;
	m_experienceAward = that.m_experienceAward;
	m_experienceAwardOwnGuysDie = that.m_experienceAwardOwnGuysDie;
	m_targetNames = that.m_targetNames;
	((*(Rva00458450 *)(void *)&m_selectionDecal).*assignSelectionDecal)(
		*(const Rva00458450 *)(const void *)&that.m_selectionDecal);
	m_levelUpTintColor = that.m_levelUpTintColor;
	m_levelUpOCL = that.m_levelUpOCL;
	m_modelConditionState = that.m_modelConditionState;
	((*(Rva00458450 *)(void *)&m_selectionDecal).*assignSelectionDecal)(
		*(const Rva00458450 *)(const void *)&that.m_selectionDecal);
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
	((Rva00065960AttributeRange *)(void *)attributeModifiers)->erase(
		((Rva00065960AttributeRange *)(void *)attributeModifiers)->m_begin,
		((Rva00065960AttributeRange *)(void *)attributeModifiers)->m_end);
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
