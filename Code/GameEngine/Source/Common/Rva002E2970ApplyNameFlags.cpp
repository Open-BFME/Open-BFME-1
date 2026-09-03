// cl: /DNDEBUG /MD /O2
// Open-BFME5: retail 0x002E2970, 143 bytes.
// Walk XML slot list; for each tag equal to "Name\0", nameToKey the
// name field and set the matching On* event flag at this+0x10.. .

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
};

class Rva002E2970Host
{
	char m_pad0[0x10];
	EventFlagEntry m_entries[13];

public:
	void applyNameFlags(XmlNameSlotList *xml);
};

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
