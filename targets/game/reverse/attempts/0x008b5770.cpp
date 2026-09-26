// ?d_008b5770@@YAXXZ
// partial score=0.9924 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct Rva008B5770StringData
{
	unsigned short refCount, length, capacity, flags;
};
struct Rva008B5770StringPool
{
	void *unused;
	void (__cdecl *free)(void *);
};
extern Rva008B5770StringData g_bfmeDefaultString1284;
extern Rva008B5770StringPool *g_bfmeStringPool1284;

class Rva8CD130String
{
public:
	Rva8CD130String() : m_data(&g_bfmeDefaultString1284)
	{
		++g_bfmeDefaultString1284.refCount;
	}
	~Rva8CD130String()
	{
		Rva008B5770StringData *data = m_data;
		if (--data->refCount == 0)
			g_bfmeStringPool1284->free(data);
	}
	Rva008B5770StringData *m_data;
};

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *name);
};
class AptValue;
extern Rva8CD130Value **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern AptValue *g_bfmeFallbackDB;
extern int bfmeCompareVSC(const char *, const char *);

struct Rva008B5770Entry
{
	const char *name;
	int valueIndex;
};
struct Rva008B5770Number
{
	int type;
	int unused;
	int value;
};
struct Rva008B5770Scope
{
	char padding00[0x10];
	Rva008B5770Number **values;
	char padding14[0x14];
	int count;
	Rva008B5770Entry *entries;
};
struct Rva008B5770Owner
{
	void *vtable;
	unsigned int flags;
	char padding08[0x18];
	void *scope;
	int value;
	const char *name;
};

AptValue *rva008B5770NamedProperty(Rva008B5770Owner *owner)
{
	unsigned int flags = owner->flags;
	if ((flags & 63) == 0x15 && ((unsigned char)~(unsigned char)(flags >> 15) & 1) == 0)
	{
		Rva8CD130Value *value = g_bfmeArr1233[g_bfmeCount1233 - 1];
		Rva8CD130String key;
		Rva008B5770Scope *scope = (Rva008B5770Scope *)((char *)owner->scope + 8);
		value->getName(&key);
		int index = 0;
		if (scope->count > 0)
		{
			do
			{
				const char *candidateName = scope->entries[index].name;
				if (bfmeCompareVSC((const char *)key.m_data + 8, candidateName) == 0)
				{
					int valueIndex = scope->entries[index].valueIndex;
					Rva008B5770Number *candidate = scope->values[valueIndex];
					if (candidate->type != 6)
						break;
					owner->value = scope->values[scope->entries[index].valueIndex]->value;
					owner->name = scope->entries[index].name;
					break;
				}
				++index;
			} while (index < scope->count);
		}
	}
	return g_bfmeFallbackDB;
}
