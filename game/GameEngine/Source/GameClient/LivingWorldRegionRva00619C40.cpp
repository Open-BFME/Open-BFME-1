// ?rva00619C40@@YGXPAURva00619C40Entry@@HABVAsciiString@@@Z
// The 361-byte body ends at ret 0x0C at 0x00619DA6. The vtable 0x01117258 and caller's 0x24-byte record walk identify LivingWorldRegion data. I keep the helper's name address-derived because the evidence does not identify a C++ method.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/gameinfo /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <new>
#define _OPERATOR_NEW_DEFINED_
class INI;
#include "GameNetwork/GameInfo.h"
#include "Common/NameKeyGenerator.h"
#include "string_base.h"
inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<WideChar>*)this)->StringBase<WideChar>::StringBase(*(const StringBase<WideChar>*)&s); }
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->StringBase<char>::~StringBase(); }
struct Rva00619C40Entry {
    char unknown00[8]; int value08; char unknown0c[12]; char flag18; char unknown19[7]; int value20;
    AsciiString rva006196C0();
};
class Rva000E15A0 { public: bool method(NameKeyType,unsigned int *); };
class PlayerTemplateStore;
extern PlayerTemplateStore *ThePlayerTemplateStore;
extern GameInfo *Rva012F7090;
void __stdcall rva00619C40(Rva00619C40Entry *entry,int index,const AsciiString &name) {
    GameSlot slot;
    slot.reset();
    char flag=*((char*)entry+0x18);
    GameSlotConnectInfo ci;
    ci.m_port=0;
    ci.m_nat=(FirewallHelperClass::FirewallBehaviorType)0;
    if(flag==1) {
        slot.setState((SlotState)5,UnicodeString::TheEmptyString,&ci);
        ((StringBase<char>*)((char*)&slot+0x2c))->set(*(const StringBase<char>*)&AsciiString("PlayerHuman"));
    } else {
        slot.setState((SlotState)3,UnicodeString::TheEmptyString,&ci);
        ((StringBase<char>*)((char*)&slot+0x2c))->set(*(const StringBase<char>*)&entry->rva006196C0());
    }
    unsigned int value=0;
    if(((Rva000E15A0*)ThePlayerTemplateStore)->method(TheNameKeyGenerator->nameToKey(((const StringBase<char>*)&name)->str()),&value)) {
        *(int*)((char*)&slot+0x14)=value;
        *(int*)((char*)&slot+0x10)=entry->value08;
        *(int*)((char*)&slot+0xc)=index;
        *(int*)((char*)&slot+0x18)=entry->value20;
        Rva012F7090->setSlot(index,slot);
    }
}
