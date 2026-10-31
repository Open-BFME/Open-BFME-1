// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// LightPointSystem::rva0039C260, retail 0x0039C260 (287 bytes, ret 8 at
// 0x0039C37C). `this` is the global at 0x012F0FF8 that the matched
// INI::parseLightPointLevel (0x0039CCF0) loads before LightPointSystem::addLevel,
// so the object is the LightPointSystem and the entries are its LightPointLevels
// (final override, name at +0x0C). The matched BfmeItemEUA::bfmeRunEUAe
// (0x000C9930) reaches it through ILT 0x00045039 with its +0x274 store and the
// context it was handed. The loop finds the first level whose name matches the
// context string, then erases that level's index from the store's integer
// vector at +0x08 (the erase retail also keeps out of line at 0x0039BE00).
// The method is not proven, so it keeps the address.
//
// The loop is the one LightPointSystem::rva0039CB60 (0x0039CB60) runs to add
// the index, so the source follows that matched twin: a visible out-of-line
// override walk lets MSVC hoist the context string's data out of the loop.
// Without it the load stays in the preheader and the EBX save sinks below the
// EDI one.

#include <vector>
#include "ascii_string.h"

// AsciiString::compare(const AsciiString &), expanded in place.  Calling the
// member emits a ?compare@AsciiString@@QBEHABV1@@Z COMDAT that is not retail's
// 0x0005FEB0 body.  The buffer pointer is the string's first word; its length
// is the unsigned short at +4 and the characters start at +8.
struct AsciiCompareView
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};
	Header *m_data;
};

static __forceinline int asciiCompare( const AsciiString &left, const AsciiString &right )
{
	const AsciiCompareView &s = reinterpret_cast<const AsciiCompareView &>(right);
	const AsciiCompareView &t = reinterpret_cast<const AsciiCompareView &>(left);
	int thatLen = s.m_data ? s.m_data->length : 0;
	const char *thatData = s.m_data ? &s.m_data->data[0] : (const char *)"";
	int thisLen = t.m_data ? t.m_data->length : 0;
	const char *thisData = t.m_data ? &t.m_data->data[0] : (const char *)"";
	int n = thisLen < thatLen ? thisLen : thatLen;
	int c = memcmp(thisData, thatData, n);
	if (c != 0)
		return c;
	return thisLen - thatLen;
}

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	// ILT 0x00048C61 -> 0x00097880. The visible body is what lets MSVC keep
	// the name's data across the call; the call still binds to the ILT.
	__declspec(noinline) Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *finalOverrideViaFriend()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	void *m_vtable;
	Overridable *m_nextOverride;
};

class LightPointLevel : public Overridable
{
public:
	unsigned char m_pad08[0x0c - 0x08];
	AsciiString m_name;
};

// Same +0x274 store the twin 0x0039CB60 adds level indices to.
class BfmeUniqueIntegerStoreC8C0
{
public:
	unsigned char m_head[0x08];
	_STL::vector<Int> m_vector08;
};

class LightPointSystem
{
public:
	void rva0039C260(BfmeUniqueIntegerStoreC8C0 *indices, void *context);

private:
	unsigned char m_head[0x08];
	_STL::vector<LightPointLevel *> m_levels;
};

// ?rva0039C260@LightPointSystem@@QAEXPAVBfmeUniqueIntegerStoreC8C0@@PAX@Z
void LightPointSystem::rva0039C260(
		BfmeUniqueIntegerStoreC8C0 *indices, void *context)
{
	const AsciiString &name = *(const AsciiString *)context;
	for (UnsignedInt i = 0; i < m_levels.size(); ++i)
	{
		LightPointLevel *level =
			(LightPointLevel *)m_levels[i]->finalOverrideViaFriend();
		if (asciiCompare(level->m_name, name) == 0)
		{
			for (_STL::vector<Int>::iterator it = indices->m_vector08.begin();
					it != indices->m_vector08.end(); ++it)
			{
				if (*it == (Int)i)
				{
					indices->m_vector08.erase(it);
					return;
				}
			}
			return;
		}
	}
}
