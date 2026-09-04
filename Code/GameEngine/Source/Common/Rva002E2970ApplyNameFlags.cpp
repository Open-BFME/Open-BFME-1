// cl: /DNDEBUG /MD /O2 /Ob0
// Open-BFME5: retail 0x002E2970 (+143B) + sibling 0x002E2870 (+196B).
// Event-flag host: init NameKeys for On* events, then apply XML Name tags.

#include <string.h>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class XmlNameSlotList
{
public:
	int count();
	const char *tagAt(int index);
	const char *nameAt(int index);
	void finish();
};

struct EventFlagEntry
{
	NameKeyType key;
	unsigned char flag;
	char pad[3];

	void setKeyFromName(const char *name);
};

class Rva002E2970Host
{
	char m_pad0[0x10];
	EventFlagEntry m_entries[13];
	char m_pad78[0xB8 - 0x78];
	NameKeyType m_onDestroyedKey;

public:
	void initEventKeys();
	void applyNameFlags(XmlNameSlotList *xml);
};

void EventFlagEntry::setKeyFromName(const char *name)
{
	key = TheNameKeyGenerator->nameToKey(name);
}

void Rva002E2970Host::initEventKeys()
{
	m_entries[0].setKeyFromName("OnDamaged");
	m_entries[1].setKeyFromName("OnDestroyed");
	m_onDestroyedKey = TheNameKeyGenerator->nameToKey("OnDestroyed");
	m_entries[2].setKeyFromName("OnArrived");
	m_entries[3].setKeyFromName("OnUnitEntered");
	m_entries[5].setKeyFromName("OnUnitExited");
	m_entries[4].setKeyFromName("OnTeamEntered");
	m_entries[6].setKeyFromName("OnTeamExited");
	m_entries[7].setKeyFromName("OnTeamDestroyed");
	m_entries[8].setKeyFromName("BeScary");
	m_entries[9].setKeyFromName("DamageIncoming");
	m_entries[10].setKeyFromName("OnAflame");
	m_entries[11].setKeyFromName("OnQuenched");
	m_entries[12].setKeyFromName("OnCreated");
}

void Rva002E2970Host::applyNameFlags(XmlNameSlotList *xml)
{
	int i = 0;
	if (xml->count() > 0)
	{
		do
		{
			int diff = memcmp(xml->tagAt(i), "Name", 5);
			if (diff == 0)
			{
				NameKeyType key = TheNameKeyGenerator->nameToKey(xml->nameAt(i));
				int j;
				for (j = 0; j < 13; ++j)
				{
					if (m_entries[j].key == key)
					{
						m_entries[j].flag = 1;
						break;
					}
				}
			}
			++i;
		} while (i < xml->count());
	}
	xml->finish();
}
