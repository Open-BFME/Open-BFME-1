// cl: /DNDEBUG /MD
// ScriptConditions::evaluateNamedHasFreeContainerSlots.

typedef bool Bool;
typedef int Int;

class AsciiString
{
	char *m_data;
};

class Parameter;

class BfmeNamedContain
{
public:
	Int getContainCount(void) const;
	Int getContainMax(void) const { return m_max; }

private:
	unsigned char m_pad[0x28];
	Int m_max;
};

class BfmeNamedContainObject
{
public:
	unsigned char m_unreconstructed[0x210];
	BfmeNamedContain *m_contain;
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
	virtual BfmeNamedContainObject *getUnitNamed(const AsciiString &name) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateNamedHasFreeContainerSlots(Parameter *pUnitParm);
};

Bool ScriptConditions::evaluateNamedHasFreeContainerSlots(Parameter *pUnitParm)
{
	if (!pUnitParm) {
		return false;
	}

	BfmeNamedContainObject *pUnit = TheScriptEngine->getUnitNamed(
		*reinterpret_cast<const AsciiString *>(pUnitParm));
	if (!pUnit) {
		return false;
	}

	BfmeNamedContain *contain = pUnit->m_contain;
	if (contain) {
		Int max = contain->getContainMax();
		Int cur = contain->getContainCount();
		if (max > cur) {
			return true;
		}
	}
	return false;
}
