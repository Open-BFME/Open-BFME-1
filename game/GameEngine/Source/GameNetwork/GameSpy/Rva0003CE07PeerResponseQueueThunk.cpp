// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB

#define _STLP_NO_EXCEPTIONS 1

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class deque
{
};

template <class Type, class Sequence>
class queue
{
public:
	void push(const Type &value);
};
}

class PeerResponse
{
	char m_bfmeBody[0x330];
};

class Rva0003CE07PeerResponseQueueThunk
	: public _STL::queue<PeerResponse,
		_STL::deque<PeerResponse, _STL::allocator<PeerResponse> > >
{
public:
	void forward(const PeerResponse &value);
};

void Rva0003CE07PeerResponseQueueThunk::forward(const PeerResponse &value)
{
	this->push(value);
}
