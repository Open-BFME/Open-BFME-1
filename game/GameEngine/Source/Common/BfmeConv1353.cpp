// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" unsigned strlen(const char *s);
#pragma intrinsic(strlen)

struct BfmeBufVGD
{
	int m_bfme00;
	unsigned short m_bfme04;
};

class BfmeLayoutVGD
{
public:
	BfmeBufVGD *m_bfmeBuf;
};

class BfmeThingVGE
{
public:
	void bfmeGoVGE(const char *s);
	char m_bfmePad[0x10];
	BfmeLayoutVGD m_bfmeStr;
};

void BfmeThingVGE::bfmeGoVGE(const char *s)
{
	BfmeLayoutVGD *p = &m_bfmeStr;
	reinterpret_cast<StringBase<char> *>(p)->set(s, s ? strlen(s) : 0);
}

class BfmeThingVGF
{
public:
	void bfmeGoVGF(const char *s);
	void bfmeGoVGG(const char *s, int i);
	char m_bfmePad[0x200];
	BfmeLayoutVGD m_bfmeStr;
	BfmeLayoutVGD m_bfmeList[64];
};

void BfmeThingVGF::bfmeGoVGF(const char *s)
{
	BfmeLayoutVGD *p = &m_bfmeStr;
	reinterpret_cast<StringBase<char> *>(p)->set(s, s ? strlen(s) : 0);
}

void BfmeThingVGF::bfmeGoVGG(const char *s, int i)
{
	BfmeLayoutVGD *p = &m_bfmeList[i];
	reinterpret_cast<StringBase<char> *>(p)->set(s, s ? strlen(s) : 0);
}

class BfmeThingVGH
{
public:
	void bfmeGoVGH(const char *s);
	char m_bfmePad[0x268];
	BfmeLayoutVGD m_bfmeStr;
};

void BfmeThingVGH::bfmeGoVGH(const char *s)
{
	if (m_bfmeStr.m_bfmeBuf && m_bfmeStr.m_bfmeBuf->m_bfme04)
		return;
	reinterpret_cast<StringBase<char> *>(&m_bfmeStr)->set(s, s ? strlen(s) : 0);
}

extern "C" __declspec(dllimport) unsigned __cdecl wcslen(const unsigned short *s);

class BfmeWideVGI;

class BfmeThingVGI
{
public:
	void bfmeGoVGI(BfmeWideVGI *out);
	char m_bfmePad[0x1e];
	unsigned short m_bfmeBuf[8];
};

void BfmeThingVGI::bfmeGoVGI(BfmeWideVGI *out)
{
	const unsigned short *p = m_bfmeBuf;
	reinterpret_cast<StringBase<unsigned short> *>(out)->set(p, p ? wcslen(p) : 0);
}

class BfmeThingVGJ
{
public:
	char m_bfmePad[0x94];
	BfmeLayoutVGD m_bfmeStr;
};

struct BfmeArgVGJ
{
	int m_bfme00;
	const char *m_bfme04;
};

// Retail's writable-global pointer (0x012ED5C8), defined once in
// Common/GlobalData.cpp. This TU reads one embedded string out of it through
// its own TU-local view, so the canonical declaration plus a cast keeps the
// single linked name.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

int __cdecl bfmeGoVGJ(BfmeArgVGJ *a)
{
	const char *s = a->m_bfme04;
	BfmeLayoutVGD *p = &((BfmeThingVGJ *)TheWritableGlobalData)->m_bfmeStr;
	reinterpret_cast<StringBase<char> *>(p)->set(s, s ? strlen(s) : 0);
	return 2;
}
