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
	class __new_alloc
	{
	public:
		static void *allocate( unsigned int bytes );
	};
}

void operator delete( void *pointer );
void *operator new( unsigned int bytes );

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

struct Rva009ED0A0Element
{
	char m_data[ 12 ];
};

class Rva009ED0A0Allocator
{
public:
	void deallocate( void *pointer, unsigned int count );
};

void Rva009ED0A0Allocator::deallocate( void *pointer, unsigned int count )
{
	if ( pointer != 0 )
	{
		unsigned int bytes = count * sizeof( Rva009ED0A0Element );
		if ( bytes > 128 )
			operator delete( pointer );
		else
			_STL::__node_alloc< true, 0 >::_M_deallocate( pointer, bytes );
	}
}

class Rva009ED450Allocator
{
public:
	void deallocate( void *pointer, unsigned int count );
};

void Rva009ED450Allocator::deallocate( void *pointer, unsigned int count )
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

class Rva009ECD20Allocator
{
public:
	void *allocate( unsigned int count, const void *hint );
};

void *Rva009ECD20Allocator::allocate( unsigned int count, const void * )
{
	if ( count != 0 )
	{
		unsigned int bytes = count * sizeof( Rva009F4AF0Element );
		if ( bytes > 128 )
			return operator new( bytes );
		return _STL::__new_alloc::allocate( bytes );
	}
	return 0;
}

class Rva009F4AB0Allocator
{
public:
	void *allocate( unsigned int count, const void *hint );
};

void *Rva009F4AB0Allocator::allocate( unsigned int count, const void * )
{
	if ( count != 0 )
	{
		unsigned int bytes = count * sizeof( Rva009F4AF0Element );
		if ( bytes > 128 )
			return operator new( bytes );
		return _STL::__new_alloc::allocate( bytes );
	}
	return 0;
}
