// cl: /DNDEBUG /MD /O2 /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	AsciiString getNextQuotedAsciiString();
};

class BfmeObjD540
{
public:
	void bfmeGoD540(AsciiString s);
};

void bfmeParseD780(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	AsciiString s = ini->getNextQuotedAsciiString();
	((BfmeObjD540 *)instance)->bfmeGoD540(s);
}
