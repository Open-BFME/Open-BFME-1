// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

struct Rva002DC3D0Element
{
    int a[2];
};

struct Gen_t_002dbcb0_p8cd
{
    int a[2];
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

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

template <class Type>
__forceinline Type *copyPod(Type *first, Type *last, Type *result)
{
    if (first != last)
    {
        do
        {
            if (result)
                *result = *first;
            ++first;
            ++result;
        }
        while (first != last);
    }
    return result;
}

template <class Type>
__forceinline Type *fillPod(Type *result, unsigned int count,
    const Type &value)
{
    for (; count > 0; --count)
    {
        if (result)
            *result = value;
        ++result;
    }
    return result;
}

template <class Type, class Allocator>
class vector
{
    template <class, class>
    friend class vector;

protected:
    void _M_insert_overflow(Type *position, const Type &value,
        const __false_type &, unsigned int fillLength, bool atEnd);

    void _M_clear();

    Type *_M_start;
    Type *_M_finish;
    Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
    Type *position, const Type &value, const __false_type &,
    unsigned int fillLength, bool atEnd)
{
    Type *newStart;
    unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
    const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
    unsigned int length = growth + oldSize;

    if (length)
    {
        unsigned int bytes = length * sizeof(Type);
        if (bytes > 128)
            newStart = (Type *)vectorLargeAllocate(bytes);
        else
            newStart = (Type *)vectorSmallAllocate(bytes);
    }
    else
    {
        newStart = 0;
    }

    Type *newFinish = copyPod(_M_start, position, newStart);
    if (fillLength == 1)
    {
        if (newFinish)
            *newFinish = value;
        ++newFinish;
    }
    else
    {
        newFinish = fillPod(newFinish, fillLength, value);
    }

    if (!atEnd)
        newFinish = copyPod(position, _M_finish, newFinish);

    typedef vector<Gen_t_002dbcb0_p8cd,
        allocator<Gen_t_002dbcb0_p8cd> > ClearVector;
    ((ClearVector *)this)->_M_clear();
    _M_finish = newFinish;
    _M_start = newStart;
    _M_end_of_storage = newStart + length;
}

template class vector<Rva002DC3D0Element,
    allocator<Rva002DC3D0Element> >;
}
