// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The carved body at retail RVA 0x00142250 destroys a 20-byte vector element.
// Each element owns two four-byte strings and releases them in reverse order.

#include <vector>

class BFMERetailAsciiString
{
private:
	void releaseBuffer();
	void *m_data;

public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}
};

struct Rva00142250Nugget
{
	BFMERetailAsciiString first;
	BFMERetailAsciiString second;
	unsigned char m_padding[12];

	~Rva00142250Nugget()
	{
	}
};

template class _STL::vector<Rva00142250Nugget>;
