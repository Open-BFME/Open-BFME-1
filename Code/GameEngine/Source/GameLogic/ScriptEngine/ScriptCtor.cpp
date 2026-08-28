// readable body of ??0Script@@QAE@XZ: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
// BFME's Script predates the additional Zero Hour action-comment field.  Keep
// the retail layout local so the later reference header cannot shift members.

class Xfer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_text( 0 ) {}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();

protected:
	virtual void crc( Xfer *xfer ) = 0;
	virtual void xfer( Xfer *xfer ) = 0;
	virtual void loadPostProcess() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Script : public Snapshot
{
public:
	Script();
	virtual ~Script();
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess();

private:
	AsciiString m_scriptName;
	AsciiString m_comment;
	AsciiString m_conditionComment;
	int m_delayEvaluationSeconds;
	bool m_isActive;
	bool m_isOneShot;
	bool m_easy;
	bool m_isSubroutine;
	bool m_normal;
	bool m_hard;
	bool m_bfmeFlag;
	void *m_condition;
	void *m_action;
	void *m_actionFalse;
	Script *m_nextScript;
	bool m_hasWarnings;
	AsciiString m_conditionTeamName;
	float m_conditionTime;
	float m_curTime;
	int m_conditionExecutedCount;
};

Script::Script() :
	m_delayEvaluationSeconds( 0 ),
	m_isActive( true ),
	m_isOneShot( true ),
	m_easy( true ),
	m_isSubroutine( false ),
	m_normal( true ),
	m_hard( true ),
	m_bfmeFlag( true ),
	m_condition( 0 ),
	m_action( 0 ),
	m_actionFalse( 0 ),
	m_nextScript( 0 ),
	m_hasWarnings( false ),
	m_conditionTime( 0.0f ),
	m_curTime( 0.0f ),
	m_conditionExecutedCount( 0 )
{
}
