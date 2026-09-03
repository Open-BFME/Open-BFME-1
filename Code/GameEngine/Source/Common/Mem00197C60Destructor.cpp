// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

#include <new>

class Mem00197C60;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
	friend class Mem00197C60;
	void releaseData();
};

struct Mem00197C60Element
{
	unsigned int m_payload[ 3 ];
	Dict m_dictionary;
};

namespace _STL
{

template <bool Threads, int Instance>
class __node_alloc
{
	static void _M_deallocate( void *storage, unsigned int bytes );

public:
	static void deallocate( void *storage, unsigned int bytes )
	{
		if ( bytes > 128 )
			::operator delete( storage );
		else
			_M_deallocate( storage, bytes );
	}
};

}

class Mem00197C60Storage
{
protected:
	Mem00197C60Element *m_begin;
	Mem00197C60Element *m_end;
	Mem00197C60Element *m_capacity;

	__forceinline ~Mem00197C60Storage()
	{
		if ( m_begin )
		{
			const unsigned int bytes =
				( m_capacity - m_begin ) * sizeof( Mem00197C60Element );
			_STL::__node_alloc<true, 0>::deallocate( m_begin, bytes );
		}
	}
};

class Mem00197C60 : private Mem00197C60Storage
{
public:
	~Mem00197C60();
};

Mem00197C60::~Mem00197C60()
{
	Mem00197C60Element *finish = m_end;
	Mem00197C60Element *item = m_begin;
	for ( ; item != finish; ++item )
		item->m_dictionary.releaseData();
}
