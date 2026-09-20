// cl: /DNDEBUG /MD /EHsc

// Retail 0x0002491A jumps directly to the matched PSRequest deque
// pop_front body at 0x00656B60. The queue pin and popQueue0 caller prove the
// BFMENetworkQueue::popFront identity.
class PSRequest;

namespace _STL
{
template <class Type> class allocator;

template <class Type, class Allocator> class deque
{
public:
	void pop_front();
};
}

class BFMENetworkQueue
{
public:
	void popFront();
};

void BFMENetworkQueue::popFront()
{
	reinterpret_cast<_STL::deque<PSRequest, _STL::allocator<PSRequest> > *>(this)->pop_front();
}
