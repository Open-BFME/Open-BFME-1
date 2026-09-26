// cl: /DNDEBUG /MD /EHsc
// ?ParseAction@ScriptAction@@KAPAV1@AAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// readable ZH body: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
//
// BFME ScriptAction::ParseAction for retail 0x00358370 (2545 B: code, then the
// three switch jump tables and their index bytes, ending at the int3 pad).
// Identity: the reloc/export name, and ParseActionDataChunk (0x00358FE0) and
// its ParseActionFalseDataChunk twin call it through the link thunk.
//
// Differences from Zero Hour, all read off the retail bytes: plain operator
// new for the 0x48-byte action (inline protected ctor with the +0x44 tail) and
// for 0x28-byte Parameters; ScriptEngine::getActionTemplate is virtual slot
// 10; the version-2 name check also accepts the renamed
// BUILD_BASE_BUILDING_* spellings for action 0x181; a Sleep(0) /
// serviceWindowsOS yield after each phase; OBJECT_TYPE parameters are
// retyped to 0x3d where the template asks for it (same as
// Condition::ParseConditionDataChunk); and a BFME set of heal-old-files
// cases. Case values come from the retail jump tables, not the ZH enum, so
// they stay numeric. Parameter types up to AI_MOOD keep their ZH ordinals;
// 0x34 and 0x3d are left unnamed. The template retype re-reads the parameter
// type, which retail does; the barrier keeps that second read.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
enum NameKeyType { NAMEKEY_INVALID = 0 };

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

template <class T> class StringBase
{
public:
	int compare(const T *str) const throw();
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

private:
	friend class AsciiString;
	friend class Parameter;
	void releaseBuffer();
	char *m_data;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text)
	{
		((BFMERetailAsciiString *)this)->BFMERetailAsciiString::BFMERetailAsciiString(text);
	}
	~AsciiString() { ((BFMERetailAsciiString *)this)->releaseBuffer(); }
	int compare(const char *text) const { return ((const StringBase<char> *)this)->compare(text); }

private:
	char *m_data;
};

AsciiString KEYNAME(NameKeyType key);

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
};

class GameEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void serviceWindowsOS();
};
extern GameEngine *TheGameEngine;

static inline void yieldToOS(void)
{
	Sleep(0);
	if (TheGameEngine)
		TheGameEngine->serviceWindowsOS();
}

// Parameter's by-value string setter (ZH friend_setString); the ledger names
// the body by address only, so Parameter reaches it through this empty base.
class Gen002E3FD0
{
public:
	void bfmeSet(AsciiString value);
};

class Parameter : public Gen002E3FD0
{
public:
	enum ParameterType
	{
		INT = 0,
		REAL = 1,
		BOOLEAN = 8,
		SIDE = 11,
		OBJECT_TYPE = 15,
		AI_MOOD = 20
	};

	Parameter(ParameterType type, Int val = 0) :
		m_paramType(type),
		m_initialized(false),
		m_int(val),
		m_real(0.0f),
		m_objectStatus0(0),
		m_objectStatus1(0)
	{
		m_coord.x = 0.0f;
		m_coord.y = 0.0f;
		m_coord.z = 0.0f;
	}
	static Parameter *ReadParameter(DataChunkInput &file);

	ParameterType getParameterType() const { return m_paramType; }
	Int getInt() const { return m_int; }
	void friend_setParameterType(ParameterType type) { m_paramType = type; }

private:
	ParameterType m_paramType;
	Bool m_initialized;
	Int m_int;
	float m_real;
	AsciiString m_string;
	struct { float x, y, z; } m_coord;
	unsigned int m_objectStatus0;
	unsigned int m_objectStatus1;
};

class ActionTemplate
{
public:
	Int getNumParameters() const { return m_numParameters; }
	Int getParameterType(Int ndx) const
	{
		if (ndx >= 0 && ndx < m_numParameters)
			return m_parameters[ndx];
		return 0;
	}

	char m_head[0x04];
	AsciiString m_name;
	AsciiString m_internalName;
	NameKeyType m_internalNameKey;
	char m_middle[0x34];
	Int m_numParameters;
	Int m_parameters[12];
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual const ActionTemplate *getActionTemplate(Int type);
};
extern ScriptEngine *TheScriptEngine;

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	enum { NO_OP = 5, NUM_ITEMS = 0x21f };
	virtual ~ScriptAction();

protected:
	ScriptAction() :
		m_actionType(NO_OP),
		m_numParms(0),
		m_nextAction(0),
		m_hasWarnings(false),
		m_bfmeActionTail(0)
	{
		Int i;
		for (i = 0; i < MAX_PARMS; i++) {
			m_parms[i] = 0;
		}
	}

	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData);

	Int getActionType() const { return m_actionType; }
	Int getNumParameters() const { return m_numParms; }

	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	Bool m_hasWarnings;
	Int m_bfmeActionTail;
};

