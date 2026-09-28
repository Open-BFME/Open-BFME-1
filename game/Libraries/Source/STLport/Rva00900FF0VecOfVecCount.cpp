// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// 0x008FFA50 / 301 bytes -- count constructor of the
// vector<basic_string<char>>-shaped container witnessed by
// Rva00900FF0Constructor.cpp (base ctor at retail 0x008FF3E0, already
// matched via gen_small/tgrid_122.cpp's vec_p12cd instantiation). Each
// inner element is a 12-byte {start,finish,endOfStorage} string buffer
// (no SSO) matching stlport_narrow_string_reserve.cpp's allocator split.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>

extern "C" __declspec(dllimport) void *__cdecl BfmeMemMove(void *dest, const void *src, unsigned int count);

namespace _STL {
void *__cdecl vectorLargeAllocate(unsigned int);
void *__cdecl vectorSmallAllocate(unsigned int);
void __cdecl vectorLargeDeallocate(void *);
}

struct Rva008FFB80StringBase
{
	char *m_start;
	char *m_finish;
	char *m_endOfStorage;
 Rva008FFB80StringBase():m_start(0),m_finish(0),m_endOfStorage(0) {}
 __forceinline ~Rva008FFB80StringBase() {
  unsigned int bytes=m_endOfStorage-m_start;
  if(m_start) {
   if(bytes>128) _STL::vectorLargeDeallocate(m_start);
   else _STL::allocator<char>().deallocate(m_start,bytes);
  }
 }
};

__forceinline void Rva008FFB80Allocate(Rva008FFB80StringBase *self,unsigned int capacity) {
 if(capacity <= ((unsigned int)-1 / sizeof(char) - 1) + 1 && capacity > 0) {
  char *buffer;
  if(capacity > 128) buffer=(char*)_STL::vectorLargeAllocate(capacity);
  else buffer=(char*)_STL::vectorSmallAllocate(capacity);
  self->m_start=buffer; self->m_finish=buffer; self->m_endOfStorage=buffer+capacity;
 }
}
inline char *Rva008FFB80Copy(const char *first,const char *last,char *dest) {
 return last==first?dest:(char*)BfmeMemMove(dest,first,last-first)+(last-first);
}
struct Gen_t_008ff3e0_p12cd: Rva008FFB80StringBase {
 __forceinline Gen_t_008ff3e0_p12cd(const _STL::string &source) {
  const char *first=source.begin(); const char *last=source.end();
  Rva008FFB80Allocate(this,(unsigned int)(last-first)+1);
  m_finish=Rva008FFB80Copy(first,last,m_start);
  *m_finish=0;
 }
};
class Rva00900FF0VecOfVec
	: public _STL::_Vector_base<Gen_t_008ff3e0_p12cd, _STL::allocator<Gen_t_008ff3e0_p12cd> >
{
	typedef _STL::allocator<Gen_t_008ff3e0_p12cd> AllocT;
	typedef _STL::_Vector_base<Gen_t_008ff3e0_p12cd, AllocT> BaseT;

public:
	Rva00900FF0VecOfVec(int n);

	unsigned int size() const { return (unsigned int)(_M_finish - _M_start); }
	__declspec(noinline) AllocT get_allocator() const { return AllocT(); }
};
struct Rva008FFB80FalseType {};
template <class T1,class T2> __forceinline void Rva008FFB80Construct(T1 *p,const T2 &val) { new((void*)p) T1(val); }
template <class Output,class Size,class T> __forceinline Output Rva008FFA50UninitializedFill(Output first,Size n,const T &value) {
 Output cur=first;
 for(;n>0;--n,++cur) Rva008FFB80Construct(&*cur,value);
 return cur;
}
Rva00900FF0VecOfVec::Rva00900FF0VecOfVec(int n)
 : BaseT(n,AllocT()) {
 _M_finish=Rva008FFA50UninitializedFill(_M_start,(unsigned int)n,_STL::string());
}


// The default string constructor is called through ILT 0x0004048A,
// which jumps to the native narrow-string constructor at 0x004D4F40.
