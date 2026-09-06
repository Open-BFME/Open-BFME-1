// ??1Rva00078540@@QAE@XZ
// partial score=0.92 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x00078540 (183 B), no vtable (non-
// polymorphic member/aggregate).  Reverse member unwind: two
// StringBase<wchar_t> members at +0xF8/+0xF4, an 8-element array of
// 0x14-byte map-like elements at +0x54 (real vector-destructor-iterator
// call, same element dtor family as 0x000C0B90's), a BFMERetailAsciiString
// at +0x50, two 4-byte list<Coord3D>-like members at +0x4C/+0x48 (matched
// ~_List_base<Coord3D> at 0x00078060 through ILT 0x0004A3AE... wait: two
// separate ILT targets -- 0x000344F0 (list<Coord3D>, 0x00076B00) called
// twice at +0x4C/+0x48, then 0x0004A3AE (the AsciiString/Coord3D map
// destructor 0x00078060) at +0x38 -- and two more StringBase<wchar_t>
// members at +0x4/+0x0.  Member types are opaque address-derived shells
// sized from the offsets with out-of-line destructors; the destructor body
// is empty and the compiler-generated reverse unwind (including the real
// array-of-nontrivial-destructor loop) reproduces retail exactly.

template< typename T >
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer( void );
	T *m_data;
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

class Rva00076B00ListElem
{
public:
	~Rva00076B00ListElem();

private:
	char m_body[ 4 ];
};

class Rva00078060MapElem
{
public:
	~Rva00078060MapElem();

private:
	char m_body[ 0x10 ];
};

class Rva000775F0MapElem
{
public:
	~Rva000775F0MapElem();

private:
	char m_body[ 0x14 ];
};

class Rva00078540
{
public:
	~Rva00078540();

private:
	StringBase< unsigned short > m_str00;
	StringBase< unsigned short > m_str04;
	unsigned char m_unreconstructed08[ 0x38 - 8 ];
	Rva00078060MapElem m_map38;
	Rva00076B00ListElem m_list48;
	Rva00076B00ListElem m_list4C;
	BFMERetailAsciiString m_str50;
	Rva000775F0MapElem m_maps54[ 8 ];
	StringBase< unsigned short > m_strF4;
	StringBase< unsigned short > m_strF8;
};

// ??1Rva00078540@@QAE@XZ
Rva00078540::~Rva00078540()
{
}