ScriptAction *ScriptAction::ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	ScriptAction *pScriptAction = new ScriptAction;

	pScriptAction->m_actionType = file.readInt();

	const ActionTemplate *at = TheScriptEngine->getActionTemplate(pScriptAction->m_actionType);
	if (info->version >= 2) {
		NameKeyType key = file.readNameKey();
		Bool match = false;
		if (at) {
			if (at->m_internalNameKey == key) {
				match = true;
			} else if (pScriptAction->m_actionType == 0x181 &&
				(at->m_internalName.compare("BUILD_BASE_BUILDING_PER_TACTICAL_MARKER") == 0 ||
				 at->m_internalName.compare("BUILD_BASE_BUILDING_PER_TACTIC") == 0)) {
				match = true;
			}
		}
		if (!match && pScriptAction->m_actionType == 0x181) {
			AsciiString name = KEYNAME(key);
			if (name.compare("BUILD_BASE_BUILDING_PER_TACTICAL_MARKER") == 0 ||
				name.compare("BUILD_BASE_BUILDING_WITH_TACTIC") == 0) {
				match = true;
			}
		}
		if (!match) {
			Int i;
			for (i = 0; i < ScriptAction::NUM_ITEMS; i++) {
				at = TheScriptEngine->getActionTemplate(i);
				if (key == at->m_internalNameKey) {
					match = true;
					pScriptAction->m_actionType = i;
					break;
				}
			}
			if (!match) {
				pScriptAction->m_actionType = ScriptAction::NO_OP;
				pScriptAction->m_numParms = 0;
			}
		}
	}
	yieldToOS();

	pScriptAction->m_numParms = file.readInt();
	Int i;
	for (i = 0; i < pScriptAction->m_numParms; i++) {
		Parameter *parameter = Parameter::ReadParameter(file);
		pScriptAction->m_parms[i] = parameter;
		if (parameter->getParameterType() == Parameter::OBJECT_TYPE && at->getNumParameters() > i &&
			at->getParameterType(i) == 0x3d) {
			_ReadWriteBarrier();
			if (parameter->getParameterType() == Parameter::OBJECT_TYPE)
				parameter->friend_setParameterType((Parameter::ParameterType)0x3d);
		}
	}
	yieldToOS();

	// heal old files.
	switch (pScriptAction->getActionType()) {
		case 0x24:
			if (pScriptAction->m_numParms == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x2d:
		case 0x2e:
			if (pScriptAction->m_numParms >= 2 && pScriptAction->m_parms[1]->getParameterType() == Parameter::INT) {
				pScriptAction->m_parms[1] = new Parameter(Parameter::AI_MOOD, pScriptAction->m_parms[1]->getInt());
			}
			break;
		case 0x55:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 1);
			}
			break;
		case 0x1a:
		case 0x1b:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[1] = new Parameter((Parameter::ParameterType)0x34, 0);
				pScriptAction->m_parms[2] = new Parameter((Parameter::ParameterType)0x34, 0);
			}
			break;
		case 0x0e:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x52:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x5d:
		case 0x94:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::SIDE);
			}
			break;
		case 0x7a:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL);
			}
			break;
		case 0x69:
		case 0x95:
		case 0xe9:
		case 0xea:
			if (pScriptAction->getNumParameters() == 0) {
				pScriptAction->m_numParms = 1;
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
			}
			break;
		case 0xb9:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			if (pScriptAction->getNumParameters() == 5) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0xd2:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::BOOLEAN, 0);
			} else if (pScriptAction->getNumParameters() == 4) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[4] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0xfe:
			if (pScriptAction->m_numParms == 1) {
				Bool flank = pScriptAction->m_parms[0]->getInt() != 0;
				delete pScriptAction->m_parms[0];
				pScriptAction->m_numParms = 0;
				if (flank)
					pScriptAction->m_actionType = 0x102;
			}
			break;
		case 0x1b2:
		case 0x1b3:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter((Parameter::ParameterType)0x34, 1);
			}
			break;
		case 0xff:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = pScriptAction->m_parms[0];
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
				pScriptAction->m_parms[0]->bfmeSet("<This Player>");
			}
			break;
		case 0x11:
		case 0x186:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL);
			} else if (pScriptAction->getNumParameters() == 5) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x12:
		case 0x13:
		case 0x78:
		case 0x79:
		case 0x154:
		case 0x15a:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL);
			}
			break;
	}
	yieldToOS();

	if (at->getNumParameters() != pScriptAction->getNumParameters()) {
		pScriptAction->m_actionType = ScriptAction::NO_OP;
		pScriptAction->m_numParms = 0;
	}
	return pScriptAction;
}
