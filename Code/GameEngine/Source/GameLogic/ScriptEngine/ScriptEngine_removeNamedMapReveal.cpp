// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ScriptEngine::removeNamedMapReveal, retail 0x0034D440, 217 bytes.
//
// The reference's body unchanged: scan the named reveals for the one with this
// name and erase it. Both halves are inlined, which is the whole 217 bytes --
// the same AsciiString compare TerrainTypes_findTerrain.cpp landed, and
// STLport's vector erase, which shifts the tail down and drops the last
// element rather than calling anything of its own.
//
// The vector sits at ScriptEngine+0x175F8 and its stride is 0x10, which is the
// reference's NamedReveal exactly: three strings and the reveal radius.
//
// The compare returns early on a memcmp difference rather than falling through
// to one return: written the other way the result is spilled to a third stack
// local, which costs the loop pointer the register whose addressing mode is a
// byte longer, and the body comes out one short.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

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

	AsciiString &operator=(const AsciiString &that);

	Int getLength(void) const { return m_data ? m_data->m_len : 0; }
	const char *str(void) const { return m_data ? (const char *)(m_data + 1) : ""; }

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

	Bool operator==(const AsciiString &rhs) const { return compare(rhs) == 0; }

private:
	BfmeAsciiStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
struct NamedReveal
{
	AsciiString m_revealName;				// +0x00
	AsciiString m_waypointName;				// +0x04
	AsciiString m_playerName;				// +0x08
	Real m_radiusToReveal;					// +0x0C
};

typedef _STL::vector<NamedReveal> VecNamedReveal;
typedef VecNamedReveal::iterator VecNamedRevealIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void removeNamedMapReveal(const AsciiString &revealName);

private:
	char m_slice_pad[0x175F8];				// retail this+0x00 .. +0x175F7, untouched
	VecNamedReveal m_namedReveals;				// this+0x175F8
};

void ScriptEngine::removeNamedMapReveal(const AsciiString& revealName)
{
	VecNamedRevealIt it;

	for (it = m_namedReveals.begin(); it != m_namedReveals.end(); ++it) {
		if (it->m_revealName == revealName) {
			m_namedReveals.erase(it);
			return;
		}
	}
}
