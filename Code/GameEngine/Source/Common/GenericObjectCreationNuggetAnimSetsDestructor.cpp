// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

#include <new>

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_text;
};

struct GenericObjectCreationAnimSet
{
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
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

class GenericObjectCreationAnimSetStorage
{
protected:
	GenericObjectCreationAnimSet *m_begin;
	GenericObjectCreationAnimSet *m_end;
	GenericObjectCreationAnimSet *m_capacity;

	__forceinline ~GenericObjectCreationAnimSetStorage()
	{
		if ( m_begin )
		{
			const unsigned int bytes =
				( m_capacity - m_begin ) * sizeof( GenericObjectCreationAnimSet );
			_STL::__node_alloc<true, 0>::deallocate( m_begin, bytes );
		}
	}
};

class GenericObjectCreationNuggetAnimSets
	: private GenericObjectCreationAnimSetStorage
{
public:
	~GenericObjectCreationNuggetAnimSets();
};

GenericObjectCreationNuggetAnimSets::~GenericObjectCreationNuggetAnimSets()
{
	GenericObjectCreationAnimSet *item = m_begin;
	GenericObjectCreationAnimSet *finish = m_end;
	for ( ; item != finish; ++item )
	{
		item->~GenericObjectCreationAnimSet();
	}
}
