// ?lookup@Rva0046F280Owner@@QBEHXZ
// partial score=0.3 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef int Int;
typedef unsigned short UnsignedShort;

// StringBase.cpp: BFMERetailAsciiString(const char*) is the thin 0x888BC0
// body; releaseBuffer() is the pinned 0x887940 body already reused by many
// landed sibling files. The local here is zero-initialized directly (not
// constructed) and only ever populated in place by bfmeGetParamVMZ's output
// parameter, so no ctor is declared -- just the raw layout (data@0,
// length@4, matching every other AsciiString-shaped local in this codebase)
// plus the destructor shape for the four cleanup call sites.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

	char *m_data;

private:
	void releaseBuffer();
};

// Code/GameEngine/Source/Common/BfmeConv1494.cpp
class BfmeStrVMZ;
extern "C" char __cdecl bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out);

// retail 0x0135933C: __imp___stricmp (Open-BFME7 CRT stricmp import slot)
extern "C" int (__cdecl *g_lookup)(const char *, const char *);

struct Rva0046F280Entry
{
	Int value;
	const char *name;
};

#define g_rva0046f280Table ((const Rva0046F280Entry *)0x010F738C)

// retail treats 'this' directly as a (const char*) buffer -- the function
// is not a real method, this is the "custom register convention via a
// TU-local thiscall caller" lever (docs/matching.md) reproducing ecx-as-arg.
class Rva0046F280Owner
{
public:
	Int lookup() const;
};

Int Rva0046F280Owner::lookup() const
{
	const char *hay = (const char *)this;

	BFMERetailAsciiString value;
	value.m_data = 0;

	if (!bfmeGetParamVMZ(hay, (const char *)0x010F73C8, (BfmeStrVMZ *)&value))
		return 2;

	if (value.m_data == 0)
		return 2;

	if (*(UnsignedShort *)(value.m_data + 4) == 0)
		return 2;

	const char *str = value.m_data ? value.m_data + 8 : (const char *)0x0107388B;

	int (__cdecl *cmp)(const char *, const char *) = g_lookup;
	const Rva0046F280Entry *entry = g_rva0046f280Table;

	for (Int i = 0; i < 6; ++i, ++entry)
	{
		if (cmp(entry->name, str) == 0)
			return entry->value;
	}

	return 2;
}
