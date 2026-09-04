// cl: /DNDEBUG /DWIN32 /MD
//
// Open-BFME5: free stdcall helper at retail 0x0032C620 (75B). ScriptEngine
// getUnitNamed (vtable +0x68), walk Object+4 ThingTemplate through
// m_nextOverride->friend_getFinalOverride (ILT 0x22BB -> 0x87A80), then
// compare bit 26 of dword +0xD8 to (arg2+8 != 0). Sibling of
// bfmeScriptUnitBitTest at 0x0032BB30.

class AsciiString
{
	char *m_data;
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	void *m_vtable;                  // +0
	BfmeOverridable *m_nextOverride; // +4
};

class ThingTemplate : public BfmeOverridable
{
public:
	char m_pad[0xD0];            // +8 .. +0xD7
	unsigned int m_flagsD8;      // +0xD8
};

class Object
{
public:
	char m_pad0[4];
	ThingTemplate *m_template; // +4
};

class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual void _se_17() = 0;
	virtual void _se_18() = 0;
	virtual void _se_19() = 0;
	virtual void _se_20() = 0;
	virtual void _se_21() = 0;
	virtual void _se_22() = 0;
	virtual void _se_23() = 0;
	virtual void _se_24() = 0;
	virtual void _se_25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

extern ScriptEngine *TheScriptEngine;

struct BfmeBitRequest
{
	char m_pad[8];
	unsigned int m_value;
};

// ?bfmeScriptUnitTemplateBitEq@@YG_NABVAsciiString@@PBUBfmeBitRequest@@@Z
bool __stdcall bfmeScriptUnitTemplateBitEq(const AsciiString &name, const BfmeBitRequest *req)
{
	Object *object = TheScriptEngine->getUnitNamed(name);
	if (!object)
		return false;
	ThingTemplate *tmpl = object->m_template;
	if (tmpl)
	{
		if (tmpl->m_nextOverride)
			tmpl = (ThingTemplate *)tmpl->m_nextOverride->friend_getFinalOverride();
	}
	unsigned char bit = (unsigned char)((tmpl->m_flagsD8 >> 26) & 1);
	unsigned char expect = req->m_value != 0;
	if (bit == expect)
		return true;
	return false;
}
