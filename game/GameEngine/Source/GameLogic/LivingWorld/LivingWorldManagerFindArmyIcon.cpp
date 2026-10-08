// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// LivingWorldManager name lookup over the army-icon vector at this+0x264.
// INIArmyIcon.cpp already places that vector here; 0x006174B0's name getter
// returns "LivingWorldManager". Each record starts with AsciiString m_name.
// The INI parser's findArmyIcon at 0x00614700 always allocates; this body
// is the const-ref search that returns the matching pointer or null.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

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

struct Rva006122A0Item
{
	AsciiString m_name;
};

class Rva006122A0Mgr
{
public:
	Rva006122A0Item *find(const AsciiString &name);

private:
	char m_pad[0x264];
	_STL::vector<Rva006122A0Item *> m_items;
};

// ?find@Rva006122A0Mgr@@QAEPAURva006122A0Item@@ABVAsciiString@@@Z
Rva006122A0Item *Rva006122A0Mgr::find(const AsciiString &name)
{
	for (Int i = 0; i < m_items.size(); i++)
		if (name == m_items[i]->m_name)
			return m_items[i];
	return 0;
}
