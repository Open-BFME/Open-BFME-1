// ?rva00901160@@YAHAAV?$vector@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$allocator@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@@_STL@@PBD1@Z
// partial score=0.59430605 date=2026-09-28
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string>
namespace _STL {
void *__cdecl vectorLargeAllocate(unsigned int);
void *__cdecl vectorSmallAllocate(unsigned int);
template<> __forceinline void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int n) {
 if(n<=max_size()+1 && n>0) {
  char *buffer;
  if(n>128) buffer=(char*)vectorLargeAllocate(n); else buffer=(char*)vectorSmallAllocate(n);
  _M_end_of_storage._M_data=buffer+n; _M_start=buffer; _M_finish=buffer;
 }
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
template<> __forceinline basic_string<char,char_traits<char>,allocator<char> >::basic_string(const char *text,const allocator<char> &a)
: _String_base<char,allocator<char> >(a) {
 _M_range_initialize(text,text+char_traits<char>::length(text));
}
}
namespace _STL {
template<> __forceinline void _Construct<string,string>(string *p,const string &val) {new((void*)p) string(val);}
template<> __forceinline void vector<string,allocator<string> >::push_back(const string &x) {
 if(_M_finish!=_M_end_of_storage._M_data) { _Construct(_M_finish,x); ++_M_finish; }
 else _M_insert_overflow(_M_finish,x,__false_type(),1,true);
}
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
