// ?Rva00462E80@@YAPAXPBD0@Z
// partial score=0.33 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME: anonymous carved body at 0x00462E80 (431 bytes). Only caller is
// an ILT thunk from the unlanded 0x00460F80 family (d_00460f80.asm), so the
// owning function/class is unproven; this is a plain __cdecl free function
// (ret with no operand; no "this" register is loaded).
//
// Retail parses a query-style parameter blob (arg2, the same string used by
// all three bfmeGetParamVMZ lookups) for "_RenderObj", "_KeepAspectRatio"
// and "_AnimMode" (literals read from the image at 0x0010F6FEC/FD8/FA8),
// builds a Gen_0078A430-shaped object (see Gen_0078A430.cpp) from the
// leaf-after-marker of arg1 (bfmePathLeafAfterMarker.cpp) and the parsed
// values, registers it under the dot-converted path
// (Rva0046F6F0SlashToDot, BfmeConv524.cpp) in the retail hashtable
// g_Rva00462DE0_table (Rva004613F0Map, RvaHashIndexAsciiString.cpp /
// RvaHashInsertAsciiString.cpp / RvaHashFindAsciiString.cpp), and returns
// the new object (or 0 if "_RenderObj" was missing/empty).
//
// bfmeGetParamVMZ's "out" parameter (BfmeStrVMZ) is checked afterward
// through the same StringBase-style 8-byte header (m_data ? m_data+8 : ...,
// word length at m_data+4) used everywhere else in this codebase, so it is
// modelled the same way here rather than as an opaque type.

#include "ascii_string.h"

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

namespace rts { template <class T> struct hash { unsigned int operator()(T value) const; }; }

enum Rva004613F0Mapped { Rva004613F0MappedZero = 0 };

typedef _STL::hash_map<AsciiString, Rva004613F0Mapped, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva004613F0Mapped> > > Rva004613F0Map;

extern Rva004613F0Map g_Rva00462DE0_table;

const char *__cdecl bfmePathLeafAfterMarker(const char *path);

class BfmeStrVMZ
{
public:
	BfmeStrVMZ() : m_data(0) {}
	void bfmeReleaseVMZ();
	void bfmeSetVMZ(const char *s, int n);

	const unsigned char *m_data;
};

char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out);

class BFMERetailAsciiString
{
public:
	const unsigned char *m_data;
};

BFMERetailAsciiString Rva0046F6F0SlashToDot(void *what);

struct Gen_0078A430
{
	unsigned int m_vptr;
	int m_a;
	int m_b;
	int m_c;
	int m_d;
	unsigned char m_flag;
	int m_e;
	int m_f;
	int m_g;
	int m_h;
	int m_i;
	int m_j;

	Gen_0078A430(unsigned char flag)
	{
		m_a = -1;
		m_b = 0;
		m_vptr = 0x01126ccc;
		m_c = 0;
		m_d = 0;
		m_flag = flag;
		m_e = 0;
		m_f = 0;
		m_g = 0;
		m_h = 0;
		m_i = 0;
		m_j = 0;
	}
};

Gen_0078A430 *createGen_0078A430(unsigned char flag);

int bfmeGoDYG(void *s);

class Gen_0078A430Caller
{
public:
	void slot1();
	void slot3(const BfmeStrVMZ *renderObj, const BfmeStrVMZ *animMode,
		const AsciiString *dotPath);
};

void *Rva00462E80(const char *path, const char *query)
{
	const char *leaf = bfmePathLeafAfterMarker(path);

	BfmeStrVMZ renderObj;
	if (!bfmeGetParamVMZ(query, "_RenderObj", &renderObj))
		return 0;
	if (!renderObj.m_data || !*(const unsigned short *)(renderObj.m_data + 4))
	{
		renderObj.bfmeReleaseVMZ();
		return 0;
	}

	BfmeStrVMZ keepAspect;
	bfmeGetParamVMZ(query, "_KeepAspectRatio", &keepAspect);

	const unsigned char *begin;
	const unsigned char *end;
	if (keepAspect.m_data)
	{
		begin = keepAspect.m_data + 8;
		end = begin + *(const unsigned short *)(keepAspect.m_data + 4);
	}
	else
	{
		extern const unsigned char Rva006A16B0Empty[];
		begin = Rva006A16B0Empty;
		end = begin;
	}

	bool defaultTrue = true;
	for (const unsigned char *p = begin; p != end; ++p)
	{
		if (*p == 'f')
		{
			defaultTrue = false;
			break;
		}
	}

	BfmeStrVMZ animMode;
	bfmeGetParamVMZ(query, "_AnimMode", &animMode);

	Gen_0078A430 *obj = createGen_0078A430((unsigned char)defaultTrue);
	Gen_0078A430Caller *caller = reinterpret_cast<Gen_0078A430Caller *>(obj);

	{
		typedef void (Gen_0078A430Caller::*Slot1Fn)();
		union { void *raw; Slot1Fn member; } thunk;
		thunk.raw = (*(void ***)obj)[1];
		(caller->*thunk.member)();
	}

	obj->m_e = bfmeGoDYG((void *)leaf);

	BFMERetailAsciiString dotPathRaw = Rva0046F6F0SlashToDot((void *)path);
	AsciiString &dotPath = *reinterpret_cast<AsciiString *>(&dotPathRaw);

	{
		typedef void (Gen_0078A430Caller::*Slot3Fn)(const BfmeStrVMZ *,
			const BfmeStrVMZ *, const AsciiString *);
		union { void *raw; Slot3Fn member; } thunk;
		thunk.raw = (*(void ***)obj)[3];
		(caller->*thunk.member)(&renderObj, &animMode, &dotPath);
	}

	keepAspect.bfmeReleaseVMZ();

	{
		AsciiString key(leaf);
		g_Rva00462DE0_table[key] = (Rva004613F0Mapped)0;
		*reinterpret_cast<void **>(&g_Rva00462DE0_table[key]) = obj;
	}

	animMode.bfmeReleaseVMZ();
	renderObj.bfmeReleaseVMZ();

	return obj;
}
