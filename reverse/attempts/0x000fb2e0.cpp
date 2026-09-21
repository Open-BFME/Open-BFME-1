// ?Gen000FB2E0Method@Gen000FB2E0Owner@@QAEHI_N@Z
// partial score=0.5 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Address-derived reconstruction: no owning class or method identity is proven
// (no named caller; the single caller is itself an unnamed dump at 0x002A30D0).
// Structural evidence: this operates on a sub-object embedded at this+4 that is
// the SAME _STL::vector<Rva000FB210Element, _STL::allocator<Rva000FB210Element> >
// already landed as push_back (retail 0x000FB210,
// Code/Libraries/Source/WWVegas/WWLib/RvaVectorPushBack.cpp) and _M_insert_overflow
// (retail 0x000FB080, Code/Libraries/Source/WWVegas/WWLib/RvaVectorInsertOverflowInlineCopy.cpp),
// so this body links directly against those already-compiled template bodies
// instead of aliasing to still-dump thunks. The element's first field is a
// BFMERetailAsciiString (releaseBuffer called directly, retail 0x00887940) and its
// field at +0x44 is an embedded AudioEventRTS (destructed through the ILT thunk at
// retail 0x0002671F). A still-dump helper at 0x00032CC7 (-> 0x000FA1B0) constructs
// the element from the first stack parameter; a still-dump copy ctor at 0x0004845F
// (-> 0x000F9FF0) copies it into the vector's finish slot when there is room.
// Field +0x2C is zeroed when the second (bool) parameter is set. Like push_back's
// own body, the empty __false_type dispatch tag passed to _M_insert_overflow is
// aliased onto the value's own stack slot rather than a separate local.

inline void *operator new( unsigned int, void *place ) { return place; }

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
};

class Rva0002671FAudioEventRTSDestructorThunk
{
public:
	void forward();
};

// The teardown slot for the embedded AudioEventRTS-shaped field: retail destructs
// it through the ILT thunk at 0x0002671F, not the plain AudioEventRTS destructor
// symbol (0x000CFA40), so this local wrapper routes there explicitly.
struct Gen000FB2E0AudioSlot
{
	unsigned char m_bytes[ 0x1C ];

	~Gen000FB2E0AudioSlot()
	{
		( ( Rva0002671FAudioEventRTSDestructorThunk * )this )->forward();
	}
};

struct Rva000FB210Element
{
	BFMERetailAsciiString m_string;
	unsigned char m_pad04[ 0x28 ];
	int m_field2C;
	unsigned char m_pad30[ 0x14 ];
	Gen000FB2E0AudioSlot m_audioEvent;

	// still-dump helper (retail 0x00032CC7 -> 0x000FA1B0); constructs the element
	// from the caller's first stack parameter.
	Rva000FB210Element( unsigned int param1 );
	Rva000FB210Element( const Rva000FB210Element &other );
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

// Matches the already-landed instantiation for this element in
// RvaVectorPushBack.cpp / RvaVectorInsertOverflowInlineCopy.cpp exactly, so the
// mangled name of _M_insert_overflow below links directly to that landed body
// instead of needing an alternatename thunk.
template <class Type, class Allocator>
class vector
{
public:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

struct Gen000FB2E0Owner
{
	void *m_unknown00;
	_STL::vector<Rva000FB210Element, _STL::allocator<Rva000FB210Element> > m_vec;

	int Gen000FB2E0Method( unsigned int param1, bool param2 );
};

int Gen000FB2E0Owner::Gen000FB2E0Method( unsigned int param1, bool param2 )
{
	Rva000FB210Element temp( param1 );

	if ( param2 )
		temp.m_field2C = 0;

	_STL::vector<Rva000FB210Element, _STL::allocator<Rva000FB210Element> > &vec = m_vec;
	Rva000FB210Element *finish = vec._M_finish;
	if ( finish != vec._M_end_of_storage )
	{
		if ( finish != 0 )
			new ( finish ) Rva000FB210Element( temp );
		++vec._M_finish;
	}
	else
	{
		vec._M_insert_overflow( finish, temp,
			reinterpret_cast<const _STL::__false_type &>( temp ), 1, true );
	}

	return ( int )( vec._M_finish - vec._M_start ) - 1;
}

#pragma comment( linker, "/alternatename:??0Rva000FB210Element@@QAE@I@Z=?j_00032cc7@@YAXXZ" )
#pragma comment( linker, "/alternatename:??0Rva000FB210Element@@QAE@ABU0@@Z=?j_0004845f@@YAXXZ" )
