// cl: /O2 /MD /EHsc
//
// Open-BFME7: the throw path at 0x00522830 constructs std::exception, stores
// vftable 0x010766DC, and throws with the image's FunctorNotSet RTTI.  Slot
// zero of that vftable reaches 0x0007B640 through ILT 0x0003C5A6; its sole
// destructor call reaches the imported std::exception destructor through
// ILT 0x0003B89F.

#include <exception>

class FunctorNotSet : public std::exception
{
public:
	virtual ~FunctorNotSet();
};

FunctorNotSet::~FunctorNotSet()
{
}
