// ?d_0035ee70@@YAXXZ
// partial score=0.82 date=2026-09-09
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

class LineScanner
{
public:
	const char *skipWhitespace(const char *s);
};

class BfmeLexEAN
{
public:
	int bfmeFailEAN(int code);
	int bfmeScanEAN();
};

class BfmeLexEAO
{
public:
	char bfmeSkipCommentEAO();
};

class Rva0035E8B0Tail
{
public:
	int scan();
};

class XmlNameSlotList
{
	const char *m_pos;
	char *m_unused4;
	char *m_lineStart;
	int m_lineNumber;
	unsigned char m_inTag;
	unsigned char m_pad11[0x1c - 0x11];
	char *m_pending;
	char *m_pendingEnd;
	unsigned char m_pendingChar;
	unsigned char m_pad25[0x28 - 0x25];
	int m_count;

public:
	int count();
	const char *tagAt(int index);
	const char *nameAt(int index);
	int finish();
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

int XmlNameSlotList::finish()
{
	BfmeLexEAN *parser = (BfmeLexEAN *)this;
	LineScanner *scanner = (LineScanner *)this;
	BfmeLexEAO *commentParser = (BfmeLexEAO *)this;

	if (m_inTag && *m_pos == '/')
	{
		++m_pos;
		if (*m_pos != '>')
			return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
		++m_pos;
		return 2;
	}

	if (m_pendingEnd)
	{
		*m_pendingEnd = m_pendingChar;
		m_pendingEnd = NULL;
		m_pendingChar = 0;
	}

	if (!m_pos)
		return parser->bfmeFailEAN(-1);

	m_pos = scanner->skipWhitespace(m_pos);
	while (*m_pos != 0)
	{
		if (*m_pos != '<')
			return parser->bfmeScanEAN();
		if (m_pos[1] != '!')
			return ((Rva0035E8B0Tail *)this)->scan();
		if (!commentParser->bfmeSkipCommentEAO())
			return parser->bfmeFailEAN(-1);
		m_pos = scanner->skipWhitespace(m_pos);
	}

	m_pending = NULL;
	m_count = 0;
	return 0;
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
