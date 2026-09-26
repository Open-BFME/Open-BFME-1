// cl: /DNDEBUG /MD /EHsc /Og-
// Open-BFME7: STLport __node_alloc<false,0>::_S_refill, retail 0x0082C870.
// The retail body calls the recovered chunk allocator at 0x0082B3A0 and uses
// the false-thread free-list table at 0x0130B210.

extern char *bfmeChunk1149(unsigned int size, int *nobjs);
extern char *g_bfmeFreeList1149[];

namespace _STL
{

template <bool __threads, int __inst>
class __node_alloc
{
    struct _Obj
    {
        _Obj *_M_free_list_link;
    };

    static void *_S_refill(unsigned int n);

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
    locals.chunk = bfmeChunk1149(n, &locals.nobjs);

    if (1 == locals.nobjs)
        return locals.chunk;
    locals.my_free_list = (_Obj * volatile *)g_bfmeFreeList1149 + ((n - 1) >> 3);
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

template void *__node_alloc<false, 0>::_S_refill(unsigned int);

}
