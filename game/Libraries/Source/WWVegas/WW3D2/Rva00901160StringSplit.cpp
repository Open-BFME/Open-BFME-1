// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// 0x00901160: splits text on the delimiter set into a vector of strings and returns its size.
// Retail inlines STLport's string construction; the specializations force the native bodies inline.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>
namespace _STL {
template<> __forceinline void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int n) {
 if((n<=(max_size()+1)) && (n>0)) {
  _M_start=_M_end_of_storage.allocate(n);
  _M_finish=_M_start;
  _M_end_of_storage._M_data=_M_start+n;
 }
 else
  _M_throw_length_error();
}

template<> template<> __forceinline void basic_string<char,char_traits<char>,allocator<char> >::_M_range_initialize<char *>(char *first,char *last,const forward_iterator_tag &) {
 int n=distance(first,last);
 _M_allocate_block(n+1);
 _M_finish=uninitialized_copy(first,last,_M_start);
 _M_terminate_string();
}
template<> template<> __forceinline void basic_string<char,char_traits<char>,allocator<char> >::_M_range_initialize<char *>(char *first,char *last) {
 _M_range_initialize(first,last,random_access_iterator_tag());
}
template<> __forceinline basic_string<char,char_traits<char>,allocator<char> >::basic_string(const basic_string<char,char_traits<char>,allocator<char> >&source)
: _String_base<char,allocator<char> >(source.get_allocator()) {
 _M_range_initialize(source._M_start,source._M_finish);
}
}
namespace _STL {
template<> __forceinline void _Construct<string,string>(string *p,const string &val) {new((void*)p) string(val);}
}

#include <string.h>
int rva00901160(_STL::vector<_STL::string> &out,const char *text,const char *delimiters) {
 out.clear();
 char buffer[2048];
 strcpy(buffer,text);
 for(char *token=strtok(buffer,delimiters);token;token=strtok(0,delimiters)) {
  out.push_back(_STL::string(token));
 }
 return out.size();
}
