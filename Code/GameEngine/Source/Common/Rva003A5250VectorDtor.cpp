// cl: /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// STLport vector destructor at retail 0x003A5250.  The destroy loop advances
// by 0x14 bytes and releases two narrow-string members at offsets +8 and
// +0xC.  The neighboring 0x003A53D0 vector destructor and the matched
// Gen003A4310 element destructor establish the family and member layout.

class BFMERetailAsciiString
{
public:
	__forceinline ~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	__forceinline void reset()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

class Rva003A5250Element
{
public:
	~Rva003A5250Element()
	{
		m_fieldA.reset();
		m_fieldB.reset();
	}

private:
	unsigned char m_pad00[8];
	BFMERetailAsciiString m_fieldA;
	BFMERetailAsciiString m_fieldB;
	unsigned char m_tail[4];
};

#include <vector>

template class _STL::vector<Rva003A5250Element>;
