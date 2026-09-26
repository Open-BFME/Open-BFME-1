// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <ios>
#include <string>

namespace _STL {
ios_base::failure::failure(const string &message) : __Named_exception(message)
{
}
}
