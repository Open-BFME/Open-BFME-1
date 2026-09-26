// cl: /DNDEBUG /MD /EHsc

// Retail 0x00023592 jumps directly to the matched PSResponse deque
// pop_front body at 0x00656BD0. The queue pin and popQueue1 caller prove the
// BFMENetworkQueue1::popFront identity.
class PSResponse;

namespace _STL
{
template <class Type> class allocator;

template <class Type, class Allocator> class deque
{
public:
	void pop_front();
};
}

class BFMENetworkQueue1
{
public:
	void popFront();
};

void BFMENetworkQueue1::popFront()
{
	reinterpret_cast<_STL::deque<PSResponse, _STL::allocator<PSResponse> > *>(this)->pop_front();
}
