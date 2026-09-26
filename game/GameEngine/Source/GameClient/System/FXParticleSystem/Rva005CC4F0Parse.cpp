// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Address-derived model for the anonymous static cdecl INI callback at
// 0x005CC4F0.  The retail body proves a category-8 factory walk followed by
// appending the created template to the vector at data+0xC0.  The vector view
// reuses the independently matched five-argument overflow ABI at ILT 0x16AE5;
// the Gen_t spelling is only the already-pinned 4-byte-POD vector callee
// contract, not an identity claim about the created FX template.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

extern const char g_bfmeEmptyAscii[];

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

#include "ascii_string.h"

struct Rva005CC4F0StringHeader
{
    int ref_count;
    unsigned short length;
    unsigned short capacity;
    char data[1];
};

static __forceinline int compareName(const AsciiString &name, const char *right)
{
    const Rva005CC4F0StringHeader *header =
        *reinterpret_cast<const Rva005CC4F0StringHeader * const *>(&name);
    int rightLength = right ? (int)strlen(right) : 0;
    int leftLength = header ? header->length : 0;
    const char *leftData = header ? &header->data[0] : g_bfmeEmptyAscii;
    int count = leftLength < rightLength ? leftLength : rightLength;
    const int result = memcmp(leftData, right, count);
    if (result != 0)
        return result;
    return leftLength - rightLength;
}

class Rva005CC4F0Factory
{
public:
	virtual void *createTemplate(INI *ini);

	const char *m_name;
	void *m_sourceAt8;
	Rva005CC4F0Factory *m_next;
};

#define _STLP_USE_STATIC_LIB
#include <vector>

struct Gen_t_005c8690_m4pod
{
	void *m_value;
};

// This is the independently matched ABI view of the folded STLport helper
// reached through ILT 0x00016AE5.  Its three pointers are the vector object
// layout; the element spelling is only a four-byte pointer slot.
class Rva005CC4F0VectorOwner
{
public:
	unsigned char m_head[0xC0];
	_STL::vector<Gen_t_005c8690_m4pod> m_templates;
};

class Rva005CC4F0Parse
{
public:
	static void parse(INI *ini, void *data, void *store, const void *userData);
};

// ?parse@Rva005CC4F0Parse@@SAXPAVINI@@PAX1PBX@Z
void Rva005CC4F0Parse::parse(INI *ini, void *data, void *, const void *)
{
	const char *token = ini->getNextToken(0);
	AsciiString name(token);
	Rva005CC4F0Factory *factory =
		*reinterpret_cast<Rva005CC4F0Factory **>(0x012F6508);

	for (;;)
	{
		if (compareName(name, factory->m_name) == 0)
			break;
		factory = factory->m_next;
	}

	void *created = factory->createTemplate(ini);
	Rva005CC4F0VectorOwner *owner = (Rva005CC4F0VectorOwner *)data;
	data = created;
	owner->m_templates.push_back(
		*reinterpret_cast<const Gen_t_005c8690_m4pod *>(&data));
}
