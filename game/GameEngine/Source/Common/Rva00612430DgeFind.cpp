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
