// cl: /DNDEBUG /MD /EHsc
// Retail 0x00064640 is a seven-dword thiscall copy body. The record owner remains address-derived.

class Rva00064640Record
{
public:
	Rva00064640Record( const Rva00064640Record &other );

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	unsigned int m_18;
};

// ??0Rva00064640Record@@QAE@ABV0@@Z
Rva00064640Record::Rva00064640Record( const Rva00064640Record &other )
	: m_00( other.m_00 ),
	  m_04( other.m_04 ),
	  m_08( other.m_08 ),
	  m_0C( other.m_0C ),
	  m_10( other.m_10 ),
	  m_14( other.m_14 ),
	  m_18( other.m_18 )
{
}
