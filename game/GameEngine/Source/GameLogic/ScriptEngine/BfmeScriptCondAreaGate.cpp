// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: ScriptConditions thiscall gate at retail 0x0032C400 (75B).
// getQualifiedTriggerAreaByName (vtable +0x58) on arg3's string; on success
// invert-call the 700B sibling body at 0x0032C090 via ILT 0x0000C586.

typedef bool Bool;

class PolygonTrigger;

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

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
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
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool bfmeAreaBody(Parameter *a, Parameter *b, Parameter *c);
	Bool bfmeAreaGate(Parameter *a, Parameter *b, Parameter *c);
};

// ?bfmeAreaGate@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::bfmeAreaGate(Parameter *a, Parameter *b, Parameter *c)
{
	PolygonTrigger *trig = TheScriptEngine->getQualifiedTriggerAreaByName(c->getString());
	if (!trig)
		return false;
	return !bfmeAreaBody(a, b, c);
}
