// ?Rva007752E0ParseProbability@@YAXPAVINI@@PAX1PBX@Z
// Retail 0x007752E0 / 308 bytes; scoped gate verifies all 19 relocations.
// cl: /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stlp_nodealloc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
#include <new>
#define _STLP_NO_EXCEPTIONS 1
#define _OPERATOR_NEW_DEFINED_
#include <stdlib.h>
#include <string.h>
#include "Common/AsciiString.h"
#include "Common/INIException.h"
template<> inline const char* StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
inline AsciiString::~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
inline AsciiString::AsciiString(const char* text, int length) {
    ((StringBase<char>*)this)->StringBase<char>::StringBase(text,length);
}
#include <vector>

struct Rva007752E0Element { AsciiString first; int second; };

// The callback needs only these retail method contracts; INI.h brings the
// unrelated ZH enum hash specializations into this narrow translation unit.
class INI
{
public:
	AsciiString getNextAsciiString();
	const char *getNextTokenOrNull(const char *separators = 0);
	const char *getNextToken(const char *separators = 0);
};

// Callback entry at retail RVA 0x007752E0. The INI object's +0x41c member supplies
// the separator string for the optional "prob" token. The owner+0x10 vector
// holds eight-byte owning AsciiString/int records; store is unused.
void __cdecl Rva007752E0ParseProbability(
	INI *ini, void *owner, void *store, const void *userData)
{
	(void)userData;
	if (!owner)
		return;

	Rva007752E0Element value;
	value.first = ini->getNextAsciiString();
	const char *separators = *(const char **)((char *)ini + 0x41c);
	const char *token = ini->getNextTokenOrNull(separators);
	if (token && _strcmpi(token, "prob") == 0)
	{
		separators = *(const char **)((char *)ini + 0x41c);
		value.second = atoi(ini->getNextToken(separators));
		if (value.second < 1 || value.second > 100)
			throw INIException(3,
				"*** ASSET ERROR: probability must be between 1 and 100 (not %i)",
				value.second);
	}
	else
	{
		value.second = -1;
	}

	((std::vector<Rva007752E0Element> *)((char *)owner + 0x10))->push_back(value);
}
