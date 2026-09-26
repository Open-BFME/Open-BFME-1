// ?Rva003C5270Find@@YGHPAVRva003C5820Owner@@PAVRva003C5820Key@@@Z
// partial score=0.29 date=2026-09-22
// Called as a raw __stdcall function pointer (not virtual/thiscall -- both
// args are plain stack args, ret 8) from Rva003C5820Owner::appendMatch
// (Code/GameEngine/Source/Common/Rva003C5820AppendMatch.cpp), which already
// declares the exact FindFunction signature this body must match:
// `int __stdcall (Rva003C5820Owner*, Rva003C5820Key*)`. That caller already
// existed before this session; this is the first compilable candidate for
// the callee itself.
//
// Full disassembly read start to finish (not just the boundary): linear
// scan over owner's vector<Item*> (modelled directly as the STLport
// _M_start/_M_finish pointer pair, no <vector> needed -- read-only). Each
// Item (owner->m_begin[i]) and the Key are BOTH a pointer to a
// length-prefixed blob: word length at blob+4, data at blob+8; a null blob
// pointer falls back to the shared empty-string constant Rva006A16B0Empty
// (VA 0x0107388B, named by an existing relocation in this body). The
// compare is `memcmp(key,item,min(keyLen,itemLen))==0 && keyLen==itemLen`
// (exact match only, not prefix) -- confirmed from the tail `sub
// ebx,ebp;test;je` after the `repe cmpsb`. Returns the index of the first
// exact match, or -1. `extern "C" int memcmp(...); #pragma intrinsic(memcmp)`
// is what gets MSVC to emit `repe cmpsb` for the byte compare instead of a
// manual loop (a hand-written char-by-char loop compiled to ~30 extra bytes
// and never produced the rep-string opcode).
//
// RESULT: ours=152B retail=181B, 128/181 nonreloc diff, first divergence at
// +2 (i.e. only the initial `push ecx` prologue byte matches). The residue
// is REGISTER CHOICE, not missing logic: retail loads `owner` into EDX and
// keeps `count` in EAX across the whole function; every source order tried
// here put `owner` in EAX instead (edx never appears). Tried (all compiled,
// none changed the register choice or beat this diff count): a manual
// byte-compare loop instead of memcmp (209B, worse), computing the item's
// blob fields into named locals inline instead of through the getRange()
// helper (162B, worse), marking getRange() __forceinline explicitly (no
// change, already inlined), and declaring `p = owner->m_begin` before vs.
// after the key-range lookup (156B, worse either way tried). NEXT LEVER:
// something that makes MSVC 7.1 prefer EDX over EAX for the first
// dereferenced pointer parameter of a 2-argument __stdcall free function --
// not yet found; shape_family_levers.py --families register,sib,loop,branch
// found no applicable automatic lever (no adjacent atom-initialized decl
// pair to swap). t=25min model=claude-sonnet-5 score=0.29
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

extern char Rva006A16B0Empty[];

struct Rva003C5270Blob
{
	void *m_00;
	unsigned short m_len;
	unsigned short m_pad;
	char m_data[ 1 ];
};

class Rva003C5820Item
{
public:
	Rva003C5270Blob *m_blob;
};

class Rva003C5820Key
{
public:
	Rva003C5270Blob *m_blob;
};

class Rva003C5820Owner
{
public:
	Rva003C5820Item **m_begin;
	Rva003C5820Item **m_end;
};

extern "C" int memcmp( const void *, const void *, unsigned int );
#pragma intrinsic( memcmp )

static __forceinline void getRange( Rva003C5270Blob *blob, unsigned short &len, const char *&data )
{
	if( blob )
	{
		len = blob->m_len;
		data = blob->m_data;
	}
	else
	{
		len = 0;
		data = Rva006A16B0Empty;
	}
}

int __stdcall Rva003C5270Find( Rva003C5820Owner *owner, Rva003C5820Key *key )
{
	int count = (int)( owner->m_end - owner->m_begin );
	if( count > 0 )
	{
		unsigned short keyLen;
		const char *keyData;
		getRange( key->m_blob, keyLen, keyData );

		Rva003C5820Item **p = owner->m_begin;
		for( int i = 0; i < count; ++i, ++p )
		{
			unsigned short itemLen;
			const char *itemData;
			getRange( (*p)->m_blob, itemLen, itemData );

			unsigned short n = ( keyLen < itemLen ) ? keyLen : itemLen;
			if( memcmp( keyData, itemData, n ) == 0 && keyLen == itemLen )
				return i;
		}
	}
	return -1;
}
