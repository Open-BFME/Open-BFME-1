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

class AsciiString
{
public:
	Int getLength(void) const { return m_data ? m_data->length : 0; }
	const char *str(void) const { return m_data ? m_data->text : ""; }

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

	bool operator==(const AsciiString &rhs) const { return compare(rhs) == 0; }

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
