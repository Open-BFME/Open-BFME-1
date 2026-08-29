// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Two more two-iterator vector erases, landed as relocation-blind twins of
// Code/GameEngine/Source/Common/RTS/PlayerTemplate.cpp (0x000E3E60).  Each
// differs from the model in two callees: the __copy that closes the gap and
// the element destructor that runs over the tail.
//
// The element size is what the destructor loop's stride says: 0x88 for one
// and 0xb8 for the other.  They still normalise the same, because the
// relocation-blind hash blanks any four-byte window that reads as an image
// address and `81 c6 88 00 00 00` contains one -- a reminder that the search
// finds CANDIDATES and the byte check is the judge.  Nothing else about the
// element is observable here, so each is named after its own address.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class Open2Elem39EB70
{
public:
	~Open2Elem39EB70();

private:
	char m_storage[ 0x88 ];
};

class Open2Elem3A3280
{
public:
	~Open2Elem3A3280();

private:
	char m_storage[ 0xb8 ];
};

void Open2EraseAnchor39EB70( _STL::vector<Open2Elem39EB70> &target,
	Open2Elem39EB70 *first, Open2Elem39EB70 *last )
{
	target.erase( first, last );
}

void Open2EraseAnchor3A3280( _STL::vector<Open2Elem3A3280> &target,
	Open2Elem3A3280 *first, Open2Elem3A3280 *last )
{
	target.erase( first, last );
}
