// ?rva000C0D00Index@WaypointMap@@QAEAAUCoord3D@@ABVAsciiString@@@Z
// partial score=0.59 date=2026-09-08
// cl: /DNDEBUG /DBFME_STLP_NODE_ALLOC /D_STLP_USE_STATIC_LIB /DWIN32 /D_WINDOWS /MD /EHsc /Ivendor/stlport /Ireference/shims/stlp_nodealloc /Ireference/shims/archivefilesystem_nosubsystem /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include <stl/_config.h>

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/FileSystem.h"
#include "Common/STLTypedefs.h"

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	void *m_data;
};

// Retail's WaypointMap is std::map<AsciiString, Coord3D>.  Coord3D comes from
// the upstream BaseType shim; its three-Real POD layout is already established
// by the neighboring map and waypoint bodies.

// AsciiString is a thin StringBase<char> wrapper in the retail layout.  The
// forwarding copy constructor is kept local, as in the neighboring map
// reconstructions, so the key copy calls the matched StringBase body.
inline AsciiString::AsciiString(const AsciiString &that)
{
	((StringBase<char> *)this)->StringBase<char>::StringBase(
		*(const StringBase<char> *)&that);
}

class WaypointAsciiStringLess
{
public:
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};

namespace _STL
{
template <> struct less<AsciiString> : public WaypointAsciiStringLess
{
};
}

extern void j_00044d82();
extern void j_00036f70();
class Rva000C0D00LowerCall {};
class Rva000C0D00InsertCall {};

class WaypointMap : public std::map<AsciiString, Coord3D>
{
public:
	Int m_numStartSpots;
	Coord3D &rva000C0D00Index(const AsciiString &key);
};

Coord3D &WaypointMap::rva000C0D00Index(const AsciiString &key)
{
	typedef void *(Rva000C0D00LowerCall::*LowerFunction)(const AsciiString &) const;
	union { void (*raw)(); LowerFunction member; } lower;
	lower.raw = j_00044d82;
	iterator it(static_cast<_STL::_Rb_tree_node<value_type> *>(
		(reinterpret_cast<Rva000C0D00LowerCall *>(this)->*lower.member)(key)));
	if (it == end() || key_comp()(key, (*it).first))
	{
		Coord3D value;
		typedef iterator (Rva000C0D00InsertCall::*InsertFunction)(iterator, const value_type &);
		union { void (*raw)(); InsertFunction member; } insert;
		insert.raw = j_00036f70;
		it = (reinterpret_cast<Rva000C0D00InsertCall *>(this)->*insert.member)(it, value_type(key, value));
	}
	return (*it).second;
}
