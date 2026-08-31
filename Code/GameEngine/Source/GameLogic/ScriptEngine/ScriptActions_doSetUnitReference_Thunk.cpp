// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

class Object;

class ScriptActionParameter
{
	friend class ScriptActions;

private:
	unsigned char m_unmodelled[0x10];
	AsciiString m_string;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *resolveUnit(ScriptActionParameter *) = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void bindUnitReference(Object *, const AsciiString &) = 0;

	void assignUnitReference(const AsciiString &, Object *);
	void copyUnitReference(const AsciiString &, AsciiString);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doSetUnitReference(
		const AsciiString &, ScriptActionParameter *, Bool);
};

// ?doSetUnitReference@ScriptActions@@IAEXABVAsciiString@@PAVScriptActionParameter@@_N@Z
void ScriptActions::doSetUnitReference(const AsciiString &referenceName,
	ScriptActionParameter *parameter, Bool referenceToReference)
{
	if (referenceToReference) {
		TheScriptEngine->copyUnitReference(referenceName, parameter->m_string);
		return;
	}

	Object *object = TheScriptEngine->resolveUnit(parameter);
	TheScriptEngine->assignUnitReference(referenceName, object);
	TheScriptEngine->bindUnitReference(object, referenceName);
}
