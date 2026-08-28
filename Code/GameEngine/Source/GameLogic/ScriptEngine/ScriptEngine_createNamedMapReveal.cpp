// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ScriptEngine::createNamedMapReveal, retail 0x0034EF80, 379 bytes.
//
// The reference's body unchanged, and the fourth of the named-reveal family to
// land on the same model: the scan that refuses a duplicate name is the one
// its three siblings run, over the 0x10-stride vector at ScriptEngine+0x175F8
// with the same inlined AsciiString compare.
//
// What is new here is the tail -- a NamedReveal built on the stack, assigned
// in the reference's own order, and pushed onto the vector -- which is most of
// the extra bytes, push_back's grow path included. The element layout is the
// one the do and undo halves already pinned, with the radius at +8 and the
// player name at +0x0C.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef float Real;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);

struct Coord3D { Real x, y, z; };

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;					// this+0x04
	UnsignedShort m_pad;
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	// Delegating, and visibly so: it is what puts the __$SEHRec$ store ahead of
	// `mov ecx, esp` when the by-value name is built in the outgoing argument
	// slot for getWaypointByName.
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}

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
	// Declared, so the whole element is one object to the unwinder: retail
	// carries a single state across the three strings, not one apiece.
	NamedReveal(void) {}

	AsciiString m_revealName;				// +0x00
	AsciiString m_waypointName;				// +0x04
	Real m_radiusToReveal;					// +0x08
	AsciiString m_playerName;				// +0x0C
};

typedef _STL::vector<NamedReveal> VecNamedReveal;
typedef VecNamedReveal::iterator VecNamedRevealIt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void createNamedMapReveal(const AsciiString &revealName, const AsciiString &waypointName,
														Real radiusToReveal, const AsciiString &playerName);

private:
	char m_slice_pad[0x175F8];				// retail this+0x00 .. +0x175F7, untouched
	VecNamedReveal m_namedReveals;				// this+0x175F8
};

void ScriptEngine::createNamedMapReveal(const AsciiString& revealName, const AsciiString& waypointName, Real radiusToReveal, const AsciiString& playerName)
{
	VecNamedRevealIt it;

	// Will fail if there's already one in existence of the same name.
	for (it = m_namedReveals.begin(); it != m_namedReveals.end(); ++it) {
		if (it->m_revealName == revealName) {
			return;
		}
	}

	NamedReveal reveal;
	reveal.m_playerName = playerName;
	reveal.m_radiusToReveal = radiusToReveal;
	reveal.m_revealName = revealName;
	reveal.m_waypointName = waypointName;

	m_namedReveals.push_back(reveal);
}
