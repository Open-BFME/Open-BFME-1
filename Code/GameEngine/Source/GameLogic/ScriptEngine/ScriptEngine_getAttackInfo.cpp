// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ScriptEngine::getAttackInfo, retail 0x0033DD70, 555 bytes.

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

// BFME's AsciiString data header is eight bytes; the reference header's
// StringBase<char> header is four bytes.
struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_numChars;
	UnsignedShort m_unreconstructed_06;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

	Int getLength(void) const
	{
		return m_data ? m_data->m_numChars : 0;
	}

	const char *str(void) const
	{
		return m_data ? (const char *)(m_data + 1) : (const char *)0x0107388B;
	}

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

	Bool operator==(const AsciiString &rhs) const
	{
		return compare(rhs) == 0;
	}

private:
	BfmeAsciiStringData *m_data;
};

class ThingTemplate;

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class AttackPriorityInfo
{
public:
	void setPriority(const ThingTemplate *thing, Int priority);
	AsciiString getName(void) const { return m_name; }

	void *m_unreconstructed_00;
	AsciiString m_name;
	Int m_defaultPriority;
	void *m_priorityMap;
};

class ScriptEngine
{
public:
	const AttackPriorityInfo *getAttackInfo(const AsciiString &name);

private:
	AttackPriorityInfo *findAttackInfo(const AsciiString &name, Bool addIfNotFound);

	unsigned char m_unreconstructed_00000[0x1607C];
	AttackPriorityInfo m_attackPriorityInfo[256];
	Int m_numAttackInfo;
};

struct BfmeAttackPriorityItem
{
	BfmeAttackPriorityItem *m_next;
	BfmeAttackPriorityItem *m_previous;
	AsciiString m_templateName;
	Int m_priority;
};

struct BfmeAttackPrioritySet
{
	void *m_unreconstructed_00;
	AsciiString m_name;
	Int m_defaultPriority;
	BfmeAttackPriorityItem *m_priorityList;
	BfmeAttackPrioritySet *m_next;
};

class BfmeAIFactors
{
public:
	unsigned char m_unreconstructed_00[0xF4];
	BfmeAttackPrioritySet *m_attackPrioritySets;
};

class BfmeAIRoot
{
public:
	unsigned char m_unreconstructed_00[0x14];
	BfmeAIFactors *m_factors;
};

extern "C" BfmeAIRoot *TheAIParseDefinitionAI;

class BfmeDebugReport
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeDebugReport *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(Int value);
};

class BfmeDebugManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeDebugReport *slot6C(void *first, void *second);
};

extern BfmeDebugManager *TheGen001336E5C;
bool _bfme_debugReportingEnabled(void);
void _bfme_debugRecordCallsite(int kind);

const AttackPriorityInfo *ScriptEngine::getAttackInfo(const AsciiString &name)
{
	Int i;
	for (i = 1; i < m_numAttackInfo; ++i)
	{
		if (m_attackPriorityInfo[i].getName() == name)
			return &m_attackPriorityInfo[i];
	}

	BfmeAIRoot *root = TheAIParseDefinitionAI;
	BfmeAIFactors *factors = root->m_factors;
	BfmeAttackPrioritySet *set = factors->m_attackPrioritySets;
	for (; set; set = set->m_next)
	{
		if (set->m_name == name)
		{
			AttackPriorityInfo *info = findAttackInfo(name, true);
			if (!info)
				break;

			info->m_defaultPriority = set->m_defaultPriority;
			BfmeAttackPriorityItem *item = set->m_priorityList->m_next;
			while (item != set->m_priorityList)
			{
				ThingTemplate *thing = TheThingFactory->findTemplate(item->m_templateName);
				if (thing)
					info->setPriority(thing, item->m_priority);
				item = item->m_next;
			}
			return info;
		}
	}

	if (_bfme_debugReportingEnabled())
	{
		_bfme_debugRecordCallsite(1);
		TheGen001336E5C->slot60();
		BfmeDebugReport *report = TheGen001336E5C->slot6C(0, 0);
		report = report->slot38("Attempting to use an undefined attack priority - '");
		report->slot38(name.str());
		report = report->slot38("'\n");
		report->slot4C(2);
	}

	return &m_attackPriorityInfo[0];
}
