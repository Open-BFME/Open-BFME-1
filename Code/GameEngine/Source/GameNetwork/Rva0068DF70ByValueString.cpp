// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// GameInfo method that copies a by-value AsciiString and forwards it to
// GameInfo::setMap (retail 0x00620510 via ILT 0x0001B5DB).

#include "StringInline.h"

class GameInfo
{
public:
	void setMap(AsciiString mapName);
	void rva68df70(AsciiString name);
};

// ?rva68df70@GameInfo@@QAEXVAsciiString@@@Z
void GameInfo::rva68df70(AsciiString name)
{
	setMap(name);
}
