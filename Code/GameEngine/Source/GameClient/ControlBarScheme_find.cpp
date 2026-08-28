// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?findControlBarScheme@ControlBarSchemeManager@@QAEPAVControlBarScheme@@VAsciiString@@@Z: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarScheme.cpp
// Open-BFME: ControlBarSchemeManager::findControlBarScheme, retail 0x004AD740,
// 245 bytes.
//
// The reference's body unchanged: lower-case the name we were handed, walk the
// scheme list, and return the first whose own name matches without regard to
// case. The list is at this+0x0C and the scheme's name is its first member,
// which is what `mov eax, [ebp]` reads.
//
// compareNoCase is inlined here rather than called, and its shape matches the
// case-sensitive compare the terrain and reveal lookups already landed: two
// lengths from the buffer's +4, characters from +8 with an empty string
// standing in for a null buffer, a case-insensitive run over the shorter of
// the two, and the length difference only when that came out equal. The run is
// the CRT's own, reached through the import table.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that);
	~AsciiString();

	void toLower(void);					// retail 0x00887DA0

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

	Int compareNoCase(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = _memicmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarScheme
{
public:
	AsciiString m_name;					// this+0x00
};

typedef _STL::list<ControlBarScheme *> ControlBarSchemeList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBarScheme.h
class ControlBarSchemeManager
{
public:
	ControlBarScheme *findControlBarScheme(AsciiString name);

private:
	char m_slice_pad[0x0C];					// retail this+0x00 .. +0x0B, untouched
	ControlBarSchemeList m_schemeList;			// this+0x0C
};

ControlBarScheme *ControlBarSchemeManager::findControlBarScheme( AsciiString name )
{
	name.toLower();

	ControlBarSchemeList::iterator it = m_schemeList.begin();

	// iterate through the list and return the scheme that we're looking for
	while (it != m_schemeList.end())
	{
		ControlBarScheme *CBScheme = *it;
		if( !CBScheme )
		{
			return 0;
		}
		if(CBScheme->m_name.compareNoCase( name ) == 0)
			return CBScheme;
		it ++;
	}
	return 0;
}
