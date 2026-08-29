// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Two more instantiations of STLport's vector::_M_insert_overflow, landed as
// relocation-blind twins of
// Code/GameEngine/Source/Common/AsciiStringVectorInsert.cpp (0x00757C70).
// Each differs from the model in exactly two callees: the element's copy
// constructor (reached four times, once per move in the grow) and the
// routine that releases the old buffer.
//
// The element type is not recoverable from these bytes -- only its size (one
// pointer), that it has a non-trivial copy constructor and that it has a
// destructor -- so each is named after the body's address.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Open2Elem063700
{
public:
	Open2Elem063700( const Open2Elem063700 &other );		// retail ILT 0x00007554
	~Open2Elem063700();					// retail ILT 0x0003588C

	void *m_data;
};

void Open2VectorAnchor063700( _STL::vector<Open2Elem063700> &v, const Open2Elem063700 &value )
{
	v.insert( v.begin(), value );
}

class Open2Elem247180
{
public:
	Open2Elem247180( const Open2Elem247180 &other );		// retail ILT 0x00028308
	~Open2Elem247180();					// retail ILT 0x00022534

	void *m_data;
};

void Open2VectorAnchor247180( _STL::vector<Open2Elem247180> &v, const Open2Elem247180 &value )
{
	v.insert( v.begin(), value );
}
