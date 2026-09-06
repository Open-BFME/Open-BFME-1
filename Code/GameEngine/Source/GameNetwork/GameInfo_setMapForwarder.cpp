// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Retail 0x0068DF70, 92 bytes: a GameInfo method that copies its by-value
// AsciiString and forwards it to GameInfo::setMap (retail 0x00620510, whose
// 1213-byte body is Zero Hour's map-mask and preview work, reached here
// through ILT 0x0001B5DB).
//
// The name describes the body; the retail identity is NOT recovered.  It is
// reached from five direct call sites -- LANAPI::RequestGameCreate at
// 0x006880BA, where Zero Hour calls myGame->setMap(mapName), plus four in the
// GUI region -- and it appears in no vtable, so it is not an override and
// nothing names it.

#include "StringInline.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	void setMap(AsciiString mapName);
	void setMapForwarder(AsciiString name);
};

// ?setMapForwarder@GameInfo@@QAEXVAsciiString@@@Z
void GameInfo::setMapForwarder(AsciiString name)
{
	setMap(name);
}
