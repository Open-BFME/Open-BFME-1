// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME7: retail 0x00462DE0 (120 bytes) is the one-byte twin of the hash lookup at
// 0x00462C10 (Rva00462C10HashLookup.cpp): the same search over its own table, but it
// returns the pointer STORED at node+8 (mov eax,[esi+8]) rather than the address of
// that field (lea).  Names re-tagged for this address; table and callee autopinned.
// Fuzzy-twin lane: near-twin of bfmeFindUpgradeByName (retail 0x000BB270,
// game/GameEngine/Source/Common/UpgradeCenter_findUpgradeByName.cpp) -- same
// "wrap a C-string in a temporary AsciiString key, look up, release the key,
// return the found payload or 0" shape, but this body:
//   - the "this" for the lookup is a fixed global hashtable object at
//     0x012F19B8 (defined by game/GameEngine/Source/Common/
//     Rva00C6B390StaticInitializers.cpp as g_rva012F19B8), loaded as a plain
//     address, not a pointer that needs a null check
//   - the lookup calls the private hashtable _M_find implementation directly
//     through its own ILT thunk at 0x00442F78 (?j_00042f78@@YAXXZ, retail
//     0x00860CD0), NOT the 0x0002E5A5 thunk its one-byte twin at 0x00462C10
//     uses. tools/dis_retail.py 0x00462DE0 120 reads `call 0x442f78` at +0x37.
//     The two thunks are the same _M_find<AsciiString> template instantiated
//     over two different value types, one per table, so the byte comparison
//     masked the difference: the REL32 is compared after masking. This TU now
//     spells the thunk retail actually calls. The linked bytes are unchanged.
//     rather than through a public find()/end() wrapper, so this TU calls the
//     thunk directly via the member-pointer-thunk trick (same idiom as
//     game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6140_ResourceRelease.cpp)
//     instead of re-deriving the template's decorated name
//   - the found node pointer has 8 added before being returned, proving the
//     table's value struct carries a payload field right after the 4-byte
//     AsciiString key

#include "ascii_string.h"

extern void j_00042f78(void);

// address-derived stand-in for the hashtable instance living at 0x012F19B8.
// The global itself is defined once, by the TU that owns its dynamic
// initializer: Rva00C6B390StaticInitializers.cpp declares
// `Rva00C6B880Init g_rva012F19B8;` (retail 0x00C6B880, the $E stub for this
// address).  Only the address is used here, so this TU repeats the type name to
// spell that exact symbol -- same idiom as Gen_00C700A0Target in
// S3SingletonForwarders.cpp.  It must be a `struct`, not a `class`: MSVC
// decorates a class type `V...` and a struct type `U...`, and the defining
// object spells ?g_rva012F19B8@@3URva00C6B880Init@@A.
struct Rva00C6B880Init
{
	void *findRaw(const AsciiString &key)
	{
		typedef void *(Rva00C6B880Init::*MemberThunk)(const AsciiString &);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_00042f78;
		return (this->*thunk.member)(key);
	}
};

extern Rva00C6B880Init g_rva012F19B8;

// ?Rva00462DE0@@YAPAXPBD@Z -- address-derived TAG, identity unresolved
void *Rva00462DE0(const char *name)
{
	void *node;
	{
		AsciiString key(name);
		node = g_rva012F19B8.findRaw(key);
	}
	return node ? *reinterpret_cast<void **>(reinterpret_cast<char *>(node) + 8) : 0;
}
