// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// GameClient::addTOCEntry, RVA00431C60,168B. Matched xferDrawableTOC00431DC0
// calls via ILT266F2 with this, by-value AsciiString and ushort; retail ret8.
// Zero Hour GameClient.cpp supplies the same list push_back body/signature.
// Retail list lives at+F0. Disabling STLport exceptions inlines node creation
// into allocation(16) plus the existing _Construct specialization. Its opaque
// Rva00430E90Element name is retained from the independently matched caller
// family and pinned copy helper at ILT404E4 ->00430840.
#define _STLP_NO_EXCEPTIONS 1` before <list> is what makes
// this shape reproducible: with STLport exceptions on, list<T>::_M_create_node
// keeps its try/catch and stays an out-of-line call (the _M_create_node at
// 0x00431C60's caller sites), while retail inlines it into allocate(16) +
// _Construct. Same mechanism as
// game/GameEngine/Source/Common/RTS/Gen_guarded_list_push_back.cpp.
//
// The element type is deliberately address-derived. Its only proven identity
// is the _Construct instantiation the list insert calls, and retail's symbols
// name it ?$_Construct@URva00430E90Element@@U1@@_STL@@YAXPAU
// Rva00430E90Element@@ABU1@@Z (pinned to 0x000404E4, a jmp to 0x00430840) --
// spelling the struct anything else would emit a different callee name and
// lose the call target.

#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include "ascii_string.h"

typedef unsigned short UnsignedShort;

// 8-byte payload of the 16-byte list node: the name copied through
// StringBase<char>::set, and the id.
struct Rva00430E90Element
{
	AsciiString m_name;
	UnsignedShort m_id;
};

class GameClient
{
private:
	void **m_vtable;							// +0x00
	char m_pad04[0xEC];
	std::list<Rva00430E90Element> m_drawableTOC;	// +0xF0

	void addTOCEntry(AsciiString name, UnsignedShort id);
};

void GameClient::addTOCEntry(AsciiString name, UnsignedShort id)
{
	Rva00430E90Element entry;
	entry.m_name = name;
	entry.m_id = id;
	m_drawableTOC.push_back(entry);
}
