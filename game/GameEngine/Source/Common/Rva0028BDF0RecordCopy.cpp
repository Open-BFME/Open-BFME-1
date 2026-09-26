// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

#include "ascii_string.h"

struct Rva0028BDF0Record
{
	UnsignedInt m_first;
	UnsignedByte m_flag;
	UnsignedByte m_padding[3];
	UnsignedInt m_second;
	AsciiString m_text;
	UnsignedInt m_third;
	UnsignedInt m_tailPadding;
};

class Rva0028BDF0Object
{
public:
	Rva0028BDF0Object &operator=(const Rva0028BDF0Object &other);

private:
	UnsignedByte m_header[8];
	Rva0028BDF0Record m_records[3];
};

Rva0028BDF0Object &Rva0028BDF0Object::operator=(const Rva0028BDF0Object &other)
{
	for (UnsignedInt i = 0; i < 3; ++i) {
		m_records[i].m_first = other.m_records[i].m_first;
		m_records[i].m_flag = other.m_records[i].m_flag;
		m_records[i].m_second = other.m_records[i].m_second;
		m_records[i].m_text = other.m_records[i].m_text;
		m_records[i].m_third = other.m_records[i].m_third;
	}

	return *this;
}
