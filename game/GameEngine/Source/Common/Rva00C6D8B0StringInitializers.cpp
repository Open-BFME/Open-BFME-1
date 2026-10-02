// cl: /O2 /Ob2 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 35-byte string global initializers use the existing out-of-line
// STLport from-pointer constructor, its native one-byte allocator temporary,
// and the matched cleanup for each global. The explicit specialization
// declarations keep the header body from being inlined at these call sites.
// The constructor providers remain the existing matched instantiations;
// no new constructor definition, pin or application-level name is introduced.
#include <string>
namespace _STL {
template<> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const char*, const allocator<char>&);
template<> basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >::basic_string(const wchar_t*, const allocator<wchar_t>&);
}
extern "C" int __cdecl atexit(void (__cdecl *)());

class Gen_00C70CC0Target;
extern Gen_00C70CC0Target TheBfmeObject_00C70CC0;
void bfmeForward_00C70CC0();
void rva00C6D8B0Initialize()
{
    typedef _STL::string Rva00C6D8B0String;
    ((Rva00C6D8B0String *)&TheBfmeObject_00C70CC0)->Rva00C6D8B0String::basic_string("*");
    atexit(bfmeForward_00C70CC0);
}

class Gen_00C70DD0Target;
extern Gen_00C70DD0Target TheBfmeObject_00C70DD0;
void bfmeForward_00C70DD0();
void rva00C6D9E0Initialize()
{
    typedef _STL::string Rva00C6D9E0String;
    ((Rva00C6D9E0String *)&TheBfmeObject_00C70DD0)->Rva00C6D9E0String::basic_string("true");
    atexit(bfmeForward_00C70DD0);
}

class Gen_00C70DE0Target;
extern Gen_00C70DE0Target TheBfmeObject_00C70DE0;
void bfmeForward_00C70DE0();
void rva00C6DA10Initialize()
{
    typedef _STL::string Rva00C6DA10String;
    ((Rva00C6DA10String *)&TheBfmeObject_00C70DE0)->Rva00C6DA10String::basic_string("false");
    atexit(bfmeForward_00C70DE0);
}

class Gen_00C70DF0Target;
extern Gen_00C70DF0Target TheBfmeObject_00C70DF0;
void bfmeForward_00C70DF0();
void rva00C6DA40Initialize()
{
    typedef _STL::string Rva00C6DA40String;
    ((Rva00C6DA40String *)&TheBfmeObject_00C70DF0)->Rva00C6DA40String::basic_string("");
    atexit(bfmeForward_00C70DF0);
}

class Gen_00C70E00Target;
extern Gen_00C70E00Target TheBfmeObject_00C70E00;
void bfmeForward_00C70E00();
void rva00C6DA70Initialize()
{
    typedef _STL::wstring Rva00C6DA70String;
    ((Rva00C6DA70String *)&TheBfmeObject_00C70E00)->Rva00C6DA70String::basic_string(L"true");
    atexit(bfmeForward_00C70E00);
}
