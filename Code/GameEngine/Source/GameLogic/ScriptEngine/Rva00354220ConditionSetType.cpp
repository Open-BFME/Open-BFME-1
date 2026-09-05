// cl: /DNDEBUG /MD /EHsc
// Near-twin of Condition::setConditionType (twin 0x00355D10,
// Condition_setConditionType_Thunk.cpp): identical parameter-rebuild shape,
// but getConditionTemplate sits at vtable slot 0x28 here instead of 0x2c --
// one fewer virtual ahead of it on this ScriptEngine-shaped interface, so
// this is a sibling on a slightly different vtable and kept address-derived.

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	void *m_data;
public:
	AsciiString() : m_data(0) {}
	~AsciiString();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

class ObjectStatusMask
{
	unsigned int m_bits[2];
public:
	ObjectStatusMask() { m_bits[0] = 0; m_bits[1] = 0; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Rva00354220Parameter
{
public:
	enum ParameterType { INT = 0 };
	Rva00354220Parameter(ParameterType type, int value = 0) :
		m_initialized(false),
		m_paramType(type),
		m_int(value),
		m_real(0)
	{
		m_coord.x = 0;
		m_coord.y = 0;
		m_coord.z = 0;
	}
	void deleteInstance() { delete this; }

private:
	ParameterType m_paramType;
	bool m_initialized;
	unsigned char m_padding[3];
	int m_int;
	float m_real;
	AsciiString m_string;
	Coord3D m_coord;
	ObjectStatusMask m_objectStatus;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Rva00354220ConditionTemplate
{
	unsigned char m_pad[0x44];
	int m_numParameters;
	Rva00354220Parameter::ParameterType m_parameters[12];
public:
	int getNumParameters() const { return m_numParameters; }
	Rva00354220Parameter::ParameterType getParameterType(int index) const
	{
		if (index >= 0 && index < m_numParameters)
			return m_parameters[index];
		return Rva00354220Parameter::INT;
	}
};

// address-derived: one fewer leading virtual than ScriptEngine in
// Condition_setConditionType_Thunk.cpp, so getConditionTemplate lands at
// slot 0x28 instead of 0x2c.
class Rva00354220ScriptEngine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual const Rva00354220ConditionTemplate *getConditionTemplate(int type);
};

extern Rva00354220ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Rva00354220Condition
{
public:
	enum ConditionType {};
	void setConditionType(ConditionType type);

private:
	unsigned int m_poolLink;
	ConditionType m_conditionType;
	int m_numParms;
	Rva00354220Parameter *m_parms[12];
};

// @?setConditionType@Rva00354220Condition@@QAEXW4ConditionType@1@@Z 0x00354220
void Rva00354220Condition::setConditionType(ConditionType type)
{
	int i;
	for (i = 0; i < m_numParms; ++i)
	{
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}

	m_conditionType = type;
	const Rva00354220ConditionTemplate *conditionTemplate = TheScriptEngine->getConditionTemplate(m_conditionType);
	m_numParms = conditionTemplate->getNumParameters();
	for (i = 0; i < m_numParms; ++i)
		m_parms[i] = new Rva00354220Parameter(conditionTemplate->getParameterType(i));
}
