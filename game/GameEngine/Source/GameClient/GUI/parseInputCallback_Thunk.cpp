// stlport
// cl: /I. /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/functionlexicon /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Lift the parseInputCallback window-file parser to clean C++.
//
// The third argument is a line from a window file. Scan to the opening quote,
// step past it, then extract the field with strtok and the quote
// delimiter. strtok is the retail import at IAT 0x013594D8 and terminates the token in the
// caller-owned line buffer.
//
// The result is stored into the global AsciiString at 0x012F2574 with an
// explicit length, guarded so a missing token stores nothing rather than
// measuring a null pointer. strtok mutates the caller-owned line buffer, matching
// the retail C runtime call. Its characters then go through NameKeyGenerator's
// name-to-key call on the generator at 0x012ED600 -- the same one
// Player::getProductionCostChangePercent uses, whose ILT thunk at 0x0003ADD7 is
// the pinned ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z -- and the key is
// looked up on the global at 0x012ED88C with a second argument of 1. The result
// lands in 0x012F255C and the function reports success unconditionally.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *s, const char *delim);
extern "C" unsigned int __cdecl strlen(const char *s);

#define Matrix4x4 Matrix4
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#define ASCIISTRING_H
#include "PreRTS.h"
#include "Common/FunctionLexicon.h"

class WindowLookupShim
{
public:
	/// address-derived name -- do not treat as an identity.
	void *unidentified_00025CD4(Int key, Int flag);		///< ILT thunk at 0x00025CD4
};

class WinInstanceData;

extern AsciiString theInputString;				///< retail [0x012F2574]
extern NameKeyGenerator *TheNameKeyGeneratorShim;	///< retail [0x012ED600]
class FunctionLexicon;
extern FunctionLexicon *TheFunctionLexicon;			///< retail [0x012ED88C]
extern void *TheParsedCallbackResult;					///< retail [0x012F255C]

// ?parseInputCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseInputCallback(char *token, WinInstanceData *instData, char *line, void *userData)
{
	char *p = line;
	while (*p != '"')
	{
		++p;
	}
	++p;

	char *fieldText = strtok(p, "\"");
	theInputString.StringBase<char>::set(fieldText, fieldText ? (Int)strlen(fieldText) : 0);

	Int key = TheNameKeyGeneratorShim->nameToKey(theInputString.str());
	TheParsedCallbackResult = ((WindowLookupShim *)TheFunctionLexicon)->unidentified_00025CD4(key, 1);

	return true;
}

class Gen_00C700B0Target;
extern Gen_00C700B0Target TheBfmeObject_00C700B0;
extern void *g_Va012F2554;
void j_00015a28();
class Rva00105480 {
public:
 void *call(NameKeyType key, int index);
};
// ?callRva00105480@@YAPAXPAVFunctionLexicon@@W4NameKeyType@@H@Z absent-from-retail
static __forceinline void *callRva00105480(FunctionLexicon *self, NameKeyType key, int index)
{
 union Entry {
  void (__cdecl *raw)();
  void *(Rva00105480::*member)(NameKeyType, int);
 } entry;
 entry.raw = j_00015a28;
 return (((Rva00105480 *)self)->*entry.member)(key, index);
}
// Open BFME 2: Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseWinClass.cpp.
Bool Rva004867A0(char *token, WinInstanceData *instData, char *buffer, void *data)
{
 char *ptr = buffer;
 while (*ptr != '"') ++ptr;
 ++ptr;
 char *value = strtok(ptr, "\"");
 AsciiString &name = *(AsciiString *)&TheBfmeObject_00C700B0;
 name.StringBase<char>::set(value, value ? (int)strlen(value) : 0);
 NameKeyType key = TheNameKeyGenerator->nameToKey(name.str());
 g_Va012F2554 = callRva00105480(TheFunctionLexicon, key, -1);
 return true;
}

extern void *g_Va012F2558;
// Open BFME 2: Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseSystemCallback.cpp.
Bool Rva00486850(char *token, WinInstanceData *instData, char *buffer, void *data)
{
 char *ptr = buffer;
 while (*ptr != '"') ++ptr;
 ++ptr;
 char *value = strtok(ptr, "\"");
 AsciiString &name = *(AsciiString *)&TheBfmeObject_00C700B0;
 name.StringBase<char>::set(value, value ? (int)strlen(value) : 0);
 NameKeyType key = TheNameKeyGenerator->nameToKey(name.str());
 g_Va012F2558 = (void *)TheFunctionLexicon->gameWinSystemFunc(key);
 return true;
}
