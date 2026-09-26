// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// ?objectTypesFromParam@ScriptConditions@@KAXPAVParameter@@PAVObjectTypes@@@Z
// Retail's helper used by the named-by-type conditions.  The implementation
// is a static cdecl helper in that source family; its two callers pass a
// Parameter string view followed by the destination ObjectTypes set.

// stlport
#include <vector>

// This is the same one-pointer StringBase ABI used by StringInline.h, with
// the length test exposed here because retail inlines AsciiString::isEmpty at
// this call site.  The out-of-line StringBase ctor, set, and dtor are the
// established WWLib bodies; this TU only supplies their real C++ call shapes.
template <typename T> struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

private:
	void set(const StringBase<T> &other);

private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&other);
		return *this;
	}

	bool isEmpty() const
	{
		return m_data == 0 || m_data->m_length == 0;
	}
};

// Parameter's string field is at +0x10 in the retail script ABI.  Keeping
// this accessor inline leaves the caller's original pointer arithmetic in
// the helper rather than introducing a non-retail callee.
class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes();
	void addObjectType(const AsciiString &objectType);

private:
	AsciiString m_listName;
	// Retail's ObjectTypes layout is vptr, AsciiString, vector triple.
	// The implicit assignment operator is intentional: it emits the proven
	// StringBase set call followed by the established vector assignment body.
	std::vector<AsciiString> m_objectTypes;
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
	virtual ObjectTypes *getObjectTypes(const AsciiString &objectTypeList) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{

protected:
	static void objectTypesFromParam(Parameter *pTypeParm,
		ObjectTypes *outObjectTypes);
};

void ScriptConditions::objectTypesFromParam(Parameter *pTypeParm,
	ObjectTypes *outObjectTypes)
{
	if (!outObjectTypes) {
		return;
	}

	AsciiString str = pTypeParm->getString();

	if (str.isEmpty()) {
		return;
	}

	ObjectTypes *types = TheScriptEngine->getObjectTypes(str);
	if (!types) {
		outObjectTypes->addObjectType(str);
	} else {
		*outObjectTypes = *types;
	}
}
