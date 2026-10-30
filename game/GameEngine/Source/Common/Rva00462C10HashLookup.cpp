// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Fuzzy-twin lane: near-twin of bfmeFindUpgradeByName (retail 0x000BB270,
// game/GameEngine/Source/Common/UpgradeCenter_findUpgradeByName.cpp) -- same
// "wrap a C-string in a temporary AsciiString key, look up, release the key,
// return the found payload or 0" shape, but this body:
//   - the "this" for the lookup is a fixed global hashtable object at
//     0x012F19A4 (defined by game/GameEngine/Source/Common/
//     Rva00C6B390StaticInitializers.cpp under the recorded name below), loaded as a plain
//     address, not a pointer that needs a null check
//   - the lookup calls the private hashtable _M_find implementation
//     directly through its own ILT thunk (0x0002E5A5 -> retail 0x00460C00,
//     already landed as the _M_find<AsciiString> instantiation for this same
//     table shape in game/Libraries/Source/WWVegas/WWLib/RvaHashFindAsciiString.cpp)
//     rather than through a public find()/end() wrapper, so this TU calls the
//     thunk directly via the member-pointer-thunk trick (same idiom as
//     game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6140_ResourceRelease.cpp)
//     instead of re-deriving the template's decorated name
//   - the found node pointer has 8 added before being returned, proving the
//     table's value struct carries a payload field right after the 4-byte
//     AsciiString key

#include "ascii_string.h"

extern void j_0002e5a5(void);

// address-derived stand-in for the hashtable instance living at 0x012F19A4.
// The previous reference spelled ?g_rva012F19A4@@3URva00C6B860Init@@A,
// following Rva00C6B390StaticInitializers.cpp's local view. Only the address
// is used here; bind the recorded storage symbol below while preserving this
// opaque call view. This does not establish a new class or initializer identity.
struct Rva00C6B860Init
{
	void *findRaw(const AsciiString &key)
	{
		typedef void *(Rva00C6B860Init::*MemberThunk)(const AsciiString &);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_0002e5a5;
		return (this->*thunk.member)(key);
	}
};

// Bind the existing recorded storage symbol without changing this opaque view.
extern "C" Rva00C6B860Init __identifier("?TheBfmeObject_00C700A0@@3VGen_00C700A0Target@@A");

// ?Rva00462C10@@YAPAXPBD@Z -- address-derived TAG, identity unresolved
void *Rva00462C10(const char *name)
{
	void *node;
	{
		AsciiString key(name);
		node = __identifier("?TheBfmeObject_00C700A0@@3VGen_00C700A0Target@@A").findRaw(key);
	}
	return node ? reinterpret_cast<char *>(node) + 8 : 0;
}
