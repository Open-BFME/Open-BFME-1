// cl: /DNDEBUG /MD /EHs-c-

struct Rva009F4AF0Element
{
	char m_data[ 24 ];
};

namespace _STL
{
	// The node allocator's pool entry points are private STLport members
	// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
	// 0x0082E5F0); these TU-local helpers reach them under their real names.
	template <bool __threads, int __inst> class __node_alloc;
	static void nodePoolDeallocate(void *block, unsigned int bytes);
	static __forceinline void *nodePoolAllocate(unsigned int bytes);
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend void nodePoolDeallocate(void *, unsigned int);
		friend void *nodePoolAllocate(unsigned int);
		static void *__cdecl _M_allocate(unsigned int __n);
		static void __cdecl _M_deallocate(void *__p, unsigned int __n);
	};
	static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
	static __forceinline void *nodePoolAllocate(unsigned int bytes)
	{
		return __node_alloc<true, 0>::_M_allocate(bytes);
	}

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
			_STL::nodePoolDeallocate( pointer, bytes );
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
			_STL::nodePoolDeallocate( pointer, bytes );
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
			_STL::nodePoolDeallocate( pointer, bytes );
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
		return _STL::nodePoolAllocate( bytes );
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
		return _STL::nodePoolAllocate( bytes );
	}
	return 0;
}
