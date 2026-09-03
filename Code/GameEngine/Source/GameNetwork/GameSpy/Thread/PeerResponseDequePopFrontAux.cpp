// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME5: STLport deque<PeerResponse>::_M_pop_front_aux, retail 0x00647A80.

void __cdecl operator delete( void *memory );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerThread.h
class PeerResponse
{
public:
	~PeerResponse();

private:
	unsigned char m_unreconstructed[0x330];
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class deque
{
protected:
	void _M_pop_front_aux();

private:
	Type *m_startCurrent;
	Type *m_startFirst;
	Type *m_startLast;
	Type **m_startNode;
};

template <class Type, class Allocator>
void deque<Type, Allocator>::_M_pop_front_aux()
{
	m_startCurrent->~Type();
	if (m_startFirst != 0)
		::operator delete( m_startFirst );
	++m_startNode;
	m_startFirst = *m_startNode;
	m_startLast = m_startFirst + 1;
	m_startCurrent = m_startFirst;
}

template void deque<PeerResponse, allocator<PeerResponse> >::_M_pop_front_aux();
}
