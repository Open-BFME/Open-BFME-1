// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x00462540 is the STLport for_each instantiation over the window
// table at 0x012F19A4 (hash_map<AsciiString, WindowRecord>).  The APT
// close-screen helper _bfme_closeAptScreen (0x004629A0, ILT 0x00042591) and
// the delegate setup at 0x00463340 reach it through that ILT with a hidden
// result, a begin/end iterator pair and a by-value one-string functor, and
// cdecl `add esp, 0x18` for those six dwords.  The body inlines
// _Ht_iterator::operator++ including _M_skip_to_next, so it reloads the
// hashtable's bucket vector (+4 begin, +8 end) and re-hashes the node key
// with rts::hash's h*5+c walk when a chain ends.  WindowRecord keeps the
// record name at +0x28, the value offset 0x2C the body reads and releases
// through StringBase<char>::releaseBuffer (0x00887940); the by-value key copy
// and the returned functor go through StringBase<char>'s copy constructor
// (0x00887B60), exactly the callees Rva00462B40WindowTable.cpp witnesses.
//
// State: byte-exact, 360/360, all 12 relocations placed.  Do NOT add an
// optimisation flag to the // cl: line.  With /G7 this body is 360 bytes but
// stops being retail: the folded _M_buckets._M_start load (sub edi,[ebx+4])
// and `add reg,1` in place of retail's materialised `mov tmp,[ebx+4]` and
// `inc reg` are /G7-generation choices, and 13 earlier verdicts chased that
// residue as a register-allocation problem.  Retail is the plain default
// (/O2 with no /G flag), which is what the matched sibling
// Rva00462710ModeCheckForEach.cpp -- same STLport, same rts::hash<AsciiString>
// walk, same _M_skip_to_next -- also compiles under.  See
// targets/game/reverse/re_attempts.log for 0x00462540.
//
// NameClearFunctor00462540 also appears in AptScreenClose.cpp (the matched
// 0x004629A0 caller), where operator() spells the same test with `==` over the
// WWLib ascii_string.h shim.  Only the explicit compare() here inlines the
// memcmp this retail body shows, and the two shims model AsciiString
// differently, so the two definitions are intentionally not text-identical.
// Nothing links the COMDAT except the explicit instantiation below; if a
// future change makes that false, the two bodies must be reconciled.

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <hash_map>

#include "Common/AsciiString.h"

struct WindowRecord
{
	unsigned char m_pad00[0x28];
	AsciiString m_name;
};

namespace rts
{
	// Common/STLTypedefs.h: the generic hash defers to the container's own
	// std::hash, and the AsciiString specialization runs std::hash<const char *>
	// (STLport's __stl_hash_string, the h*5+c walk the body inlines) over the
	// inline str().  The by-value parameter is the header's spelling.
	template <class T> struct hash
	{
		size_t operator()(const T &value) const
		{
			_STL::hash<T> tmp;
			return tmp(value);
		}
	};
	template <> struct hash<AsciiString>
	{
		size_t operator()(AsciiString value) const
		{
			_STL::hash<const char *> tmp;
			return tmp((const char *)value.str());
		}
	};
	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}

typedef _STL::hash_map<AsciiString, WindowRecord, rts::hash<AsciiString>,
	rts::equal_to<AsciiString> > WindowTable;

struct NameClearFunctor00462540
{
	NameClearFunctor00462540(const AsciiString &name) : m_name(name) {}
	void operator()(_STL::pair<const AsciiString, WindowRecord> &record)
	{
		if (record.second.m_name.compare(m_name) == 0)
			record.second.m_name.clear();
	}
	AsciiString m_name;
};

template NameClearFunctor00462540
_STL::for_each<WindowTable::iterator, NameClearFunctor00462540>(
	WindowTable::iterator, WindowTable::iterator, NameClearFunctor00462540);
