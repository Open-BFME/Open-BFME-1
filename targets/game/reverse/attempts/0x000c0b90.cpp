// ??1Rva000C0B90@@QAE@XZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x000C0B90 (158 B), no vtable (non-
// polymorphic member/aggregate).  Reverse member unwind: an 8-element array
// of 0x14-byte map-like elements at +0xB0 (real vector-destructor-iterator
// call, element dtor an 8-byte-adjusting thunk into the matched
// _Rb_tree<AsciiString,...> destructor at 0x000775F0 -- the constructor
// counterpart bfmeInitEOE in BfmeConv881.cpp constructs this same 8x0x14
// array), two 4-byte STLport list<Coord3D> members at +0xAC/+0xA8, an
// 8-element Coord3D array at +0x3C (also a real vector-destructor-iterator
// call, element dtor the matched empty ??1Coord3D@@QAE@XZ), and two
// BFMERetailAsciiString members at +0x24/+0x20.  Member types are opaque
// address-derived shells sized from the offsets with out-of-line
// destructors; the destructor body is empty and the compiler-generated
// array-of-nontrivial-destructor loops reproduce retail's real ??_M calls
// with only 9 bytes off: retail schedules `lea eax,[esi+0xb0]` before
// `push 0x14` (ours pushes the constant first) and uses eax for the second
// array's element address where ours allocates ecx -- pure argument/
// register scheduling inside the MSVC-synthesized vector-destructor-iterator
// call, not reachable by reordering the C++ member declarations (their
// physical offsets are fixed) or by changing element class shape (flat
// char body vs split 8+0xC fields tested, no change) or by making Coord3D's
// destructor out-of-line instead of inline-empty (no change). t=35min
// model=sonnet

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/WWVegas/WWMath/Vector3.h
class Coord3D
{
public:
	~Coord3D();

private:
	float m_x, m_y, m_z;
};

class Rva00076B00ListCoord3D
{
public:
	~Rva00076B00ListCoord3D();

private:
	char m_body[ 4 ];
};

class Rva000775F0MapElem
{
public:
	~Rva000775F0MapElem();

private:
	char m_body[ 0x14 ];
};

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	void releaseBuffer( void );

private:
	char *m_data;
};

class Rva000C0B90
{
public:
	~Rva000C0B90();

private:
	unsigned char m_unreconstructed00[ 0x20 ];
	BFMERetailAsciiString m_str20;
	BFMERetailAsciiString m_str24;
	unsigned char m_unreconstructed28[ 0x3C - 0x28 ];
	Coord3D m_coords3C[ 8 ];
	unsigned char m_unreconstructed9C[ 0xA8 - 0x9C ];
	Rva00076B00ListCoord3D m_listA8;
	Rva00076B00ListCoord3D m_listAC;
	Rva000775F0MapElem m_mapsB0[ 8 ];
};

// ??1Rva000C0B90@@QAE@XZ
Rva000C0B90::~Rva000C0B90()
{
}
