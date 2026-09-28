// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 009D9C70..009D9D80, between INT3 padding runs. The three calls
// to bfmeAppend use newline, null and "<%s>\n". The following calls are
// STLport string construction/copy and vector<string> overflow, with 12-byte
// elements. The class identity is intentionally address-derived.
#include <string>
#include <vector>

class BfmeAppendStream;
extern "C" void __cdecl bfmeAppend(BfmeAppendStream *, const char *, ...);

class Rva009D9C70 {
    void *field00;
    bool pending;
    void *sink;
    _STL::vector<_STL::string> entries;
public:
    int append(const char *text);
};

int Rva009D9C70::append(const char *text)
{
    if (pending) {
        bfmeAppend((BfmeAppendStream *)this, "\n");
        pending = false;
    }
    bfmeAppend((BfmeAppendStream *)this, 0);
    if (text == 0) text = "";
    bfmeAppend((BfmeAppendStream *)this, "<%s>\n", text);
    _STL::string value(text);
    entries.push_back(value);
    return 0;
}
