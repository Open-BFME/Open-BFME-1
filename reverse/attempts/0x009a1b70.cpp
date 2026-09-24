// ?d_009a1b70@@YAXXZ
// partial score=0.28 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// GameEngine::init loads TheSubsystemList (retail 0x0134C6C8) into ECX before
// calling 0x009A1B70. The body walks its pair-vector and formats one CSV name
// per subsystem; its method identity remains address-derived.
#include "Lib/BaseType.h"
#include "subsystem_interface.h"

class Rva009A1B70Dispatch
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    // The base vtable slot at +0x18 routes to 0x00067940: xor al,al; ret 4.
    virtual int slot18(const char *fileName) = 0;
};

class Rva009A1B70
{
public:
    void call();
};

// Match the existing inline AsciiString destructor body from ascii_string.cpp;
// the retail loop calls StringBase<char>::releaseBuffer directly at each cleanup.
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

// ?call@Rva009A1B70@@QAEXXZ
void Rva009A1B70::call()
{
    SubsystemInterfaceList *list = (SubsystemInterfaceList *)this;
    int index = 0;
    std::vector<std::pair<SubsystemInterface *, void *> >::iterator it =
        list->m_subsystems.begin();
    for (; it != list->m_subsystems.end(); ++it)
    {
        AsciiString name;
        name = it->first->getName();
        AsciiString fileName;
        fileName.format(AsciiString("%s_%02d.csv"), name.str(), index);
        ((Rva009A1B70Dispatch *)it->first)->slot18(fileName.str());
        ++index;
    }
}
