// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFME PlayerTemplate copy constructor, retail 0x000E2E50. The two named
// callers are _STL::_Construct<PlayerTemplate> and
// PlayerTemplateStore::parsePlayerTemplateDefinition. The layout is shared
// with the exact assignment body at 0x000E32D0. In particular, the three
// sound-event members have out-of-line destructors: that preserves their
// unwind states without emitting a state store around each nonthrowing retain.

#include "Lib/BaseType.h"
#define _STLP_NO_EXCEPTIONS 1
#define private public
#include <map>
#include <hash_map>
#include <vector>
#undef private
#include "ascii_string.h"

extern "C" __declspec(dllimport) __declspec(nothrow) long __stdcall
	InterlockedIncrement(long volatile *addend);

class UnicodeString
{
public:
	UnicodeString() : m_text(0) {}
	UnicodeString(const UnicodeString &source)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&source);
	}
	~UnicodeString();

private:
	unsigned short *m_text;
};

typedef int NameKeyType;

enum VeterancyLevel
{
	VETERANCY_LEVEL_INVALID = -1
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Handicap
{
public:
	float m_handicaps[4];
};

class Money
{
public:
	virtual ~Money();
	virtual void slot00() {}
	virtual void slot01() {}
	virtual void slot02() {}
	float m_money;
	int m_playerIndex;
};

namespace rts
{
template <class T> struct hash
{
	unsigned int operator()(T value) const;
};
}

struct Rva000D6770Value
{
	AsciiString m_key;
	Real m_mapped;
};

struct Rva000D6770ExtractKey
{
	const AsciiString &operator()(const Rva000D6770Value &value) const
	{
		return value.m_key;
	}
};

typedef _STL::hashtable<Rva000D6770Value, AsciiString, rts::hash<AsciiString>,
	Rva000D6770ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D6770Value> > ProductionTimeChangeMap;

struct Gen_t_000e2230_p4pod
{
	Real m_value;
};

struct Gen_t_000e2330_p4pod
{
	VeterancyLevel m_level;
};

class PlayerTemplateSoundObject
{
public:
	virtual void slot00() {}
	virtual void slot01() {}
	virtual void slot02() {}
	long m_refCount;
};

class PlayerTemplateSoundEvent
{
public:
	static __forceinline void retain(void *data) throw()
	{
		if (data != 0)
		{
			PlayerTemplateSoundObject *object = (PlayerTemplateSoundObject *)data;
			InterlockedIncrement(&object->m_refCount);
		}
	}

	__forceinline PlayerTemplateSoundEvent(
		const PlayerTemplateSoundEvent &source) throw()
	{
		m_data = source.m_data;
		retain(m_data);
	}
	~PlayerTemplateSoundEvent();

	void *m_data;
};

typedef _STL::map<NameKeyType, Gen_t_000e2230_p4pod,
	_STL::less<NameKeyType> > ProductionChangeMap;
typedef _STL::map<NameKeyType, Gen_t_000e2330_p4pod,
	_STL::less<NameKeyType> > ProductionVeterancyMap;
typedef _STL::vector<ScienceType> ScienceVec;

class PlayerTemplate
{
public:
	NameKeyType m_nameKey;
	UnicodeString m_displayName;
	AsciiString m_side;
	Handicap m_handicap;
	Money m_money;
	RGBColor m_preferredColor;
	AsciiString m_startingBuilding;
	AsciiString m_startingUnits[10];
	ProductionChangeMap m_productionCostChanges;
	ProductionTimeChangeMap m_productionTimeChanges;
	ProductionVeterancyMap m_productionVeterancyLevels;
	ScienceVec m_intrinsicSciences;
	ScienceVec m_intrinsicSciencesMP;
	AsciiString m_purchaseScienceCommandSet;
	AsciiString m_purchaseScienceCommandSetMP;
	AsciiString m_specialPowerShortcutCommandSet;
	AsciiString m_specialPowerShortcutWinName;
	int m_specialPowerShortcutButtonCount;
	AsciiString m_loadScreenMusic;
	bool m_observer;
	bool m_playableSide;
	int m_intrinsicSPP;
	int m_maxLevelMP;
	int m_maxLevelSP;
	AsciiString m_scoreScreenImage;
	AsciiString m_loadScreenImage;
	AsciiString m_headWaterMark;
	AsciiString m_flagWaterMark;
	AsciiString m_enabledImage;
	AsciiString m_sideIconImage;
	AsciiString m_beaconTemplate;
	_STL::vector<AsciiString> m_initialUpgrades;
	_STL::vector<AsciiString> m_buildableHeroesMP;
	PlayerTemplateSoundEvent m_lightPointsUpSound;
	PlayerTemplateSoundEvent m_objectiveAddedSound;
	PlayerTemplateSoundEvent m_objectiveCompletedSound;
	AsciiString m_defaultPlayerAIType;
	AsciiString m_spellBook;
	AsciiString m_spellBookMP;
	bool m_evil;
	AsciiString m_spellStoreCurrentPowerLabel;
	AsciiString m_spellStoreMaximumPowerLabel;
};

PlayerTemplate makePlayerTemplateCopy(const PlayerTemplate &source)
{
	return source;
}
