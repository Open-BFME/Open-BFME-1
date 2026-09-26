// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: address-derived HordeContain template selection helper, retail
// 0x002369C0.  Retail chooses one integer from the list at +0x138, maps its
// sixteen-byte slot at +0x12C to the module-data roster at +0x224, and asks
// TheRegistry for the matching template name.

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class ThingTemplate
{
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};

extern BfmeThingFactory *Rva0020AA00TheRegistry;

extern Int GetGameLogicRandomValue( Int low, Int high, char *file, Int line );

struct BfmeRandomNode
{
	BfmeRandomNode *m_next;
	BfmeRandomNode *m_previous;
	Int m_value;
};

struct BfmeRandomList
{
	BfmeRandomNode *m_head;

	Bool empty() const
	{
		return m_head->m_next == m_head;
	}
};

struct BfmeHordeSlot
{
	void *m_key;
	char m_tail[ 0xc ];
};

struct BfmeHordeRosterEntry
{
	void *m_key;
	AsciiString m_name;
};

struct BfmeHordeRoster
{
	char m_head[ 0x224 ];
	BfmeHordeRosterEntry **m_begin;
	BfmeHordeRosterEntry **m_end;
};

class Rva002369C0HordeContain
{
public:
	ThingTemplate *rva002369C0();

private:
	char m_head[ 4 ];
	BfmeHordeRoster *m_moduleData;
	char m_gap[ 0x114 - 8 ];
	char m_unusedTree[ 0x18 ];
	BfmeHordeSlot *m_slots;
	char m_gap2[ 0x138 - 0x130 ];
	BfmeRandomList m_randomList;
};

// ?rva002369C0@Rva002369C0HordeContain@@QAEPAVThingTemplate@@XZ
ThingTemplate *Rva002369C0HordeContain::rva002369C0()
{
	if (m_randomList.empty())
		return 0;

	Int count = 0;
	BfmeRandomNode *node = m_randomList.m_head;
	while ((node = node->m_next) != m_randomList.m_head)
		++count;

#line 975 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"
	Int selected = GetGameLogicRandomValue(0, count - 1, __FILE__, __LINE__);

	node = m_randomList.m_head->m_next;
	while (selected > 0)
	{
		--selected;
		node = node->m_next;
	}

	BfmeHordeSlot *slot = (BfmeHordeSlot *)((char *)m_slots + node->m_value * 0x10);
	for (BfmeHordeRosterEntry **cursor = m_moduleData->m_begin;
		cursor != m_moduleData->m_end; ++cursor)
	{
		BfmeHordeRosterEntry *entry = *cursor;
		if (slot->m_key == entry->m_key)
			return (ThingTemplate *)Rva0020AA00TheRegistry->findTemplate(entry->m_name);
	}

	return 0;
}
