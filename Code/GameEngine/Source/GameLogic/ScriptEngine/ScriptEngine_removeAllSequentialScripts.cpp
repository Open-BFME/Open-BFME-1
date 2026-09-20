// cl: /DNDEBUG /MD /O2 /EHsc

extern "C" __declspec(dllimport) void * __cdecl memmove(
	void *destination, const void *source, unsigned int bytes);

typedef int ObjectID;

class Object
{
private:
	char m_gap[0x74];
	ObjectID m_id;

public:
	ObjectID getID() const { return m_id; }
};

class SequentialScript
{
public:
	virtual void deleteInstance(int destroy) = 0;

private:
	char m_gap0[4];
	ObjectID m_objectID;
	char m_gap1[0x1c];
	SequentialScript *m_nextScriptInSequence;

public:
	SequentialScript *nextScriptInSequence() const
	{
		return m_nextScriptInSequence;
	}

	ObjectID objectID() const
	{
		return m_objectID;
	}
};

__forceinline void cleanupSequentialScript(SequentialScript **it)
{
	SequentialScript *seqScript = *it;
	if (!seqScript)
		return;

	while (seqScript)
	{
		SequentialScript *scriptToDelete = seqScript;
		seqScript = seqScript->nextScriptInSequence();
		scriptToDelete->deleteInstance(1);
	}
	*it = seqScript;
}

template <class T>
class RawVector
{
public:
	T *m_begin;
	T *m_end;
	T *m_capacity;

	T *begin() { return m_begin; }
	T *end() { return m_end; }
};

class ScriptEngine
{
private:
	void *m_vptr;
	char m_gap0[8];
	RawVector<SequentialScript *> m_sequentialScripts;

public:
	void removeAllSequentialScripts(Object *obj);
};

// ?removeAllSequentialScripts@ScriptEngine@@QAEXPAVObject@@@Z
void ScriptEngine::removeAllSequentialScripts(Object *obj)
{
	if (!obj)
		return;

	ObjectID id = obj->getID();
	SequentialScript **it;
	for (it = m_sequentialScripts.begin(); it != m_sequentialScripts.end();)
	{
		SequentialScript **next = it + 1;
		SequentialScript *seqScript = *it;
		if (!seqScript)
		{
			if (next != m_sequentialScripts.end())
				memmove(it, next,
					(unsigned int)((char *)m_sequentialScripts.end() -
						(char *)next));
			--m_sequentialScripts.m_end;
			continue;
		}
		if (seqScript->objectID() != id)
		{
			++it;
			continue;
		}

		cleanupSequentialScript(it);
		if (next != m_sequentialScripts.end())
			memmove(it, next,
				(unsigned int)((char *)m_sequentialScripts.end() -
					(char *)next));
		--m_sequentialScripts.m_end;
	}
}
