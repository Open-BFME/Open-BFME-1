// cl: /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
// AsciiString::isEmpty, expanded in place.  Calling the member would emit
// ?isEmpty@AsciiString@@QBE_NXZ and ?isEmpty@?$StringBase@D@@QBE_NXZ COMDATs
// that are not retail's bodies.  The buffer pointer is the string's first
// word; its length is at +4.
static __forceinline bool asciiIsEmpty( const AsciiString &string )
{
	const char *data = *reinterpret_cast<const char * const *>(&string);
	return !data || *reinterpret_cast<const unsigned short *>(data + 4) == 0;
}
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline AsciiString::AsciiString(const char* str, int len) {
    ((StringBase<char>*)this)->StringBase<char>::StringBase(str,len);
}
// Select the existing address-derived _Construct contract.
namespace _STL {
    template<class T> void __cdecl _Construct(T* destination, const T& value);
}
#include <vector>
namespace _STL {
struct Rva000B19F0Element {
    AsciiString name;
    int weight;
    Rva000B19F0Element(const AsciiString& text,int value) : name(text), weight(value) {}
};
}
struct Rva000B1DF0Offset {
    int value;
    int get() const { return value; }
};
class INIParseSoundsListShim {
public: static void parse(INI* ini,void* instance,void* store,const void* userData);
};
void INIParseSoundsListShim::parse(INI* ini,void* instance,void* store,const void* userData) {
    int* totalWeight = userData ? (int*)((char*)instance + ((const Rva000B1DF0Offset*)userData)->get()) : 0;
    _STL::vector<_STL::Rva000B19F0Element>* sounds = (_STL::vector<_STL::Rva000B19F0Element>*)store;
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
            if(asciiIsEmpty(name)) throw INIException(3,"Sound file has no file name. Sound '%s' for audio event '%s'",token,((AsciiString*)((char*)instance + 8))->str());
            sounds->push_back(_STL::Rva000B19F0Element(name,weight));
            if(totalWeight) *totalWeight += weight;
        }
        token = ini->getNextTokenOrNull();
    }
}
