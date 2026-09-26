// cl: /DNDEBUG /MD /O2 /EHsc

// Retail 0x0033C850. The sequential-script loop matches the Team pointer at
// +0x4, deletes each linked script through vtable slot zero, and clears the
// two ScriptEngine team fields at +0x1708C and +0x17094.

class Team;

class SequentialScript
{
public:
	virtual void deleteInstance(int destroy) = 0;

	Team *m_teamToExecOn;
	char m_gap[0x20];
	SequentialScript *m_nextScriptInSequence;
};

template <class T>
class RawVector
{
public:
	T *m_begin;
	T *m_end;
	T *m_capacity;
};

class ScriptEngine
{
public:
	void notifyOfTeamDestruction(Team *teamDestroyed);
	SequentialScript **cleanupSequentialScript(SequentialScript **it,
		bool cleanDanglers)
	{
		SequentialScript *seqScript = *it;
		if (!seqScript)
			return it;

		if (cleanDanglers)
		{
			SequentialScript *scriptToDelete = seqScript;
			while (seqScript)
			{
				scriptToDelete = seqScript;
				seqScript = seqScript->m_nextScriptInSequence;
				scriptToDelete->deleteInstance(1);
			}
			*it = seqScript;
		}
		return it;
	}

	void *m_vptr;
	char m_gap0[8];
	RawVector<SequentialScript *> m_sequentialScripts;
	char m_gap1[0x1708c - 0x18];
	Team *m_callingTeam;
	char m_gap2[4];
	Team *m_conditionTeam;
};

void ScriptEngine::notifyOfTeamDestruction(Team *teamDestroyed)
{
	if (!teamDestroyed)
		return;

	SequentialScript **it = m_sequentialScripts.m_begin;
	while (it != m_sequentialScripts.m_end)
	{
		SequentialScript *seqScript = *it;
		if (seqScript && seqScript->m_teamToExecOn == teamDestroyed)
			cleanupSequentialScript(it, true);
		++it;
	}

	if (m_callingTeam == teamDestroyed)
		m_callingTeam = 0;
	if (m_conditionTeam == teamDestroyed)
		m_conditionTeam = 0;
}
