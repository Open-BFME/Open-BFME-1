// cl: /DNDEBUG /DWIN32 /MD
//
// Open-BFME5: free stdcall helper at retail 0x0032BB30 (70B). ScriptEngine
// getUnitNamed (vtable +0x68) then tests a bit taken from arg2+8 against the
// dword bitset at Object+0x90.

class AsciiString
{
	char *m_data;
};

class Object
{
public:
	char m_pad[0x90];
	unsigned int m_bits[1];
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
	unsigned int m_bit;
};

// ?bfmeScriptUnitBitTest@@YG_NABVAsciiString@@PBUBfmeBitRequest@@@Z
bool __stdcall bfmeScriptUnitBitTest(const AsciiString &name, const BfmeBitRequest *req)
{
	Object *object = TheScriptEngine->getUnitNamed(name);
	if (!object)
		return false;
	unsigned int bit = req->m_bit;
	return (object->m_bits[bit >> 5] & (1u << (bit & 31))) != 0;
}
