// _Rva004605F0
// partial score=0.26 date=2026-09-21
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
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" int __cdecl isdigit(int c);
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

// Embedded compare/cache field at node+8; releaseBuffer is the already
// matched StringBase release body (0x00887940).
class Rva004605F0Text
{
public:
	Rva004605F0Text();
	int bfmeCompare1294(const char *text) const;
	Rva004605F0Text &operator=(const char *text);
	~Rva004605F0Text();

private:
	void releaseBuffer(void);
	void *m_data;
};

Rva004605F0Text::Rva004605F0Text() : m_data(0) {}
Rva004605F0Text::~Rva004605F0Text() { releaseBuffer(); }

class Rva004605F0Node
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);
	virtual void slot3(void);
	virtual void setLight(int index, float r, float g, float b);
	virtual void setFrame(int frame, void *extra);

	Rva004605F0Text m_text;
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
	if (node->m_text.bfmeCompare1294(text) == 0)
		return;

	node->m_text = text;
	p = text;

reparse:
	if (_strnicmp(p, "_light", 6) == 0 && isdigit((unsigned char)p[6]))
	{
		int index = 0;
		float r = 1.0f, g = 1.0f, b = 1.0f;
		bfmeScanDYG(p + 6, "%d=%f,%f,%f", &b, &g, &r, &index);
		node->setLight(index, r, g, b);
		p += 6;
		goto tail;
	}

	if (_strnicmp(p, "_frame=", 7) == 0)
	{
		Rva004605F0Text tmp;
		bfmeGetParamVMZ(text, "_AnimMode", (BfmeStrVMZ *)&tmp);
		int frame = bfmeAtoi1027(p + 7);
		node->setFrame(frame, &tmp);
	}

tail:
	while (*p != 0 && *p != '&')
		p++;
	if (*p == 0)
		return;
	p++;
	if (*p == 0)
		return;
	goto reparse;
}
