// cl: /O2 /Ob0

namespace _STL
{

template <int Instance>
struct _STLP_mutex_spin
{
    static void __cdecl _M_do_lock(volatile long *lock);
};

}

struct Rva008327E0
{
    volatile long *m_00;
    Rva008327E0 *method(volatile long *lock);
};

Rva008327E0 *Rva008327E0::method(volatile long *lock)
{
    m_00 = lock;
    _STL::_STLP_mutex_spin<0>::_M_do_lock(lock);
    return this;
}
