// ??1ScriptList@@QAE@XZ
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// readable body of ??1ScriptList@@QAE@XZ: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp

class ScriptGroup
{
public:
	~ScriptGroup();

private:
	unsigned char m_data[0x20];
};

class ScriptGroupPoolObject
{
public:
	ScriptGroupPoolObject *next;
	void deleteInstance(int destroy);
};

class ScriptPoolObject
{
public:
	ScriptPoolObject *next;
	void deleteInstance(int destroy);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptListBase
{
public:
	virtual ~ScriptListBase();

private:
	ScriptGroupPoolObject *m_firstGroup;
	ScriptPoolObject *m_firstScript;
};

ScriptListBase::~ScriptListBase()
{
	ScriptPoolObject *script = m_firstScript;
	if (script)
	{
		if (script->next)
			script->next->deleteInstance(1);
		operator delete(script);
	}

	ScriptGroupPoolObject *group = m_firstGroup;
	if (group)
	{
		if (group->next)
			group->next->deleteInstance(1);
		operator delete(group);
	}
}

class ScriptList : public ScriptListBase
{
public:
	virtual ~ScriptList();

private:
	ScriptGroup m_first;
	ScriptGroup m_second;
};

// ??1ScriptList@@QAE@XZ
ScriptList::~ScriptList()
{
}
