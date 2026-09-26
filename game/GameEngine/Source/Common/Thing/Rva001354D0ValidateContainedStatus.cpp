// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/iniexception

#include "Common/INIException.h"

class ThingTemplate;
class Rva001354D0ModuleDataView;

struct Rva001354D0StringView
{
	struct Data
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_characters[1];
	};

	Data *m_data;
	const char *str() const { return m_data ? m_data->m_characters : ""; }
};

struct Rva001354D0Entry
{
	char m_pad00[8];
	Rva001354D0ModuleDataView *m_moduleData;
	char m_pad0C[8];
};

struct Rva001354D0ModuleInfoView
{
	Rva001354D0Entry *m_begin;
	Rva001354D0Entry *m_end;
	Rva001354D0Entry *m_capacity;
};

class Rva001354D0ModuleDataView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual bool slot6();
	char m_pad004[0x156 - 4];
	bool m_objectStatusOfContained;
};

class ThingTemplate
{
public:
	void resolveNames();
	char m_pad000[0x20];
	Rva001354D0StringView m_nameString;
	char m_pad024[0x294 - 0x24];
	Rva001354D0ModuleInfoView m_behaviorModuleInfo;
	char m_pad2A0[0x38C - 0x2A0];
	ThingTemplate *m_nextThingTemplate;
};

extern void bfmeDestroyAttributePoolEntries();

class Rva001354D0Owner
{
public:
	void rva001354D0();
private:
	char m_pad000[8];
	ThingTemplate *m_first;
};

void Rva001354D0Owner::rva001354D0()
{
	for (ThingTemplate *thing = m_first; thing != 0; thing = thing->m_nextThingTemplate)
	{
		thing->resolveNames();
		int count = thing->m_behaviorModuleInfo.m_end - thing->m_behaviorModuleInfo.m_begin;
		for (int i = 0; i < count; ++i)
		{
			if (i >= 0 && (unsigned int)i < (unsigned int)(thing->m_behaviorModuleInfo.m_end - thing->m_behaviorModuleInfo.m_begin))
			{
				Rva001354D0ModuleDataView *entry = thing->m_behaviorModuleInfo.m_begin[i].m_moduleData;
				if (entry && entry->slot6() && !entry->m_objectStatusOfContained)
					throw INIException(3, "ENTRY MISSING: ObjectStatusOfContained entry required within ContainModule for %s.", thing->m_nameString.str());
			}
		}
	}
	bfmeDestroyAttributePoolEntries();
}
