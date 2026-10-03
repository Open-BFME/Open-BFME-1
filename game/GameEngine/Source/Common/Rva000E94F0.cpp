// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
#include <bitset>

// Address-qualified storage view: retail complements six dwords, masks the
// last to21 bits, and returns this. The previous bitset<117> identity is false.
// Using the canonical bitset implementation here does not claim a retail type.
class Rva000E94F0
{
public:
    Rva000E94F0 &method();
private:
    _STL::bitset<181> m_rva000E94F0;
};

Rva000E94F0 &Rva000E94F0::method()
{
    m_rva000E94F0.flip();
    return *this;
}
