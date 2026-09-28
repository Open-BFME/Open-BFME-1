// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/buildlistinfo /Iinputs/reference/shims/moduledata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x001985E0: 24-byte SidesInfo copy temporary; opaque owner preserves
// the address because the available SidesInfo header lacks BFME's +0x0c vector.
#include "PreRTS.h"
#include "Common/Dict.h"
#include <vector>

namespace _STL {
template<> vector<AsciiString>::vector(const vector<AsciiString>&);
}

class Gen_00193D50 {
public:
    Gen_00193D50(const Gen_00193D50&);
    virtual ~Gen_00193D50();
    char m_04[0x28];
    Gen_00193D50 *m_2c;
    char m_30[0x5c];
};
class Gen0035E3B0;
class Host0035E450 { public: Gen0035E3B0 *create(); };

class Rva001985E0 {
public:
    Rva001985E0(const Rva001985E0&);
private:
    Gen_00193D50 *m_00;
    Dict m_04;
    Host0035E450 *m_08;
    _STL::vector<AsciiString> m_0c;
};
Rva001985E0::Rva001985E0(const Rva001985E0& other)
    : m_00(0), m_04(other.m_04), m_08(0), m_0c(other.m_0c)
{
    Gen_00193D50 *last = 0;
    try {
        for (Gen_00193D50 *node=other.m_00; node; node=node->m_2c) {
            Gen_00193D50 *copy = new Gen_00193D50(*node);
            copy->m_2c = 0;
            if (last) last->m_2c = copy;
            else m_00 = copy;
            last = copy;
        }
        if (other.m_08) m_08 = reinterpret_cast<Host0035E450 *>(other.m_08->create());
    } catch (...) {
        delete m_00;
        throw;
    }
}
