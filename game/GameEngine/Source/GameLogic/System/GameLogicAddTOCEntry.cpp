// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// GameLogic::addTOCEntry, RVA 0x00390320, 168 bytes, retail ret 8.
// ilt_oracle CONFIRMED (exact) for this name at this address; EA source-file
// evidence places the body in GameLogic.cpp. Same shape as the matched
// GameClient::addTOCEntry (0x00431C60): a list push_back of an AsciiString
// plus ushort, here with the list at this+0x1AC.
// The element copy calls ILT 0x000057E5 -> 0x003884B0, whose _Construct
// instantiation is already pinned under the address-derived element name
// Rva0038EAD0Element; the element type is reused under that name.
// _STLP_NO_EXCEPTIONS inlines node creation as in the GameClient sibling.

#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include "ascii_string.h"

#include "../../../Include/Common/ScalarTypes.h"

struct Rva0038EAD0Element
{
	AsciiString m_name;
	UnsignedShort m_id;
};

class GameLogic
{
private:
	void **m_vtable;							// +0x00
	char m_pad04[0x1A8];
	std::list<Rva0038EAD0Element> m_objectTOC;	// +0x1AC

	void addTOCEntry(AsciiString name, UnsignedShort id);
};

void GameLogic::addTOCEntry(AsciiString name, UnsignedShort id)
{
	Rva0038EAD0Element entry;
	entry.m_name = name;
	entry.m_id = id;
	m_objectTOC.push_back(entry);
}
