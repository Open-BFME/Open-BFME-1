// cl: /DNDEBUG /MD /EHsc /Og-
// Open-BFME7: STLport __node_alloc<true,0>::_S_refill, retail 0x0082C920.
// The retail call at this body resolves to the recovered chunk allocator at
// 0x0082B550, and the LEA resolves to this instantiation's free-list table at
// 0x0130B1C0.

extern char *bfmeChunk1150(unsigned int size, int *nobjs);

namespace _STL
{

struct _Node_alloc_obj
{
    _Node_alloc_obj *_M_free_list_link;
};

template <bool __threads, int __inst>
class __node_alloc
{
    typedef _Node_alloc_obj _Obj;

    static _Obj * volatile _S_free_list[16];

    static void *_S_refill(unsigned int n);

    static char *_S_chunk_alloc(unsigned int size, int &nobjs)
    {
        return bfmeChunk1150(size, &nobjs);
    }

    static unsigned int _S_round_up(unsigned int bytes)
    {
        return (bytes + 7) & ~7;
    }
};

template <bool __threads, int __inst>
void *__node_alloc<__threads, __inst>::_S_refill(unsigned int n)
{
    struct RefillLocals
    {
        _Obj *current_obj;
        _Obj *next_obj;
        int i;
        int nobjs;
        char *chunk;
        _Obj *result;
        _Obj * volatile *my_free_list;
    } locals;

    locals.nobjs = 20;
    n = _S_round_up(n);
    locals.chunk = _S_chunk_alloc(n, locals.nobjs);

    if (1 == locals.nobjs)
        return locals.chunk;
    locals.my_free_list = _S_free_list + ((n - 1) >> 3);
    locals.result = (_Obj *)locals.chunk;
    *locals.my_free_list = locals.next_obj = (_Obj *)(locals.chunk + n);
    for (locals.i = 1; ; locals.i++) {
        locals.current_obj = locals.next_obj;
        locals.next_obj = (_Obj *)((char *)locals.next_obj + n);
        if (locals.nobjs - 1 == locals.i) {
            locals.current_obj->_M_free_list_link = 0;
            break;
        } else {
            locals.current_obj->_M_free_list_link = locals.next_obj;
        }
    }
    return locals.result;
}

template void *__node_alloc<true, 0>::_S_refill(unsigned int);

}
