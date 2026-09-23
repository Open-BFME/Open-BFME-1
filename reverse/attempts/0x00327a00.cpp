// ?d_00327a00@@YAXXZ
// partial score=0.34 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /FAsc /Fabuild/attempt_00327a00_staticlib.cod
//
// ?objectTypesFromParam@ScriptConditions@@KAXPAVParameter@@PAVObjectTypes@@@Z
// The named-by-type conditions call this static cdecl helper.
// It reads a Parameter string and writes an ObjectTypes set.

// stlport
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;

class ThingTemplate;

// This StringBase model uses the one-pointer ABI from StringInline.h.
// Retail inlines AsciiString::isEmpty at this call site.
// The existing WWLib bodies provide the StringBase constructor, set, and destructor.
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

// Parameter stores its string at +0x10 in this script ABI.
// This inline accessor keeps the helper's original pointer arithmetic.
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
	Int prepForPlayerCounting(std::vector<const ThingTemplate *> &templates,
		std::vector<Int> &counts);

private:
	AsciiString m_listName;
	// Retail stores a vptr, an AsciiString, and a vector triple in ObjectTypes.
	// The implicit assignment operator emits StringBase::set and vector assignment.
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

class Condition;

class ScriptConditions
{
public:
	Bool evaluateRva00327A00(Condition *condition,
		Parameter *typeParameter, Parameter *playerParameter);

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


class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;
	ObjectTypesTemp();
	~ObjectTypesTemp()
	{
		if (m_types)
			delete m_types;
	}
};

class Condition
{
public:
	Int getCustomData() const { return m_customData; }
	void setCustomData(Int value) { m_customData = value; }
	Int getCustomFrame() const { return m_customFrame; }
	void setCustomFrame(Int value) { m_customFrame = value; }

private:
	char m_pad[0x44];
	Int m_customData;
	Int m_customFrame;
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

class BfmeP1087
{
public:
	PlayerMaskType bfmeNext1087(Parameter *parameter);
};
extern BfmeP1087 *g_bfmeP1087;

class Player
{
public:
	void countObjectsByThingTemplate(Int count,
		const ThingTemplate *const *templates, Bool ignoreDead,
		Int *counts, Bool ignoreUnderConstruction = true) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};
extern PlayerList *ThePlayerList;

struct ScriptEngineFrameView
{
	char m_pad[0x170d8];
	Int m_frameObjectCountChanged;
};

static Int currentFrameObjectCount()
{
	return reinterpret_cast<ScriptEngineFrameView *>(TheScriptEngine)->m_frameObjectCountChanged;
}

namespace rts
{
	template <typename T>
	T sum(std::vector<T> &values)
	{
		T total = 0;
		for (typename std::vector<T>::iterator it = values.begin();
			it != values.end(); ++it)
			total += *it;
		return total;
	}
}

Bool ScriptConditions::evaluateRva00327A00(
	Condition *condition, Parameter *typeParameter, Parameter *playerParameter)
{
	const ThingTemplate *templateType =
		TheThingFactory->findTemplate(typeParameter->getString());
	if (!templateType)
		return false;

	if (condition->getCustomData() != 0) {
		if (currentFrameObjectCount() == condition->getCustomFrame()) {
			if (condition->getCustomData() == 1)
				return true;
			if (condition->getCustomData() == -1)
				return false;
		}
	}

	ObjectTypesTemp types;
	objectTypesFromParam(typeParameter, types.m_types);

	std::vector<Int> counts;
	std::vector<const ThingTemplate *> templates;
	Int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
	if (numTemplates != 0) {
		PlayerMaskType playerMask = g_bfmeP1087->bfmeNext1087(playerParameter);
		if (playerMask) {
			Player *player = ThePlayerList->getEachPlayerFromMask(playerMask);
			player->countObjectsByThingTemplate(numTemplates,
				&(*templates.begin()), false, &(*counts.begin()), true);
		}
	} else {
		return 0;
	}

	Int sumOfObjects = rts::sum(counts);
	condition->setCustomData(-1);
	if (sumOfObjects != 0)
		condition->setCustomData(1);
	condition->setCustomFrame(currentFrameObjectCount());
	return sumOfObjects != 0;
}
