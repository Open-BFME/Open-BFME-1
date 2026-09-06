// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	AsciiString(const AsciiString &that);
	~AsciiString();
	void set(const AsciiString &that);

private:
	char *m_text;
};

class ScriptActionParameter
{
};

class Object
{
public:
	Int getId() const { return m_id; }

private:
	char m_padding[0x74];
	Int m_id;
};

class Script;

class Bfme5CtorA0
{
public:
	enum MagicEnum { GLUE_NOT_IMPLEMENTED = 0 };
	static void *operator new(unsigned int size, MagicEnum, const char *)
	{
		return ::operator new(size);
	}
	static void operator delete(void *pointer, MagicEnum, const char *)
	{
		::operator delete(pointer);
	}

	Bfme5CtorA0();
	virtual ~Bfme5CtorA0();

	void *m_base;
	Int m_objectID;
	AsciiString m_nameA;
	AsciiString m_nameB;
	Script *m_scriptToExecuteSequentially;
	Int m_currentInstruction;
	Int m_timesToLoop;
	Int m_framesToWait;
	Bool m_dontAdvanceInstruction;
	Bfme5CtorA0 *m_nextScriptInSequence;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Object *resolveUnit(ScriptActionParameter *) = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void slot39() = 0; virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0; virtual void slot44() = 0;
	virtual void slot45() = 0; virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0; virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual Script *findScript(const AsciiString &, AsciiString *) = 0;

	void appendSequentialScript(Bfme5CtorA0 *);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doUnitStartSequentialScript(ScriptActionParameter *, const AsciiString &, Int);
};

// ?doUnitStartSequentialScript@ScriptActions@@IAEXPAVScriptActionParameter@@ABVAsciiString@@H@Z
void ScriptActions::doUnitStartSequentialScript(ScriptActionParameter *unitParameter,
	const AsciiString &scriptName, Int loopVal)
{
	Object *object = TheScriptEngine->resolveUnit(unitParameter);
	if (!object)
		return;

	AsciiString scriptNameOut;
	Script *script = TheScriptEngine->findScript(scriptName, &scriptNameOut);
	if (!script)
		return;

	Bfme5CtorA0 *sequentialScript = new(Bfme5CtorA0::GLUE_NOT_IMPLEMENTED, "") Bfme5CtorA0;
	sequentialScript->m_objectID = object->getId();
	AsciiString *nameA = &sequentialScript->m_nameA;
	nameA->set(scriptNameOut);
	AsciiString *nameB = &sequentialScript->m_nameB;
	nameB->set(scriptName);
	sequentialScript->m_scriptToExecuteSequentially = script;
	sequentialScript->m_timesToLoop = loopVal;
	TheScriptEngine->appendSequentialScript(sequentialScript);
	delete sequentialScript;
}
