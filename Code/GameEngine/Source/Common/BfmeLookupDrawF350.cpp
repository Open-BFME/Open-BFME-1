// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: retail 0x002EF350, 57 bytes.
// executeAction calls this. ScriptEngine getUnitNamed (slot 26) then Object
// getDrawable (slot 10) twice, then BfmeOwner1158::bfmeStopAll1158 via ILT
// 0x0001DA8E. Not doEnableObjectSound -- that callee is enableAmbientSoundFromScript.

class AsciiString
{
	char *m_data;
};

class BfmeArg1158;

class BfmeOwner1158
{
public:
	void bfmeStopAll1158(BfmeArg1158 *a);
};

class Object
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void unusedSlot06();
	virtual void unusedSlot07();
	virtual void unusedSlot08();
	virtual void unusedSlot09();
	virtual BfmeOwner1158 *getDrawable(void) const;
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

void __stdcall bfmeLookupDrawF350(const AsciiString &name, BfmeArg1158 *arg)
{
	Object *object = TheScriptEngine->getUnitNamed(name);
	if (!object)
	{
		return;
	}

	if (object->getDrawable())
	{
		object->getDrawable()->bfmeStopAll1158(arg);
	}
}
