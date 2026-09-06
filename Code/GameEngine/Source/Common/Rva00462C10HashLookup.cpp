// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Fuzzy-twin lane: near-twin of bfmeFindUpgradeByName (retail 0x000BB270,
// Code/GameEngine/Source/Common/UpgradeCenter_findUpgradeByName.cpp) -- same
// "wrap a C-string in a temporary AsciiString key, look up, release the key,
// return the found payload or 0" shape, but this body:
//   - the "this" for the lookup is a fixed global hashtable object at
//     0x012F19A4 (already pinned as ?g_bfmeTwoSJA@@3PADA, a char*-typed
//     placeholder from an earlier session), loaded as a plain address, not a
//     pointer that needs a null check
//   - the lookup calls the private hashtable _M_find implementation
//     directly through its own ILT thunk (0x0002E5A5 -> retail 0x00460C00,
//     already landed as the _M_find<AsciiString> instantiation for this same
//     table shape in Code/Libraries/Source/WWVegas/WWLib/RvaHashFindAsciiString.cpp)
//     rather than through a public find()/end() wrapper, so this TU calls the
//     thunk directly via the member-pointer-thunk trick (same idiom as
//     Code/GameEngineDevice/Source/W3DDevice/GameClient/Gen_006C6140_ResourceRelease.cpp)
//     instead of re-deriving the template's decorated name
//   - the found node pointer has 8 added before being returned, proving the
//     table's value struct carries a payload field right after the 4-byte
//     AsciiString key

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

extern void j_0002e5a5(void);

// address-derived stand-in for the hashtable instance living at 0x012F19A4
class Rva00462C10Table
{
public:
	void *findRaw(const AsciiString &key)
	{
		typedef void *(Rva00462C10Table::*MemberThunk)(const AsciiString &);
		union {
			void (*function)(void);
			MemberThunk member;
		} thunk;
		thunk.function = j_0002e5a5;
		return (this->*thunk.member)(key);
	}
};

extern Rva00462C10Table g_bfmeTwoSJA_table;

// ?Rva00462C10@@YAPAXPBD@Z -- address-derived TAG, identity unresolved
void *Rva00462C10(const char *name)
{
	void *node;
	{
		AsciiString key(name);
		node = g_bfmeTwoSJA_table.findRaw(key);
	}
	return node ? reinterpret_cast<char *>(node) + 8 : 0;
}
