// ?ParseConditionDataChunk@Condition@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.84 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: clean C++ reconstruction of Condition::ParseConditionDataChunk.
//
// The retail BFME parser uses the 0x4c-byte Condition layout and scans the
// 0xb8-condition template table.  The shared Scripts.cpp source is the ZH
// implementation (its current enum ends at 0x6d and its Parameter status
// mask is larger), so this body keeps the BFME layouts local to this TU.

typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
typedef unsigned int NameKeyType;

class BfmeStringLiteralBase
{
	friend class BFMERetailAsciiString;

private:
	BfmeStringLiteralBase(const char *text);
	~BfmeStringLiteralBase();
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text)
	{
		((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase(text);
	}
	BFMERetailAsciiString(const BFMERetailAsciiString &text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void set(const BFMERetailAsciiString &text);

private:
	void releaseBuffer();
	char *m_data;
};

typedef BFMERetailAsciiString AsciiString;

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
};

class DataChunkInput
{
public:
	Int readInt();
	NameKeyType readNameKey();
	DataChunkVersionType getChunkVersion();
	Bool atEndOfChunk();
};

class Parameter
{
public:
	enum ParameterType
	{
		OBJECT_TYPE = 0x0f,
		SIDE = 0x0b,
		SURFACES_ALLOWED = 0x25,
		TEMPLATE_REMAP_TYPE = 0x3d
	};

	__forceinline Parameter(ParameterType type, Int value = 0) :
		m_initialized(false),
		m_paramType(type),
		m_int(value),
		m_real(0.0f)
	{
		m_coord.x = 0.0f;
		m_coord.y = 0.0f;
		m_coord.z = 0.0f;
	}

	static Parameter *ReadParameter(DataChunkInput &file);

	__forceinline ParameterType getParameterType() const
	{
		return m_paramType;
	}

	__forceinline void friend_setString(AsciiString text)
	{
		m_string.set(text);
	}

	__forceinline void friend_setParameterType(ParameterType type)
	{
		m_paramType = type;
	}

private:
	volatile ParameterType m_paramType;
	bool m_initialized;
	Int m_int;
	float m_real;
	AsciiString m_string;
	struct Coord3D
	{
		float x;
		float y;
		float z;
	} m_coord;
	struct ObjectStatusMask
	{
		__forceinline ObjectStatusMask() : m_low(0), m_high(0) {}
		unsigned int m_low;
		unsigned int m_high;
	} m_objectStatus;
};

class ConditionTemplate
{
public:
	__forceinline Int getNumParameters() const
	{
		return m_numParameters;
	}

	__forceinline Int getParameterType(Int index) const
	{
		if (index >= 0 && index < m_numParameters)
			return m_parameters[index];
		return -1;
	}

	char m_prefix[0x0c];
	NameKeyType m_internalNameKey;
	char m_middle[0x34];
	Int m_numParameters;
	Int m_parameters[12];
};

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
	virtual const ConditionTemplate *getConditionTemplate(Int type);
};

extern ScriptEngine *TheScriptEngine;

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

class Condition : public MemoryPoolObject
{
public:
	enum ConditionType
	{
		CONDITION_FALSE = 0,
		SKIRMISH_SPECIAL_POWER_READY = 0x55,
		NUM_ITEMS = 0xb8
	};

	__forceinline Condition() :
		m_conditionType(CONDITION_FALSE),
		m_numParms(0),
		m_nextAndCondition(0),
		m_hasWarnings(0),
		m_customData(0),
		m_customFrame(0)
	{
		for (Int i = 0; i < 12; ++i)
			m_parms[i] = 0;
	}

	static Bool __cdecl ParseConditionDataChunk(DataChunkInput &file,
		DataChunkInfo *info, void *userData);

	__forceinline ConditionType getConditionType() const
	{
		return m_conditionType;
	}

	__forceinline Condition *getNext() const
	{
		return m_nextAndCondition;
	}

