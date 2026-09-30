// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0053CA40: STLport formatted long extractor helper, not an inserter.
// _M_init_skip/_M_init_noskip callees and num_get::do_get slot 0x28 prove
// this specialization; exceptions-disabled library removes catch machinery.
#define _STLP_NO_EXCEPTIONS 1
#include <istream>
template _STL::ios_base::iostate _STLP_CALL _STL::_M_get_num<char, _STL::char_traits<char>, long>(_STL::basic_istream<char, _STL::char_traits<char> > &, long &);
