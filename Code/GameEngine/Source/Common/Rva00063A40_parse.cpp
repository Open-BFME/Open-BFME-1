// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
// stlport
// Int(char *args[], int num) command-line handler, the same family as
// Code/GameEngine/Source/Common/T3CommandLineParsers.cpp: TheWritableGlobalData
// [0x012ED5C8] and the saved-default flag byte [0x012ED4D8] are the identical
// globals that file's Rva00060980_parse pair reads and writes. Not present in
// the live -flag table (Code/GameEngine/Source/Common/CommandLine.cpp
// params[]), so no source name survives; identity is address-derived.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "StringInline.h"

typedef int Int;

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x11E0];
	std::vector<AsciiString> m_list11E0;
};

extern GlobalData *TheWritableGlobalData;	///< retail [0x012ED5C8]
extern bool g_flag12ED4D8;					///< retail [0x012ED4D8]

// ?Rva00063A40_parse@@YAHQAPADH@Z
Int Rva00063A40_parse(char *args[], int num)
{
	if (TheWritableGlobalData && num > 1)
	{
		TheWritableGlobalData->m_list11E0.push_back(AsciiString(args[1]));
		return 2;
	}
	g_flag12ED4D8 = true;
	return 2;
}
