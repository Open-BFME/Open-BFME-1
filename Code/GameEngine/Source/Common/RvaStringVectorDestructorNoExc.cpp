// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: STLport vector<string>::~vector, two copies (retail 0x00201590
// and 0x006A6CF0, 143 bytes each) that are byte twins of Science.cpp's
// vector<AsciiString> destructor once _STLP_NO_EXCEPTIONS removes the
// try/catch from the STLport helpers.  The element destructor is reached
// through the out-of-line __destroy_aux helper, which MSVC 7.1 only keeps out
// of line when the element destructor is a heavy inline (the reference-counted
// release with InterlockedDecrement and freeBytes): each copy gets an
// address-derived string tag with that destructor shape, one decorated name
// per address.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

extern "C" long __stdcall InterlockedDecrement( long volatile *addend );

struct RvaStringVectorData
{
	long m_refCount;
	int m_numCharsAllocated;
};

class Rva00201590String
{
public:
	~Rva00201590String()
	{
		if ( m_data )
		{
			if ( InterlockedDecrement( &m_data->m_refCount ) == 0 )
				freeBytes();
		}
	}
private:
	void freeBytes( void );
	RvaStringVectorData *m_data;
};

class Rva006A6CF0String
{
public:
	~Rva006A6CF0String()
	{
		if ( m_data )
		{
			if ( InterlockedDecrement( &m_data->m_refCount ) == 0 )
				freeBytes();
		}
	}
private:
	void freeBytes( void );
	RvaStringVectorData *m_data;
};

template _STL::vector<Rva00201590String, _STL::allocator<Rva00201590String> >::~vector();
template _STL::vector<Rva006A6CF0String, _STL::allocator<Rva006A6CF0String> >::~vector();
