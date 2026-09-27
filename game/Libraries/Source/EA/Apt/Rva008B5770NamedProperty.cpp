// ?rva008B5770NamedProperty@@YAPAVAptValue@@PAURva008B5770Owner@@@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x008B5770, 265 bytes. The address-derived identity does not
// assert an original callback name. It compares a string from the shared Apt
// value stack with entries in the owner's table, conditionally copies a value
// and name pointer, and returns the global at VA 0x013379BC.
//
// The two reads of scope->values[scope->entries[index].valueIndex] are written
// as two separate expressions on purpose. Caching one pointer in a local makes
// VC7.1 allocate the first load to ECX (0x008B5770 +0xAF, +0xB2) where retail
// uses EDX, and reuses it for the second read; retail re-loads the element.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned char m_padding02[6];
};

struct BfmeStringPool3AF0
{
	void *unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva8CD130String
{
public:
	Rva8CD130String() : m_data(&g_bfmeDefaultString1284)
	{
		++g_bfmeDefaultString1284.m_refCount;
	}
	~Rva8CD130String()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}
	BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *name);	// 0x008985C0, Rva008985C0ValueString.cpp
};

class AptValue;
extern AptValue **g_bfmeArr1233;				// 0x01338750
extern int g_bfmeCount1233;				// 0x01338748
extern AptValue *g_bfmeFallbackDB;			// 0x013379BC
extern int __cdecl bfmeCompareVSC(const char *, const char *);	// 0x009F6FA0

struct Rva008B5770Entry
{
	const char *m_name;
	int m_valueIndex;
};

struct Rva008B5770Number
{
	int m_type;
	int unused;
	int value;
};

struct Rva008B5770Scope
{
	char padding00[0x10];
	Rva008B5770Number **m_values;
	char padding14[0x14];
	int m_count;
	Rva008B5770Entry *m_entries;
};

struct Rva008B5770Owner
{
	void *m_vtable;
	unsigned int m_flags;
	char padding08[0x18];
	void *m_scope;
	int value;
	const char *m_name;
};

AptValue *rva008B5770NamedProperty(Rva008B5770Owner *owner)
{
	unsigned int flags = owner->m_flags;
	if ((flags & 63) == 0x15 && ((unsigned char)~(unsigned char)(flags >> 15) & 1) == 0)
	{
		Rva8CD130Value *value = (Rva8CD130Value *)g_bfmeArr1233[g_bfmeCount1233 - 1];
		Rva8CD130String key;
		Rva008B5770Scope *scope = (Rva008B5770Scope *)((char *)owner->m_scope + 8);
		value->getName(&key);
		int index = 0;
		if (scope->m_count > 0)
		{
			do
			{
				const char *candidateName = scope->m_entries[index].m_name;
				if (bfmeCompareVSC((const char *)key.m_data + 8, candidateName) == 0)
				{
					if (scope->m_values[scope->m_entries[index].m_valueIndex]->m_type != 6)
						break;
					owner->value = scope->m_values[scope->m_entries[index].m_valueIndex]->value;
					owner->m_name = scope->m_entries[index].m_name;
					break;
				}
				++index;
			} while (index < scope->m_count);
		}
	}
	return g_bfmeFallbackDB;
}
