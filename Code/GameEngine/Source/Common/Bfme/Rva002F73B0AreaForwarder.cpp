// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// Open-BFME: two-argument member overload reconstructed from retail RVA
// 0x002F73B0.  ScriptActions vtable and load-postprocess xrefs prove that this
// virtual reapplies a saved human-impassable-area state through the three-
// argument target at 0x002F7340.  The original method spelling is not
// recovered, so this translation-unit-local declaration remains address-derived.

typedef bool Bool;

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class ScriptEngineAreaLookup
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void *getArea(BfmeAsciiStringArg areaName) = 0;
};

class ScriptEngine : public ScriptEngineAreaLookup
{
};

class AreaManager
{
public:
	void setArea(void *area, Bool blocked);
};

class AI
{
private:
	char m_beforeAreaManager[0xc];

public:
	AreaManager *m_areaManager;
};

void j_00030b98();
void j_0001e376();

struct BfmeAreaManagerCall
{
	void call(void *area, Bool blocked);
};

struct BfmeSetAreaStateCall
{
	void call(const AsciiString &areaName, Bool blocked);
};

extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

extern void j_00030b98();
extern void j_0001e376();

static __forceinline void bfmeSetArea(AreaManager *areaManager, void *area,
	Bool blocked)
{
	typedef void (BfmeAreaManagerCall::*Function)(void *, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00030b98;
	(reinterpret_cast<BfmeAreaManagerCall *>(areaManager)->*fn.member)(area,
		blocked);
}

static __forceinline void bfmeSetAreaState(ScriptEngine *scriptEngine,
	const AsciiString &areaName, Bool blocked)
{
	typedef void (BfmeSetAreaStateCall::*Function)(const AsciiString &, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001e376;
	(reinterpret_cast<BfmeSetAreaStateCall *>(scriptEngine)->*fn.member)(
		areaName, blocked);
}

class Rva002F73B0Owner
{
public:
    void applyAreaState(const AsciiString &areaName, bool blocked, bool recordState);
    virtual void applyAreaState(const AsciiString &areaName, bool blocked);
};

void Rva002F73B0Owner::applyAreaState(const AsciiString &areaName, bool blocked)
{
    applyAreaState(areaName, blocked, true);
}

void Rva002F73B0Owner::applyAreaState(const AsciiString &areaName,
	bool blocked, bool recordState)
{
	void *area = ((ScriptEngineAreaLookup *)TheScriptEngine)->getArea(areaName);
	if (area)
	{
		AreaManager *areaManager = TheAI->m_areaManager;
		bfmeSetArea(areaManager, area, blocked);
		if (!recordState)
		{
			bfmeSetAreaState(TheScriptEngine, areaName, blocked);
		}
	}
}
