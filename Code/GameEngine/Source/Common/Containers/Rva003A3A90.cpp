// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// 0x003A3A90 builds a temporary 0xB8 element, inserts it at begin() in the
// vector at this+0x2C, then destroys the temporary. The default constructor's
// ILT 0x22F0C reaches 0x003A18D0; the element destructor's ILT 0x36241 reaches
// 0x002BC7A0. The owner remains address-qualified.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva003A35A0Element
{
	Rva003A35A0Element();
	Rva003A35A0Element(const Rva003A35A0Element &);
	~Rva003A35A0Element();
	Rva003A35A0Element &operator=(const Rva003A35A0Element &);

	unsigned int m_words[46];
};

struct Rva003A3A90Input
{
	unsigned int m_word00, m_word04, m_word08;
};

class Rva003A3A90Owner
{
public:
	void insert(const Rva003A3A90Input &value);

private:
	unsigned char m_prefix[0x2C];
	_STL::vector<Rva003A35A0Element> m_records;
};

void Rva003A3A90Owner::insert(const Rva003A3A90Input &value)
{
	Rva003A35A0Element temporary;
	temporary.m_words[41] = value.m_word00;
	temporary.m_words[42] = value.m_word04;
	temporary.m_words[43] = value.m_word08;
	m_records.insert(m_records.begin(), temporary);
}
