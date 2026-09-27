// _Rva004605F0
// partial score=0.96 date=2026-09-27
// ?d_004605f0@@YAXXZ [retail body 0x004605F0]
// Called through the "UpdateFn" slot of Rva00463BA0WindowBounds.cpp as
// void(__cdecl*)(void*,void*) -- re-parses a node's raw text whenever it
// changes and dispatches recognised "&"-delimited tags:
//   "_light<digit>..."  -> bfmeScanDYG("%d=%f,%f,%f", ...) then vtable+0x10
//   "_frame=..."        -> bfmeGetParamVMZ(text,"_AnimMode",&tmp), atoi,
//                          then vtable+0x14, then the temp's destructor
//                          (releaseBuffer, already matched at 0x00887940).
// Strings and imports verified against the retail image:
//   0x010f6fd0="_light" 0x010f6fc0="%d=%f,%f,%f" 0x010f6fb4="_frame="
//   0x010f6fa8="_AnimMode"; 0x01359410 IAT slot resolves to isdigit.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHa

#include "../../../../game/Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *a, const char *b, unsigned n);
extern "C" __declspec(dllimport) int __cdecl bfmeAtoi1027(char *text);
extern "C" __declspec(dllimport) int __cdecl bfmeScanDYG(const char *s, const char *fmt, ...);

// Already-matched helper (BfmeConv1494.cpp); redeclared here with the exact
// signature so this TU's call resolves to the same landed body.
class BfmeStrVMZ
{
public:
	void bfmeReleaseVMZ();
	void bfmeSetVMZ(const char *s, int n);
};
extern char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out);

class Rva004605F0Node
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void setLight(int index, float r, float g, float b);
	virtual void setFrame(int frame, void *extra);

	void *m_unknown04;
	AsciiString m_text;
};

class Rva004605F0Temp
{
public:
	Rva004605F0Temp() : m_data(0) {}
	~Rva004605F0Temp() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

#pragma comment(linker, "/alternatename:?releaseBuffer@Rva004605F0Temp@@AAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct Rva004605F0LightValues
{
	float b;
	float g;
	float r;
	int index;
};

extern "C" void __cdecl Rva004605F0(void *nodeArg, void *textArg)
{
	Rva004605F0Node *node = (Rva004605F0Node *)nodeArg;
	char *text = (char *)textArg;
	char *p;

	if (node == 0)
		return;
	if (text == 0 || *text == 0)
		return;
	if (node->m_text.compare(text) == 0)
		return;

	node->m_text = text;
	p = text;

reparse:
	if (_strnicmp(p, "_light", 6) == 0 && isdigit(p[6]))
	{
		p += 6;
		Rva004605F0LightValues values;
		values.index = 0;
		values.r = 1.0f;
		values.g = 1.0f;
		values.b = 1.0f;
		bfmeScanDYG(p, "%d=%f,%f,%f", &values.index, &values.r,
			&values.g, &values.b);
		node->setLight(values.index, values.r, values.g, values.b);
		goto tail;
	}

	if (_strnicmp(p, "_frame=", 7) == 0)
	{
		Rva004605F0Temp tmp;
		bfmeGetParamVMZ(text, "_AnimMode", (BfmeStrVMZ *)&tmp);
		int frame = bfmeAtoi1027(p + 7);
		node->setFrame(frame, &tmp);
	}

tail:
	for (;;)
	{
		char c = *p;
		if (c == 0)
			return;
		++p;
		if (c == '&')
		{
			if (*p != 0)
				goto reparse;
			return;
		}
		if (*p == 0)
			return;
	}
}
