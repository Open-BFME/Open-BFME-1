// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean reconstruction of the 0x0077C1F0 S4Base destructor.
// The member offsets and unwind order are taken from the retail body.  The
// Member destructor calls name the exact matched STLport specializations.
// Declaration-only one-byte views preserve the existing padding and offsets.

class Inner01073744
{
public:
	virtual ~Inner01073744() {}
};

#include "ascii_string.h"

#define S4_MEMBER( NAME, SIZE ) \
	class NAME \
	{ \
	public: \
		~NAME(); \
	private: \
		char m_body[ SIZE ]; \
	}

struct Gen0002306F;
struct Gen0004A1C4;
struct Rva00779CF0Element;
struct Rva0077AD90Element;
struct Gen0002A8BA;
struct Gen00770440;

namespace _STL
{
template <class Value> class allocator;
template <class Value, class Alloc> class vector
{
public:
    ~vector();
private:
    char m_body[1];
};
}

S4_MEMBER(S4Elem007746E0, 1);
S4_MEMBER( Rva00146BA0ArrayItem, 0x14 );

class S4Base0077C1F0 : public Inner01073744
{
public:
	virtual ~S4Base0077C1F0();

private:
	char m_pad04[ 4 ];
	_STL::vector<Rva0077AD90Element, _STL::allocator<Rva0077AD90Element> > m_at08;
	char m_pad09[ 0x0B ];
	AsciiString m_at14;
	_STL::vector<Gen0002306F, _STL::allocator<Gen0002306F> > m_at18;
	char m_pad19[ 0x0B ];
	_STL::vector<Gen0004A1C4, _STL::allocator<Gen0004A1C4> > m_at24;
	char m_pad25[ 0x0B ];
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_at30;
	char m_pad31[ 0x0B ];
	AsciiString m_at3c;
	AsciiString m_at40;
	AsciiString m_at44;
	AsciiString m_at48;
	char m_pad4c[ 0x20 ];
	_STL::vector<Gen0002A8BA, _STL::allocator<Gen0002A8BA> > m_at6c;
	char m_pad6d[ 0x0B ];
	_STL::vector<Rva00779CF0Element, _STL::allocator<Rva00779CF0Element> > m_at78;
	char m_pad79[ 0x0B ];
	S4Elem007746E0 m_at84;
	char m_pad85[ 0x5B ];
	AsciiString m_ate0;
	AsciiString m_ate4;
	AsciiString m_ate8;
	AsciiString m_atec;
	_STL::vector<Gen00770440, _STL::allocator<Gen00770440> > m_atf0;
	char m_padf1[ 0x43 ];
	Rva00146BA0ArrayItem m_items[ 2 ];
};

// ??1S4Base0077C1F0@@UAE@XZ
S4Base0077C1F0::~S4Base0077C1F0()
{
}
