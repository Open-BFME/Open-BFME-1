// cl: /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail RVA 0x000B1DF0, 558 bytes: body reached by INI::parseSoundsList's
// matched ILT at 0x0002E9C4. Keep the existing forwarding-shim symbol.
// BFME parses file[:weight] tokens (default weight 1000), appends an owning
// string/integer entry, and optionally accumulates the weight at an instance
// offset supplied through userData. Both validation messages are retail literals.
//
// Boundary: INT3 before 0x000B1DF0; normal ret at 0x000B1FA9; the two cold
// exception blocks end with __CxxThrowException at 0x000B2019. Padding starts
// at 0x000B201E. The compiler's extra terminal INT3 is not part of the claim.
//
// _Construct's two stack arguments and the StringBase copy plus dword copy
// are independently decoded at 0x000B0360 (via ILT 0x00039F86). The existing
// Rva000B19F0Element vector insert owns the 8-byte element ABI and resolves
// through ILT 0x0001F73F. These declarations reuse those exact callee contracts.
// An ordinary inline getter for the userData offset preserves retail's initial
// address calculation and the resulting register schedule throughout the body.

#include <new>
#define _OPERATOR_NEW_DEFINED_
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Common/AsciiString.h"
#include "Common/INI.h"
#include "Common/INIException.h"
#pragma intrinsic(strlen)
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline AsciiString::AsciiString(const char* str, int len) {
    ((StringBase<char>*)this)->StringBase<char>::StringBase(str,len);
}
#include <vector>
namespace _STL {
struct Rva000B19F0Element {
    AsciiString name;
    int weight;
    Rva000B19F0Element(const AsciiString& text,int value) : name(text), weight(value) {}
};
}
// Retail reaches the placement copy (0x000B0360) and the overflow insert
// (0x000B19F0) through their incremental-link thunks; the ledger names the
// first row after a generated pair placeholder, so route through the thunks.
extern void j_00039f86();
extern void j_0001f73f();
struct Rva000B19F0Vec : _STL::vector<_STL::Rva000B19F0Element,_STL::allocator<_STL::Rva000B19F0Element> > {
    __forceinline void append(const _STL::Rva000B19F0Element& r,const AsciiString& tagSlot) {
        if(_M_finish!=_M_end_of_storage._M_data) { typedef void (__cdecl *F)(_STL::Rva000B19F0Element*,const _STL::Rva000B19F0Element&); ((F)j_00039f86)(_M_finish,r); ++_M_finish; }
        else { typedef void (Rva000B19F0Vec::*M)(_STL::Rva000B19F0Element*,const _STL::Rva000B19F0Element&,const _STL::__false_type&,unsigned int,bool); union { void (*raw)(); M m; } u; u.raw = j_0001f73f; (this->*u.m)(_M_finish,r,(const _STL::__false_type&)tagSlot,1,true); }
    }
};
struct Rva000B1DF0Offset {
    int value;
    int get() const { return value; }
};
class INIParseSoundsListShim {
public: static void parse(INI* ini,void* instance,void* store,const void* userData);
};
void INIParseSoundsListShim::parse(INI* ini,void* instance,void* store,const void* userData) {
    int* totalWeight = userData ? (int*)((char*)instance + ((const Rva000B1DF0Offset*)userData)->get()) : 0;
    Rva000B19F0Vec* sounds = (Rva000B19F0Vec*)store;
    const char* token = ini->getNextTokenOrNull();
    while(token) {
        int tokenLength = strlen(token);
        if(tokenLength) {
            const char* end = token + tokenLength - 1;
            while(end > token && isdigit(*end)) --end;
            AsciiString name;
            int weight;
            if(*end == ':') {
                weight = atoi(++end);
                if(weight < 1) throw INIException(3,"Weight of sound files must be >= 1. Sound '%s' for audio event '%s'", token, ((AsciiString*)((char*)instance + 8))->str());
                name = AsciiString(token, end - token - 1);
            } else {
                weight = 1000;
                name = AsciiString(token,tokenLength);
            }
            if(name.isEmpty()) throw INIException(3,"Sound file has no file name. Sound '%s' for audio event '%s'",token,((AsciiString*)((char*)instance + 8))->str());
            sounds->append(_STL::Rva000B19F0Element(name,weight),name);
            if(totalWeight) *totalWeight += weight;
        }
        token = ini->getNextTokenOrNull();
    }
}