	__forceinline void setNextCondition(Condition *condition)
	{
		m_nextAndCondition = condition;
	}

private:
	ConditionType m_conditionType;
	Int m_numParms;
	Parameter *m_parms[12];
	Condition *m_nextAndCondition;
	Int m_hasWarnings;
	Int m_customData;
	unsigned int m_customFrame;
};

class OrCondition
{
public:
	__forceinline Condition *getFirstAndCondition() const
	{
		return m_firstAnd;
	}

	__forceinline void setFirstAndCondition(Condition *condition)
	{
		m_firstAnd = condition;
	}

private:
	void *m_vtable;
	OrCondition *m_nextOr;
	Condition *m_firstAnd;
};

static int ParameterChangesVer2[] =
{
	7, 17, 18, 40, 39, 41, 42, -1
};

Bool __cdecl Condition::ParseConditionDataChunk(DataChunkInput &file,
	DataChunkInfo *info, void *userData)
{
	Condition *pCondition = new Condition;
	OrCondition *pOr = (OrCondition *)userData;
	pCondition->m_conditionType = (ConditionType)file.readInt();
	const ConditionTemplate *ct =
		TheScriptEngine->getConditionTemplate(pCondition->m_conditionType);
	Bool match = false;
	if (info->version >= 4)
	{
		NameKeyType key = file.readNameKey();
		Int i;
		if (ct && ct->m_internalNameKey == key)
			goto condition_name_match;
		for (i = 0; i < Condition::NUM_ITEMS; ++i)
		{
			ct = TheScriptEngine->getConditionTemplate(i);
			if (key == ct->m_internalNameKey)
			{
				pCondition->m_conditionType = (ConditionType)i;
				goto condition_name_match;
			}
		}
		goto condition_name_done;
	condition_name_match:
		match = true;
	condition_name_done:;
	}
	pCondition->m_numParms = file.readInt();
	Int i;
	for (i = 0; i < pCondition->m_numParms; ++i)
	{
		Parameter *parameter = Parameter::ReadParameter(file);
		pCondition->m_parms[i] = parameter;
		if (parameter->getParameterType() != Parameter::OBJECT_TYPE)
			continue;
		if (ct->getNumParameters() > i &&
			ct->getParameterType(i) == Parameter::TEMPLATE_REMAP_TYPE &&
			parameter->getParameterType() == Parameter::OBJECT_TYPE)
		{
			parameter->friend_setParameterType(Parameter::TEMPLATE_REMAP_TYPE);
		}
	}
	if (!match)
	{
		ct = TheScriptEngine->getConditionTemplate(CONDITION_FALSE);
		pCondition->m_conditionType = CONDITION_FALSE;
		while (pCondition->m_numParms > 0)
		{
			--pCondition->m_numParms;
			Parameter *parameter = pCondition->m_parms[pCondition->m_numParms];
			if (parameter)
				delete parameter;
		}
	}

	if (file.getChunkVersion() < 2)
	{
		for (Int j = 0; ParameterChangesVer2[j] != -1; ++j)
		{
			if (pCondition->m_conditionType == (ConditionType)ParameterChangesVer2[j])
			{
				pCondition->m_parms[pCondition->m_numParms] =
					new Parameter(Parameter::SURFACES_ALLOWED, 3);
				pCondition->m_numParms = 3;
			}
		}
	}
	switch (pCondition->getConditionType())
	{
		case SKIRMISH_SPECIAL_POWER_READY:
			if (pCondition->m_numParms == 1)
			{
				pCondition->m_numParms = 2;
				pCondition->m_parms[1] = pCondition->m_parms[0];
				pCondition->m_parms[0] = new Parameter(Parameter::SIDE, 0);
				pCondition->m_parms[0]->friend_setString(AsciiString("<This Player>"));
			}
			break;
	}
	if (ct->getNumParameters() != pCondition->m_numParms)
	{
		pCondition->m_conditionType = CONDITION_FALSE;
		pCondition->m_numParms = 0;
	}
	Condition *pLast = pOr->getFirstAndCondition();
	while (pLast && pLast->getNext())
		pLast = pLast->getNext();
	if (pLast)
		pLast->setNextCondition(pCondition);
	else
		pOr->setFirstAndCondition(pCondition);
	return true;
}
