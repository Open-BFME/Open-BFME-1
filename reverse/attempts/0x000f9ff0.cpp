// ??0?$pair@$$CBURva000F9FF0Key@@VGen_000F9C60@@@_STL@@QAE@ABU01@@Z
// partial score=0.45 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Address-derived: no proven owner. This is a pair<const Key, Value> copy
// constructor. Both halves are already landed real bodies reached by direct
// REL32 call:
//   - the key's leading member is an AsciiString / StringBase<char>: retail
//     calls ??0?$StringBase@D@@AAE@ABV0@@Z (0x00887B60, 121B,
//     Code/Libraries/Source/string/StringBase.cpp) directly, exactly as
//     Code/Libraries/Source/WWVegas/WWLib/ascii_string.h documents for every
//     other AsciiString copy site in this tree -- the rest of the key
//     (0x40 bytes, +0x04..+0x44) is plain per-field trivial copying.
//   - the value is Gen_000F9C60 (0x000F9C60, 115B,
//     Code/GameEngine/Source/Common/BfmeMixedCopyWK.cpp), reached through the
//     ILT thunk at 0x0003ED92.
// The prior blocked attempt pinned the pair to the 16-byte
// Gen_t_000fa390_k4/p12cd tgrid scaffold, which cannot be right: this body's
// own key alone runs to 0x44 bytes before the value even starts. That pin is
// not reused here.

#include "ascii_string.h"

// upstream layout: Code/GameEngine/Source/Common/BfmeMixedCopyWK.cpp
class UnicodeStringWK
{
public:
	UnicodeStringWK(const UnicodeStringWK &other);
	~UnicodeStringWK(void);

private:
	unsigned short *m_bfmeData;
};

class AsciiStringWK
{
public:
	AsciiStringWK(const AsciiStringWK &other);
	~AsciiStringWK(void);

private:
	char *m_bfmeData;
};

class BfmeWideWK : private UnicodeStringWK
{
public:
	BfmeWideWK(const UnicodeStringWK &other) : UnicodeStringWK(other) {}
	~BfmeWideWK(void) {}
};

class BfmeStrWK : private AsciiStringWK
{
public:
	BfmeStrWK(const AsciiStringWK &other) : AsciiStringWK(other) {}
	~BfmeStrWK(void) {}
};

class Gen_000F9C60
{
public:
	Gen_000F9C60(const Gen_000F9C60 &other);

	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	bool m_bfmeFlag;
	BfmeWideWK m_bfmeText;
	BfmeStrWK m_bfmeName;
};

// The trivial 0x40-byte tail that follows the key's AsciiString, copied
// dword by dword (one byte and three pad bytes in the middle) matching the
// retail instruction sequence exactly.
struct Rva000F9FF0KeyTail
{
	int m_f04, m_f08, m_f0c, m_f10;
	int m_f14, m_f18, m_f1c, m_f20, m_f24, m_f28;
	int m_f2c, m_f30, m_f34;
	unsigned char m_f38;
	unsigned char m_pad39[3];
	int m_f3c, m_f40;
};

struct Rva000F9FF0Key
{
	AsciiString m_name;
	Rva000F9FF0KeyTail m_tail;
};

namespace _STL
{

template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
};

}

typedef _STL::pair<const Rva000F9FF0Key, Gen_000F9C60> Rva000F9FF0Value;

inline void *operator new(unsigned int, void *place) { return place; }

// The explicit instantiation alone does not emit the implicit copy
// constructor, so it is reached through a call, matching the sibling
// GameSpyGroupRoomPairDestructor.cpp anchor pattern.
void Rva000F9FF0PairCopyAnchor(Rva000F9FF0Value *dest, const Rva000F9FF0Value *src)
{
	new (dest) Rva000F9FF0Value(*src);
}
