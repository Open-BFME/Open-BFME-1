namespace _STL
{

template <class T> class allocator;

template <class T, class Allocator> class deque
{
public:
	void pop_front();
};

}

class PeerRequest;

class Rva0002D77CPeerRequestDeque
{
public:
	void pop_front();
};

void Rva0002D77CPeerRequestDeque::pop_front()
{
	(( _STL::deque<PeerRequest, _STL::allocator<PeerRequest> > *)this)->pop_front();
}
