// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: retail 0x004605F0, the (void*, void*) update callback of Rva00463BA0WindowBounds.cpp.
// Owner and class are unproven, so every name here is address-derived.

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *a, const char *b, unsigned n);
extern "C" __declspec(dllimport) int __cdecl atoi(char *text);
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *s, const char *fmt, ...);

// Landed in BfmeConv1494.cpp; declared with the same spelling so the call binds to that body.
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

struct Rva004605F0LightValues
{
	float b;
	float g;
	float r;
	int index;
};

// Caches the node's text, then applies each "&"-separated "_light<n>=r,g,b" or
// "_frame=<n>" tag through the node's virtual setters; the unwind funclet calls ~AsciiString.
void __cdecl Rva004605F0(void *nodeArg, void *textArg)
{
	Rva004605F0Node *node = (Rva004605F0Node *)nodeArg;
	char *text = (char *)textArg;
	char *p;

	if (node == 0)
		return;
	if (text == 0 || *text == 0)
		return;
	if (node->m_text.StringBase<char>::compare(text) == 0)
		return;

	node->m_text = text;
	p = text;

	do
	{
		if (_strnicmp(p, "_light", 6) == 0 && isdigit(p[6]))
		{
			p += 6;
			Rva004605F0LightValues values;
			values.index = 0;
			values.r = 1.0f;
			values.g = 1.0f;
			values.b = 1.0f;
			sscanf(p, "%d=%f,%f,%f", &values.index, &values.r,
				&values.g, &values.b);
			node->setLight(values.index, values.r, values.g, values.b);
		}
		else if (_strnicmp(p, "_frame=", 7) == 0)
		{
			AsciiString tmp;
			bfmeGetParamVMZ(text, "_AnimMode", (BfmeStrVMZ *)&tmp);
			int frame = atoi(p + 7);
			node->setFrame(frame, &tmp);
		}

		while (*p != 0)
		{
			if (*p++ == '&')
				break;
		}
	} while (*p != 0);
}
