// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva003A3B50Input
{
	int word00, word04, word08;
};

struct Rva003A35A0Element
{
	unsigned char m_prefix[0xA4];
	Rva003A3B50Input m_point;
	unsigned char m_tail[8];

	// Existing default-constructor symbol reaches body0x003A18D0 through ILT0x22F0C.
	Rva003A35A0Element();
	Rva003A35A0Element( const Rva003A35A0Element & );
	~Rva003A35A0Element();
	Rva003A35A0Element &operator=( const Rva003A35A0Element &other );
};

class Rva003A3B50Owner
{
public:
	void append( const Rva003A3B50Input *value );

private:
	char m_unreconstructed_00[ 0x2C ];
	_STL::vector<Rva003A35A0Element> m_elements;
};

// ?append@Rva003A3B50Owner@@QAEXPBURva003A3B50Input@@@Z
void Rva003A3B50Owner::append( const Rva003A3B50Input *value )
{
	Rva003A35A0Element element;
	element.m_point = *value;
	m_elements.push_back( element );
}
