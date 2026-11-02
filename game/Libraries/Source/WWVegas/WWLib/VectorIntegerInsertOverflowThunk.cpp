// cl: /EHsc
// stlport

#include <cstring>

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);

#define memmove (*bfme_memmove_ptr)
#include <vector>
#undef memmove

template class _STL::vector<int>;
template void _STL::vector<int>::_M_initialize_aux<int>(int, int, const _STL::__true_type &);
