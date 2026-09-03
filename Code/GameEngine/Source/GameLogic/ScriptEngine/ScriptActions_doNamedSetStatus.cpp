// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: UNIT_CHANGE_OBJECT_STATUS handler at retail RVA 0x002FEBD0.

typedef int Int;
#include <string.h>
typedef bool Bool;

template<int NUMBITS>
class BitFlags
{
public:
	BitFlags()
	{
		memset(m_bits, 0, sizeof(m_bits));
	}

	void set(Int idx)
	{
		m_bits[(unsigned)idx >> 5] |= 1u << (idx & 31);
	}

	unsigned m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;

class AsciiString
{
	char *m_data;
};

class Object
{
public:
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);
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

class ScriptActions
{
protected:
	void doNamedSetStatus(const AsciiString &unitName, Int bit, Bool set);
};

void ScriptActions::doNamedSetStatus(const AsciiString &unitName, Int bit, Bool set)
{
	Object *theSrcUnit = TheScriptEngine->getUnitNamed(unitName);
	if (!theSrcUnit) {
		return;
	}

	ObjectStatusMaskType status;
	status.set(bit);
	theSrcUnit->setStatus(status, set);
}
