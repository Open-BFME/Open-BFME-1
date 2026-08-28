// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &other);

private:
	void *m_data;
};

struct Rva00360820Destination
{
	UnsignedInt m_first;
	UnsignedInt m_count;
	UnsignedInt m_second;
	UnsignedInt m_third;
	Bool m_active;
	UnicodeString m_text;
};

struct Rva00360820Source
{
	UnsignedByte m_pad0[0x3c];
	UnsignedInt m_first;
	UnsignedByte m_pad40[4];
	UnsignedInt m_second;
	UnsignedInt m_third;
	UnsignedByte m_pad4c[0x2c];
	UnicodeString m_text;
};

void rva00360820CopyInit(Rva00360820Destination *destination,
	const Rva00360820Source *source)
{
	destination->m_first = source->m_first;
	destination->m_text = source->m_text;
	destination->m_second = source->m_second;
	destination->m_third = source->m_third;
	destination->m_count = 0;
	destination->m_active = 0;
}
