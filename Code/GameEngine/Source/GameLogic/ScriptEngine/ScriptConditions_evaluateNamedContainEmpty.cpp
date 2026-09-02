// cl: /DNDEBUG /DWIN32 /MD
// Twin of evaluateIsBuildingEmpty (0x003242F0) with the ZH empty-container
// return (count == 0) instead of the occupied (count > 0) form.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class AsciiString
{
	char *m_data;
};

class Parameter;

#define BFME_SLOT(N) virtual void slot##N() = 0

class BfmeNamedContain
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03);
	BFME_SLOT(04); BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07);
	BFME_SLOT(08); BFME_SLOT(09); BFME_SLOT(10); BFME_SLOT(11);
	BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14); BFME_SLOT(15);
	BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23);
	BFME_SLOT(24); BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27);
	BFME_SLOT(28); BFME_SLOT(29); BFME_SLOT(30); BFME_SLOT(31);
	BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34); BFME_SLOT(35);
	BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43);
	BFME_SLOT(44); BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47);
	BFME_SLOT(48); BFME_SLOT(49); BFME_SLOT(50); BFME_SLOT(51);
	BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54); BFME_SLOT(55);
	BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58); BFME_SLOT(59);
	BFME_SLOT(60); BFME_SLOT(61); BFME_SLOT(62); BFME_SLOT(63);
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;
};

#undef BFME_SLOT

class BfmeNamedContainObject
{
public:
	unsigned char m_unreconstructed[0x1FC];
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
	unsigned char evaluateNamedContainEmpty(Parameter *pItemParm);
};

unsigned char ScriptConditions::evaluateNamedContainEmpty(Parameter *pItemParm)
{
	BfmeNamedContainObject *obj = TheScriptEngine->getUnitNamed(
		*reinterpret_cast<const AsciiString *>(pItemParm));
	if (obj == 0) {
		return 0;
	} else {
		BfmeNamedContain *contain = obj->m_contain;
		if (contain == 0)
			return 0;
		return (unsigned char)(contain->getContainCount(false) <= 0);
	}
}
