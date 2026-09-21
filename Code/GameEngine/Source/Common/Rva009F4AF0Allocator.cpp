// cl: /DNDEBUG /MD /EHs-c-

struct Rva009F4AF0Element
{
	char m_data[ 24 ];
};

namespace _STL
{
	template < bool threads, int instance >
	class __node_alloc
	{
	public:
		static void _M_deallocate( void *pointer, unsigned int bytes );
	};
}

void operator delete( void *pointer );

class Rva009F4AF0Allocator
{
public:
	void deallocate( void *pointer, unsigned int count );
};

void Rva009F4AF0Allocator::deallocate( void *pointer, unsigned int count )
{
	if ( pointer != 0 )
	{
		unsigned int bytes = count * sizeof( Rva009F4AF0Element );
		if ( bytes > 128 )
			operator delete( pointer );
		else
			_STL::__node_alloc< true, 0 >::_M_deallocate( pointer, bytes );
	}
}
