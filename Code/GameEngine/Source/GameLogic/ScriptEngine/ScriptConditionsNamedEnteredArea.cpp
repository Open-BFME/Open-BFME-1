// cl: /DNDEBUG /MD /EHsc
// Byte-exact BFME body of the NAMED_ENTERED_AREA condition, retail 0x0032B840.
//
// executeCondition subtracts five from the condition type and dispatches type
// 38 through arm 0x0032DFEA. That arm calls the 0x000103A2 ILT, whose thunk
// lands at this body. The canonical condition table calls type 38
// "NAMED_ENTERED_AREA" with two parameters (unit name and trigger area), and
// ScriptConditions::executeCondition names this exact evaluator. The body is
// the matching BFME source-level test: getUnitNamed, reject inert units,
// resolve the qualified trigger area, then ask Object::didEnter.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord3D { Int x, y, z; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;
	unsigned char m_beforeString[0x10 - 0x0c];
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride(void) const; // ILT 0x000022BB

	void *m_vtable;
	Overridable *m_nextOverride;
};

// BFME's ThingTemplate has its compact KindOf word at +0xD0; bit 24 is
// KINDOF_INERT. This offset and flag are also recovered in ObjectFields.cpp.
enum KindOfType
{
	KINDOF_INERT = 24
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType type) const
	{
		return (m_kindof & (1UL << type)) != 0;
	}

private:
	unsigned char m_bfmeTemplatePad[0xc8];
	UnsignedInt m_kindof;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class PolygonTrigger;
class Object
{
public:
	Bool isKindOf(KindOfType type) const
	{
		const ThingTemplate *templateValue = m_template;
		if (templateValue != 0 && templateValue->m_nextOverride != 0)
			templateValue = (const ThingTemplate *)templateValue->m_nextOverride->getFinalOverride();
		return templateValue->isKindOf(type);
	}

	Bool didEnter(const PolygonTrigger *pTrigger) const; // ILT 0x0002B24C

private:
	void *m_vtable;
	ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void *slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString) = 0; // slot 22, +0x58
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0; // slot 26, +0x68
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateNamedEnteredArea(Parameter *, Parameter *);
};

// ?evaluateNamedEnteredArea@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedEnteredArea(Parameter *pUnitParm, Parameter *pTriggerParm)
{
	Object *pUnit = TheScriptEngine->getUnitNamed(*(const AsciiString *)pUnitParm);
	if (!pUnit)
		return false;

	if (pUnit->isKindOf(KINDOF_INERT))
		return false;

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (!pTrig)
		return false;

	return (pUnit->didEnter(pTrig));
}
