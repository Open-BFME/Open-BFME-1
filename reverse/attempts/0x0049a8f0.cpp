// ?add@BannerThingCounter@@QAEXPAUBannerThingCounts@@ABVAsciiString@@H@Z
// partial score=0.97 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "Common/AsciiString.h"
#include <algorithm>
#include <vector>

class ThingTemplate;

class BFMEThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

class BannerThingFilter
{
public:
	bool accepts(const ThingTemplate *thing, void *player, bool includeDisabled);

private:
	int m_state;
};

struct BannerThingEntry
{
	int m_first;
	int m_second;
	BannerThingFilter m_filter;
};

class BannerUI
{
public:
	char m_fields[0x1c];
	BannerThingFilter m_defaultFilter;
	BannerThingEntry *m_entries;
	BannerThingEntry *m_entriesEnd;
};

class BuildVariationSource
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void *getBuildVariationList() = 0;
};

struct BuildVariation
{
	int m_first;
	int m_second;
	BuildVariationSource *m_source;
	int m_fourth;
	int m_fifth;
};

class ThingTemplate
{
public:
	BuildVariationSource *getBuildVariation(int index) const
	{
		if (index < 0 || (unsigned int)index >= (unsigned int)(m_variationsEnd - m_variations))
			return 0;
		return m_variations[index].m_source;
	}

	unsigned char m_fields000[0xd4];
	unsigned int m_kindOf;
	unsigned char m_fields0d8[0x294 - 0xd8];
	BuildVariation *m_variations;
	BuildVariation *m_variationsEnd;
};

struct BuildVariationNode
{
	BuildVariationNode *m_next;
	BuildVariationNode *m_previous;
	AsciiString m_name;
	int m_count;
};

struct BuildVariationList
{
	unsigned char m_fields[0x174];
	BuildVariationNode *m_sentinel;
};

struct BannerThingCounts
{
	AsciiString *m_unmatchedNames;
	AsciiString *m_unmatchedNamesEnd;
	AsciiString *m_unmatchedNamesCapacity;
	int *m_counts;
};

class BannerThingCounter
{
public:
	void add(BannerThingCounts *counts, const AsciiString &name, int count);
};

extern BFMEThingFactory *g_mgr12EF1D8;
extern BannerUI *TheBannerUI;

void BannerThingCounter::add(BannerThingCounts *counts, const AsciiString &name, int count)
{
	const ThingTemplate *thing = g_mgr12EF1D8->findTemplate(name);
	if (thing == 0)
		return;

	if (thing->m_kindOf & 0x1000)
	{
		int variationCount = thing->m_variationsEnd - thing->m_variations;
		for (int index = 0; index < variationCount; ++index)
		{
			BuildVariationSource *source = thing->getBuildVariation(index);
			if (source != 0)
			{
				BuildVariationList *list = (BuildVariationList *)source->getBuildVariationList();
				if (list != 0)
				{
					BuildVariationNode *node = list->m_sentinel->m_next;
					for (; node != list->m_sentinel; node = node->m_next)
						add(counts, node->m_name, node->m_count * count);
					return;
				}
			}
		}
		return;
	}

	if (TheBannerUI->m_defaultFilter.accepts(thing, 0, false))
	{
		if (std::find(counts->m_unmatchedNames, counts->m_unmatchedNamesEnd, name)
			== counts->m_unmatchedNamesEnd)
			reinterpret_cast<std::vector<AsciiString> *>(counts)->push_back(name);
		return;
	}

	int entryCount = TheBannerUI->m_entriesEnd - TheBannerUI->m_entries;
	for (int index = 0; index < entryCount; ++index)
	{
		if (TheBannerUI->m_entries[index].m_filter.accepts(thing, 0, false))
		{
			counts->m_counts[index] += count;
			return;
		}
	}
}
