// cl: /DNDEBUG /MD /EHsc
// stlport
// _STLP_USE_STATIC_LIB as in vector_uchar_insert_overflow.cpp: without it the
// vector<unsigned char>::_M_insert_overflow COMDAT emitted here is not
// retail's 263-byte 0x0074D6F0 body.
#define _STLP_USE_STATIC_LIB 1
#include <vector>

// Address-derived view: retail passes the fill byte by value, unlike the
// previously claimed const-reference overload. See identity_evidence/
// 0074e620-value-argument.md for caller and complete-boundary evidence.
class Rva0074E620 : public std::vector<unsigned char> {
public:
    void method(unsigned int count, unsigned char value);
};
void Rva0074E620::method(unsigned int count, unsigned char value)
{
    if (count < size())
        erase(begin() + count, end());
    else
        insert(end(), count - size(), value);
}
