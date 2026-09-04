// ??1ScriptList@@UAE@XZ
// partial score=0.93 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// readable body of ??1ScriptList@@UAE@XZ: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp

class Gen_0035B8A0
{
public:
	~Gen_0035B8A0();

private:
	unsigned char m_data[0x20];
};

class Gen_0035B960
{
public:
	~Gen_0035B960();

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
class ScriptListInterface
{
public:
	virtual void reset();
	~ScriptListInterface() {}
};

class ScriptListBase
{
public:
    ~ScriptListBase();

private:
	ScriptPoolObject *m_firstGroup;
	ScriptGroupPoolObject *m_firstScript;
};

ScriptListBase::~ScriptListBase()
{
	ScriptGroupPoolObject *script = m_firstScript;
	if (script)
	{
		if (script->next)
			script->next->deleteInstance(1);
		operator delete(script);
	}

	ScriptPoolObject *group = m_firstGroup;
	if (group)
	{
		if (group->next)
			group->next->deleteInstance(1);
		operator delete(group);
	}
}

class ScriptList : public ScriptListInterface, public ScriptListBase
{
public:
	~ScriptList();

private:
	Gen_0035B8A0 m_first;
	Gen_0035B960 m_second;
};

// ??1ScriptList@@QAE@XZ
ScriptList::~ScriptList()
{
}
