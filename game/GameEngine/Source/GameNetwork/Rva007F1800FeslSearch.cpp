// Retail 0x007F1800 FESL search-field serializer.
// The original owner is shared by the VJC, VJD and VJE wrappers.

// cl: /GS

typedef __int64 FeslInt64;

extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);

class Rva007E8810Message
{
public:
	void addInt64(const char *key, FeslInt64 value);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *key, void *value);
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC(void *key, void *value);
};

class Rva007E8980
{
public:
	void go(int key, unsigned char value);
};

struct Rva007F1800Owner
{
	FeslInt64 m_ownerId;
	int m_ownerType;
};

struct Rva007F1800Date
{
	int m_day;
	int m_month;
	int m_year;
};

struct Rva007F1800AttributeValue
{
	const char *m_name;
	const char *m_value;
};

struct Rva007F1800AttributeSlot
{
	Rva007F1800AttributeValue *m_value;
	int m_type;
};

struct Rva007F1800Query
{
	Rva007F1800Owner *m_owner;
	int m_ownerType;
	Rva007F1800Date *m_createDateStart;
	Rva007F1800Date *m_createDateEnd;
	Rva007F1800Date *m_updateDateStart;
	Rva007F1800Date *m_updateDateEnd;
	const char *m_name;
	unsigned char m_nameCaseSensitive;
	unsigned char m_nameWildcardMatch;
	char m_pad1e[2];
	int m_sizeMin;
	int m_sizeMax;
	Rva007F1800AttributeSlot *m_attributes;
	unsigned int m_attributeCount;
};

class Rva007F1800Search
{
public:
	void serialize(Rva007E8810Message *message, int maxRecords,
		void *queryArg);
};

// ?serialize@Rva007F1800Search@@QAEXPAVRva007E8810Message@@HPAX@Z
void Rva007F1800Search::serialize(Rva007E8810Message *message, int maxRecords,
	void *queryArg)
{
	Rva007F1800Query *query = (Rva007F1800Query *)queryArg;
	if (query->m_owner)
	{
		((Rva007E8810Message *)message)->addInt64("ownerId",
			query->m_owner->m_ownerId);
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"ownerType",
			(void *)query->m_owner->m_ownerType);
	}
	if (query->m_ownerType > -1)
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"type",
			(void *)query->m_ownerType);
	{
		char date[12];
		date[0] = 0;
		if (query->m_createDateStart)
		{
			sprintf(date, "%02d/%02d/%4d", query->m_createDateStart->m_day,
				query->m_createDateStart->m_month, query->m_createDateStart->m_year);
			((BfmeThingCIC *)message)->bfmeGoCIC((void *)"createDateStart",
				date);
		}
		if (query->m_createDateEnd)
		{
			sprintf(date, "%02d/%02d/%4d", query->m_createDateEnd->m_day,
				query->m_createDateEnd->m_month, query->m_createDateEnd->m_year);
			((BfmeThingCIC *)message)->bfmeGoCIC((void *)"createDateEnd", date);
		}
		if (query->m_updateDateStart)
		{
			sprintf(date, "%02d/%02d/%4d", query->m_updateDateStart->m_day,
				query->m_updateDateStart->m_month, query->m_updateDateStart->m_year);
			((BfmeThingCIC *)message)->bfmeGoCIC((void *)"updateDateStart", date);
		}
		if (query->m_updateDateEnd)
		{
			sprintf(date, "%02d/%02d/%4d", query->m_updateDateEnd->m_day,
				query->m_updateDateEnd->m_month, query->m_updateDateEnd->m_year);
			((BfmeThingCIC *)message)->bfmeGoCIC((void *)"updateDateEnd", date);
		}
	}
	if (query->m_name)
		((BfmeThingCIC *)message)->bfmeGoCIC((void *)"name",
			(void *)query->m_name);
	((Rva007E8980 *)message)->go((int)(void *)"nameCaseSensitive",
		query->m_nameCaseSensitive);
	((Rva007E8980 *)message)->go((int)(void *)"nameWildcardMatch",
		query->m_nameWildcardMatch);
	if (query->m_sizeMin > -1)
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"sizeMin",
			(void *)query->m_sizeMin);
	else
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"sizeMin", (void *)0);
	if (query->m_sizeMax > -1)
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"sizeMax",
			(void *)query->m_sizeMax);
	else
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"sizeMax", (void *)0x19000);
	if (maxRecords > -1)
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"maxRecords",
			(void *)maxRecords);
	else
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)"maxRecords", (void *)0x4e20);
	((BfmeThingCIB *)message)->bfmeGoCIB((void *)"searchAttributes.[]",
		(void *)query->m_attributeCount);
	unsigned int i = 0;
	for (; i < query->m_attributeCount; ++i)
	{
		char key[64] = { 0 };
		sprintf(key, "searchAttributes.%d.name", i);
		((BfmeThingCIC *)message)->bfmeGoCIC((void *)key,
			(void *)query->m_attributes[i].m_value->m_name);
		sprintf(key, "searchAttributes.%d.value", i);
		((BfmeThingCIC *)message)->bfmeGoCIC((void *)key,
			(void *)query->m_attributes[i].m_value->m_value);
		sprintf(key, "searchAttributes.%d.type", i);
		((BfmeThingCIB *)message)->bfmeGoCIB((void *)key,
			(void *)query->m_attributes[i].m_type);
	}
}
