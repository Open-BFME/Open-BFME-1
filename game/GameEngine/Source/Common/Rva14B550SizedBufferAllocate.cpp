namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }
}

extern "C" void *__stdcall Rva14B550SizedBufferAllocate(unsigned int count, int)
{
    if (count != 0) {
        unsigned int size = count * 12;
        if (size > 128) {
            return _STL::vectorLargeAllocate(size);
        }

        return _STL::vectorSmallAllocate(size);
    }

    return 0;
}
