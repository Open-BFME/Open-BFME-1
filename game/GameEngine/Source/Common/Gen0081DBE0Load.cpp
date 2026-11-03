// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// The loader beside Gen_0081DBE0::bfmeClear (0x0081DBE0, matched in
// Bfme5HandOffClears.cpp): empty the object, remember the file name in the
// string at +0x08, then run INI::load over it with INI::parseVideoDefinition
// (reached through its ILT thunk j_0001bb4e) as the per-file callback.
//
// The owning class is not proven, so the body keeps the address-derived
// class name its clear already carries and an address-keeping method name.

#include <string.h>

#include "Common/INI/INI.h"

extern void j_0001bb4e();

// INI::load at 0x00853CB0 (matched in INILoadBFMERetail.cpp) takes an Xfer*
// and the block parser; INI.h still declares it as (AsciiString, int, int,
// void *), a spelling nothing defines, so the call binds to the ledger's
// defined name through a member-pointer view of that symbol.
extern "C" void __cdecl __identifier("?load@INI@@QAEXVAsciiString@@HPAVXfer@@P6AXPAV1@@Z@Z")();

typedef void (INI::*BfmeIniLoadPmf)(AsciiString, int, int, void *);
static __forceinline BfmeIniLoadPmf bfmeIniLoadPmf()
{
	union { void (__cdecl *symbol)(); BfmeIniLoadPmf member; } c;
	c.symbol = &__identifier("?load@INI@@QAEXVAsciiString@@HPAVXfer@@P6AXPAV1@@Z@Z");
	return c.member;
}

// Retail inlines the C-string store: the member address goes to ECX first,
// then strlen, then a direct call to StringBase<char>::set(const char *, int).
// ascii_string.h declares operator=(const char *) out of line, so the store is
// spelled here as a by-reference helper of the same shape.
static inline AsciiString &bfmeAssign(AsciiString &dst, const char *text)
{
	dst.StringBase<char>::set(text, text ? (int)strlen(text) : 0);
	return dst;
}

class Gen_0081DBE0
{
public:
	void bfmeClear(void);
	void bfmeLoad_0081DD20(const char *filename);

private:
	int m_bfmeHead[2];					// +0x00
	AsciiString m_bfmeNameA;				// +0x08
};

// ?bfmeLoad_0081DD20@Gen_0081DBE0@@QAEXPBD@Z
// Retail 0x0081DD20, 171 bytes.
void Gen_0081DBE0::bfmeLoad_0081DD20(const char *filename)
{
	bfmeClear();
	bfmeAssign(m_bfmeNameA, filename);

	INI ini;
	(ini.*bfmeIniLoadPmf())(AsciiString(filename), 1, 0, (void *)j_0001bb4e);
}
