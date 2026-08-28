// cl: /DNDEBUG /MD /EHsc
// readable body of ?setConditionType@Condition@@QAEXW4ConditionType@1@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp

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
class Parameter
{
public:
	enum ParameterType { INT = 0 };
	Parameter(ParameterType type, int value = 0) :
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
class ConditionTemplate
{
	unsigned char m_pad[0x44];
	int m_numParameters;
	Parameter::ParameterType m_parameters[12];
public:
	int getNumParameters() const { return m_numParameters; }
	Parameter::ParameterType getParameterType(int index) const
	{
		if (index >= 0 && index < m_numParameters)
			return m_parameters[index];
		return Parameter::INT;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
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
	virtual void slot10();
	virtual const ConditionTemplate *getConditionTemplate(int type);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Condition
{
public:
	enum ConditionType {};
	void setConditionType(ConditionType type);

private:
	unsigned int m_poolLink;
	ConditionType m_conditionType;
	int m_numParms;
	Parameter *m_parms[12];
};

// ?setConditionType@Condition@@QAEXW4ConditionType@1@@Z
void Condition::setConditionType(ConditionType type)
{
	int i;
	for (i = 0; i < m_numParms; ++i)
	{
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}

	m_conditionType = type;
	const ConditionTemplate *conditionTemplate = TheScriptEngine->getConditionTemplate(m_conditionType);
	m_numParms = conditionTemplate->getNumParameters();
	for (i = 0; i < m_numParms; ++i)
		m_parms[i] = new Parameter(conditionTemplate->getParameterType(i));
}
