// cl: /DNDEBUG /MD /EHsc -D_OPERATOR_NEW_DEFINED_ -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Iinputs/reference/shims/ini_bfme -Iinputs/reference/shims/sweep -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include -Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// stlport
// Open-BFME5 conversions. The appender this body calls at 0x00850920 is
// MultiIniFieldParse::add(const FieldParse*, unsigned), so the call goes
// through the defining class, taken from the real Common/INI.h.
//
// The receiver stays spelled BfmeMultiVHI because this file's own matched row is
// ?bfmeGoVHI@@YAXPAVBfmeMultiVHI@@@Z; renaming the parameter type would rename
// the enclosing body and unmatch that row.

#include "Common/INI.h"

struct BfmeParseVHI;

extern BfmeParseVHI g_bfmeParseAVHI[];
extern BfmeParseVHI g_bfmeParseBVHI[];

const BfmeParseVHI *bfmeGetParseCVHI();

class BfmeMultiVHI
{
};

void __cdecl bfmeGoVHI(BfmeMultiVHI *m)
{
	MultiIniFieldParse *p = reinterpret_cast<MultiIniFieldParse *>(m);
	p->add(reinterpret_cast<const FieldParse *>(g_bfmeParseAVHI), 0);
	p->add(reinterpret_cast<const FieldParse *>(g_bfmeParseBVHI), 8);
	p->add(reinterpret_cast<const FieldParse *>(bfmeGetParseCVHI()), 0x84);
}

bool __cdecl _bfme_debugReportingEnabled();
void __cdecl bfmeRecordVHJ(int n);

class BfmeMsgVHJ
{
public:
	virtual void bfmeSlot00VHJ();
	virtual void bfmeSlot04VHJ();
	virtual void bfmeSlot08VHJ();
	virtual void bfmeSlot0CVHJ();
	virtual void bfmeSlot10VHJ();
	virtual void bfmeSlot14VHJ();
	virtual void bfmeSlot18VHJ();
	virtual void bfmeSlot1CVHJ();
	virtual void bfmeSlot20VHJ();
	virtual void bfmeSlot24VHJ();
	virtual void bfmeSlot28VHJ();
	virtual void bfmeSlot2CVHJ();
	virtual void bfmeSlot30VHJ();
	virtual void bfmeSlot34VHJ();
	virtual BfmeMsgVHJ *bfmeSlot38VHJ(const char *t);
	virtual void bfmeSlot3CVHJ();
	virtual void bfmeSlot40VHJ();
	virtual void bfmeSlot44VHJ();
	virtual void bfmeSlot48VHJ();
	virtual void bfmeSlot4cVHJ(int n);
	virtual void bfmeSlot50VHJ();
	virtual void bfmeSlot54VHJ();
	virtual void bfmeSlot58VHJ();
	virtual void bfmeSlot5CVHJ();
	virtual void bfmeSlot60VHJ();
	virtual void bfmeSlot64VHJ();
	virtual void bfmeSlot68VHJ();
	virtual void bfmeSlot6CVHJ();
};

struct Rva00889690Obj
{
public:
	virtual void bfmeOwn00VHJ();
	virtual void bfmeOwn04VHJ();
	virtual void bfmeOwn08VHJ();
	virtual void bfmeOwn0CVHJ();
	virtual void bfmeOwn10VHJ();
	virtual void bfmeOwn14VHJ();
	virtual void bfmeOwn18VHJ();
	virtual void bfmeOwn1CVHJ();
	virtual void bfmeOwn20VHJ();
	virtual void bfmeOwn24VHJ();
	virtual void bfmeOwn28VHJ();
	virtual void bfmeOwn2CVHJ();
	virtual void bfmeOwn30VHJ();
	virtual void bfmeOwn34VHJ();
	virtual void bfmeOwn38VHJ();
	virtual void bfmeOwn3CVHJ();
	virtual void bfmeOwn40VHJ();
	virtual void bfmeOwn44VHJ();
	virtual void bfmeOwn48VHJ();
	virtual void bfmeOwn4CVHJ();
	virtual void bfmeOwn50VHJ();
	virtual void bfmeOwn54VHJ();
	virtual void bfmeOwn58VHJ();
	virtual void bfmeOwn5CVHJ();
	virtual void bfmeOwn60VHJ();
	virtual void bfmeOwn64VHJ();
	virtual void bfmeOwn68VHJ();
	virtual class BfmeMsgVHJ *bfmeOwn6cVHJ(int a, int b);
};

extern Rva00889690Obj *g_rva00889690;

char __stdcall bfmeGoVHK(int a, int b, int c, int d, int e, int f)
{
	if (_bfme_debugReportingEnabled())
	{
		bfmeRecordVHJ(1);
		g_rva00889690->bfmeOwn60VHJ();
		g_rva00889690->bfmeOwn6cVHJ(0, 0)->bfmeSlot38VHJ("GlowOutline buffs are no longer supported. They need to be removed from an INI file.")->bfmeSlot4cVHJ(2);
	}
	return 0;
}
