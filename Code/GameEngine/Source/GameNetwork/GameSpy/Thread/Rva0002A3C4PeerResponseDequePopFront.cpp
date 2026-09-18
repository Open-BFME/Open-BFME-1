namespace _STL
{

template <class T> class allocator;

template <class T, class Allocator> class deque
{
public:
	void pop_front();
};

}

class PeerResponse;

class Rva0002A3C4PeerResponseDeque
{
public:
	void pop_front();
};

void Rva0002A3C4PeerResponseDeque::pop_front()
{
	(( _STL::deque<PeerResponse, _STL::allocator<PeerResponse> > *)this)->pop_front();
}
