// ?d_009a1b70@@YAXXZ
// Retail 0x009A1B70: 246 bytes; resumed the banked implementation.
// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// GameEngine::init loads TheSubsystemList (retail 0x0134C6C8) into ECX before
// calling 0x009A1B70. The body walks its pair-vector and formats one CSV name
// per subsystem; its method identity remains address-derived.
#include "Lib/BaseType.h"
#include "subsystem_interface.h"
// Retail inlines the two buffer-or-empty accesses (see ascii_string.cpp).
template <>
inline const char *StringBase<char>::str() const
{
    return m_data ? m_data->data : "";
}

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


// ?call@Rva009A1B70@@QAEXXZ
void Rva009A1B70::call()
{
    SubsystemInterfaceList *list = (SubsystemInterfaceList *)this;
    int index = 0;
    std::vector<std::pair<SubsystemInterface *, void *> >::iterator it =
        list->m_subsystems.begin();
    for (; it != list->m_subsystems.end(); ++it)
    {
        AsciiString fileName;
        AsciiString name;
        name = it->first->getName();
        fileName.format(AsciiString("%s_%02d.csv"), name.str(), index++);
        ((Rva009A1B70Dispatch *)it->first)->slot18(fileName.str());

    }
}
