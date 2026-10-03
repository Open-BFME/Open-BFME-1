// cl: /DNDEBUG /MD /EHsc
// This constructor also emits the public scalar-deleting wrapper at
// 0x001F6D10 (30 bytes): vtable 0x010A2C88 slot zero routes through
// ILT 0x00019F0B, and its complete-destructor call uses ILT 0x00016A13.
// Keeping it here avoids a separate forcing TU emitting an incorrect
// vptr-only default constructor for the same class.
//
// Open-BFME5: ModuleFactory's data-create proc 0x001146F0 allocates 0x24 and
// runs this body, which identifies BuildingBehaviorModuleData.
//
// The four strings at +0x08 are an ARRAY member, which is why retail reaches
// them through the compiler's eh vector constructor iterator with the string's
// constructor ILT 0x00017BD9 and destructor ILT 0x0000D828 as arguments; the
// three dwords above them are the initialiser list, and the counted loop that
// follows is set("", 0) over the array.

// The four string elements are the real AsciiString, and both headers are
// included so every name the body reaches is the one retail links against:
//
//   * the counted loop's set("", 0) reaches StringBase<char>::set at
//     0x00887D20, whose object symbol (game/Libraries/Source/string/
//     StringBase.cpp) is ?set@?$StringBase@D@@QAEXPBDH@Z;
//   * the eh vector constructor/destructor iterators take the ELEMENT ctor
//     and dtor as arguments, and retail passes the incremental-link thunks
//     ILT 0x00417BD9 and 0x0040D828.  Those two thunks are the ones
//     functions.csv carries as ??0AsciiString@@QAE@XZ (ILT 0x00017BD9, body
//     0x00062030, game/GameEngine/Source/Common/System/AsciiString.cpp) and
//     ??1AsciiString@@QAE@XZ (ILT 0x0000D828, body 0x0005EE90,
//     game/Libraries/Source/WWVegas/WWLib/AsciiStringNative.cpp), so the
//     element type must be spelled AsciiString.  A TU-local stand-in only
//     mangles to itself (??0RetailLayoutString@@QAE@XZ), which nothing in the
//     tree defines.
//
// Both stay byte-identical: ascii_string.h's inline AsciiString() and
// ~AsciiString() are emitted here as COMDAT copies that reproduce retail's
// 9-byte 0x00062030 body and its 5-byte `jmp releaseBuffer` 0x0005EE90
// exactly, which is the same COMDAT set every TU including these two headers
// already carries.
#include "../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// The dword at +0x04 is a destructible BASE, not a member: retail stores EH
// state 0 BEFORE the vftable store, and only a base subobject is constructed
// that early. Spelled as a member it still produces state 0, but MSVC then
// hoists the vftable store to the top of the body instead of scheduling it
// into the array constructor's argument window.
class BBMD_Owned
{
public:
	~BBMD_Owned(void) { m_p = 0; }

private:
	void *m_p;
};

class BBMD_Handle
{
public:
	BBMD_Handle(int) { m_p = 0; }
	~BBMD_Handle(void) { m_p = 0; }

private:
	void *m_p;
};

class BuildingBehaviorModuleData : public BBMD_Owned
{
public:
	BuildingBehaviorModuleData();
	virtual ~BuildingBehaviorModuleData();

private:
	AsciiString m_names[4];		// this+0x08 .. 0x14
	unsigned int m_x18;
	unsigned int m_x1c;
	BBMD_Handle m_x20;
};

// ??0BuildingBehaviorModuleData@@QAE@XZ
BuildingBehaviorModuleData::BuildingBehaviorModuleData()
	: m_x18(0), m_x1c(0), m_x20(0)
{
	for (int i = 0; i < 4; i++)
		reinterpret_cast<StringBase<char> *>(&m_names[i])->set("", 0);
}
