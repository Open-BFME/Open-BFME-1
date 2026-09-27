// ??A?$map@VAsciiString@@UCoord3D@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UCoord3D@@@_STL@@@4@@_STL@@QAEAAUCoord3D@@ABVAsciiString@@@Z
// partial score=0.4 date=2026-09-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// retail 0x0064E690, 229 bytes: std::map<AsciiString, Coord3D>::operator[].
//
// The shape is STLport's own (vendor/stlport/stl/_map.h:158) and nothing is
// guessed here.  lower_bound on the key; then a comparison against the
// candidate node's key decides whether the key is already present; on a miss a
// value_type built from the key and a default-constructed Coord3D goes to the
// hinted insert, and both paths return &node->second.
//
// The three helpers are already converted elsewhere, and the body reaches all
// of them through ILT thunks:
//   0x00027381  _M_lower_bound of the AsciiString/Coord3D tree
//   0x00015898  operator!=(AsciiString, AsciiString), which the comparator
//               inlines; its target 0x006451D0 is STLport's
//               operator!=(const basic_string&, const basic_string&)
//   0x0003AFEE  insert_unique of the same tree, 628 bytes at 0x0064CBD0
//
// Two things the bytes fix, and which the sibling reconstructions of this
// subscript do not share:
//
// 1. The key is TWELVE bytes.  The comparison operand is the node at +0x10 and
//    the value this body returns is the node at +0x1C, and the copy the
//    insert path makes is taken with STLport's basic_string copy constructor
//    (0x0001CB11 -> 0x004FB1B0) rather than with a refcounted StringBase
//    forwarder.  AsciiString therefore has the three-word narrow-string
//    layout here, and it is declared locally to say so; the shared
//    ascii_string.h models the other, four-byte, one and lands on +0x14.
//
// 2. The comparator is not a guess.  The retail out-of-line
//    less<AsciiString>::operator() at 0x006455D0 is 21 bytes and forwards
//    straight to operator!= (it is stored in the tree at +8 and called
//    thiscall from insert_unique, 0x0064CBD0 +0x00C0), and this body tests
//    that call's boolean with `test al,al; je` -- the zero branch is the found
//    path -- so this tree's key_comp() answers "not equal".  That is the
//    opposite of the `compare(right) < 0` the other reconstructed map
//    subscripts use, and retail keeps the two apart: those bodies branch on the
//    signed `test eax,eax; jge` instead.
//
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
typedef float Real;

struct Coord3D
{
	Coord3D()
	{
		x = 0;
		y = 0;
		z = 0;
	}
	Real x;
	Real y;
	Real z;
};

#include <map>
#include <string>

// TU-local, for the reason in (1) above.  Everything the body needs from it is
// STLport's: the copy constructor below is basic_string's, whose out-of-line
// COMDAT the body reaches through the ILT thunk 0x0001CB11.
class AsciiString : public _STL::basic_string<char>
{
public:
	AsciiString() {}
	AsciiString(const AsciiString &that) : _STL::basic_string<char>(that) {}
	~AsciiString() {}
};

// Declared and not defined, so the comparison stays a CALL.  Retail does not
// inline it here: it calls the operator whose ILT thunk is 0x00015898, and the
// body this reproduces branches on the returned byte (`test al,al; je`).
// Defining it locally would inline the length compare and the repe cmpsb into
// the subscript instead, which is a different body -- AsciiStringCoordMap.cpp
// uses the same declare-only shape for operator<.
bool operator!=(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left != right;
	}
};
}

typedef _STL::map<AsciiString, Coord3D> AsciiStringCoord3DMap;

// retail 0x0064E690
template Coord3D &AsciiStringCoord3DMap::operator[](const AsciiString &key);
