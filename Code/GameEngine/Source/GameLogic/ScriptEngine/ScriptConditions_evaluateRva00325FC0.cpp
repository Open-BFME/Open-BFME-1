// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ScriptConditions body at 0x00325FC0, 225 bytes.
// Address-derived condition identity: the retail body compares parameter+0x10
// with the string at Object->field210+8. The original condition name and
// field210 owner type are not proven by the matching body.
// ScriptEngine slot0x68 is retail resolveUnit at34CA20: cached object ID24,
// then name10 lookup. Its80B body confirms the Parameter pointer ABI.

typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

struct BfmeStringData { int references; unsigned short length; unsigned short capacity; char text[1]; };

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

	BfmeStringData *m_text;
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class BfmeObjectField210
{
public:
	unsigned char m_beforeName[8];
	AsciiString m_name;
};

class Object
{
public:
	unsigned char m_beforeBody[0x210];
	BfmeObjectField210 *m_body;
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
	virtual Object *resolveUnitParameter(Parameter *) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateRva00325FC0(Parameter *, Parameter *);
};

// ?evaluateRva00325FC0@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateRva00325FC0(
	Parameter *pUnitParm, Parameter *pNameParm)
{
	if (!pUnitParm)
		return false;
	if (!pNameParm)
		return false;

	Object *obj = TheScriptEngine->resolveUnitParameter(pUnitParm);
	if (!obj)
		return false;

	AsciiString name = pNameParm->getString();
	BfmeStringData *p = name.m_text;
	if (p && p->length) {
		BfmeObjectField210 *body = obj->m_body;
		if (body) {
			BfmeStringData *q = body->m_name.m_text;
			const char *right = p->text;
			const char *left = q ? q->text : "";
			return _strcmpi(left, right) == 0;
		}
	}

	return false;
}
