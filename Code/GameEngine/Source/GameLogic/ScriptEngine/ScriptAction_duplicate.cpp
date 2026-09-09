// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX
// Clean C++ reconstruction of ScriptAction::duplicate at RVA 0x003560A0.
//
// The retail body is reached by the named Script copy constructor at
// 0x0035B550 through the ScriptAction::duplicate ILT.  Its 0x48 allocation,
// inline default construction of linked nodes, and the +0x44 tail are the
// BFME layout (the reference header stops at m_hasWarnings).

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
	void set(const AsciiString &other);

private:
	void *m_data;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ObjectStatusMask
{
	unsigned int m_bits[2];
};

class Parameter
{
private:
	int m_paramType;
	Bool m_initialized;
	Int m_int;
	float m_real;
	AsciiString m_string;
	Coord3D m_coord;
	ObjectStatusMask m_objectStatus;
};

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	enum ScriptActionType
	{
		NO_OP = 5
	};

	virtual ~ScriptAction();
	ScriptAction(ScriptActionType type);
	ScriptAction *duplicate(void) const;
	void setActionType(ScriptActionType type);

private:
	ScriptActionType m_actionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	Bool m_hasWarnings;
	Int m_bfmeActionTail;
};

ScriptAction::ScriptAction(ScriptActionType type) :
	m_numParms(0),
	m_nextAction(0),
	m_hasWarnings(false),
	m_bfmeActionTail(0)
{
	for (Int i = 0; i < MAX_PARMS; ++i)
		m_parms[i] = 0;
	setActionType(type);
}

ScriptAction *ScriptAction::duplicate(void) const
{
	ScriptAction *pNew = new ScriptAction(m_actionType);
	Int i;
	for (i = 0; i < m_numParms; ++i) {
		if (pNew->m_parms[i])
			*pNew->m_parms[i] = *m_parms[i];
	}

	ScriptAction *pLink = m_nextAction;
	ScriptAction *pCur = pNew;
	while (pLink) {
		pCur->m_nextAction = new ScriptAction(pLink->m_actionType);
		pCur = pCur->m_nextAction;
		for (i = 0; i < pLink->m_numParms; ++i) {
			if (pCur->m_parms[i] && pLink->m_parms[i])
				*pCur->m_parms[i] = *pLink->m_parms[i];
		}
		pLink = pLink->m_nextAction;
	}
	return pNew;
}
