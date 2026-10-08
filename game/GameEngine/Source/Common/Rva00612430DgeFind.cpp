// ?find@Rva00612430Owner@@QAEPAURva00612430Item@@ABVAsciiString@@@Z
// Retail 0x00612430 (232 bytes): search the global owner's pointer vector at
// +0x258 for a record whose AsciiString name is at +0x18.  The callers load
// g_bfmeGameCW into ECX before the ILT, but the original owner spelling is not
// independently established, so the receiver and item names stay RVA-derived.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

class AsciiString;
static inline Int asciiLength(const AsciiString &s);
static inline Int asciiCompare(const AsciiString &self, const AsciiString &other);

class AsciiString
{
public:
	friend Int asciiLength(const AsciiString &s);
	const char *str(void) const { return m_data ? m_data->text : ""; }

	friend Int asciiCompare(const AsciiString &self, const AsciiString &other);

private:
	struct Data
	{
		Int refs;
		unsigned short length;
		unsigned short capacity;
		char text[1];
	};
	Data *m_data;
};

// File-static so this TU emits no AsciiString getLength/compare/== COMDATs;
// retail inlines them here.
static inline Int asciiLength(const AsciiString &s) { return s.m_data ? s.m_data->length : 0; }

static inline Int asciiCompare(const AsciiString &self, const AsciiString &other)
{
	Int lenOther = asciiLength(other);
	const char *pOther = other.str();
	Int lenThis = asciiLength(self);
	const char *pThis = self.str();
	Int shorter = lenThis < lenOther ? lenThis : lenOther;
	Int diff = memcmp(pThis, pOther, shorter);
	if (diff != 0)
		return diff;
	return lenThis - lenOther;
}

static inline bool operator==(const AsciiString &left, const AsciiString &right) { return asciiCompare(left, right) == 0; }

struct Rva00612430Item
{
	char m_prefix[0x18];
	AsciiString m_name;
};

class Rva00612430Owner
{
public:
	Rva00612430Item *find(const AsciiString &name);

private:
	char m_prefix[0x258];
	_STL::vector<Rva00612430Item *> m_items;
};

Rva00612430Item *Rva00612430Owner::find(const AsciiString &name)
{
	for (Int i = 0; i < m_items.size(); i++)
		if (m_items[i]->m_name == name)
			return m_items[i];
	return 0;
}
