// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?findMultiplayerColorDefinitionByName@MultiplayerSettings@@: Code/GameEngine/Source/Common/MultiplayerSettings.cpp
// Open-BFME: MultiplayerSettings::findMultiplayerColorDefinitionByName, retail
// 0x0008E760, 275 bytes.
//
// The reference's body unchanged. As in the special power store's private
// lookup, the name comes back BY VALUE, so each turn builds a temporary in the
// caller's frame, compares it and destroys it -- which is what the SEH frame
// and most of the body are.
//
// The colour list is the reference's map: the tree header is at this+0x30, the
// walk starts at its leftmost node and ends on the header itself, and the value
// sits at node+0x14 behind the four node words and the key.

#define _DLL
#include <string.h>
#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();						// folded onto releaseBuffer, 0x00887940

	Int compare(const char *str, Int len) const
	{
		const Int myLen = m_data ? m_data->length : 0;
		const char *data = m_data ? &m_data->data[0] : "";
		Int result = memcmp(data, str, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	Int compare(const AsciiString &str) const
	{
		const Int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		return compare(data, len);
	}

private:
	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorDefinition
{
public:
	AsciiString getTooltipName(void) const;			// ILT 0x0002D830, returns by value

private:
	unsigned char m_unmodelled_000[0x2C];			// sizeof, for the map node only
};

typedef _STL::map<Int, MultiplayerColorDefinition> MultiplayerColorList;
typedef MultiplayerColorList::iterator MultiplayerColorIter;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *findMultiplayerColorDefinitionByName( AsciiString name );

private:
	unsigned char m_unmodelled_000[0x30];
	MultiplayerColorList m_colorList;			// this+0x30
};

MultiplayerColorDefinition * MultiplayerSettings::findMultiplayerColorDefinitionByName(AsciiString name)
{
	MultiplayerColorIter iter = m_colorList.begin();

	while (iter != m_colorList.end())
	{
		if (iter->second.getTooltipName() == name)
			return &(iter->second);

		++iter;
	}

	return 0;
}
