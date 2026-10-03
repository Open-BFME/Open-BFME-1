// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// 0x008FFB80 / 289 bytes. The named Rva00900FF0 constructors pass this
// 12-byte vector by value; the original copy-constructor alias is retained.
// Each element is a native narrow STLport string. Its three pointer fields,
// small/large allocator split, trailing null and copy semantics are witnessed
// by the retail loop and the 0x008FFA50 sibling's default-string ILT.
// Keep STLport's constructor and iterator layers: they determine spill order.
// BFME's allocation helper omits STLport's length-error path; the retail
// cmp -1 / ja and zero-count guard skip allocation without an extra call.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>
namespace _STL {
template<> __forceinline void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int n) {
 if(n<=max_size()+1 && n>0) {
  char *buffer;
  if(n>128) buffer=(char*)::operator new(n); else buffer=(char*)__node_alloc<true,0>::allocate(n);
  _M_start=buffer; _M_finish=buffer; _M_end_of_storage._M_data=buffer+n;
 }
}

template<> __forceinline basic_string<char,char_traits<char>,allocator<char> >::basic_string(const basic_string<char,char_traits<char>,allocator<char> >&source)
: _String_base<char,allocator<char> >(source.get_allocator()) {
 _M_range_initialize(source._M_start,source._M_finish);
}
}
class Rva00900FF0VecOfVec: public _STL::_Vector_base<_STL::string,_STL::allocator<_STL::string> > {
 typedef _STL::allocator<_STL::string> AllocT;
 typedef _STL::_Vector_base<_STL::string,AllocT> BaseT;
public:
 unsigned int size() const { return (unsigned int)(_M_finish-_M_start); }
 __declspec(noinline) AllocT get_allocator() const { return AllocT(); }
 Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &source);
};
template<class T1,class T2> __forceinline void Rva008FFB80Construct(T1 *p,const T2 &val) {new((void*)p) T1(val);}
struct Rva008FFB80FalseType {};
template<class Input,class Output> __forceinline Output Rva008FFB80Copy(Input first,Input last,Output result,const Rva008FFB80FalseType &) {
 Output cur=result; for(;first!=last;++first,++cur) Rva008FFB80Construct(&*cur,*first); return cur;
}
Rva00900FF0VecOfVec::Rva00900FF0VecOfVec(const Rva00900FF0VecOfVec &source):BaseT(source.size(),source.get_allocator()) {
 _M_finish=Rva008FFB80Copy((const _STL::string*)source._M_start,(const _STL::string*)source._M_finish,_M_start,Rva008FFB80FalseType());
}
