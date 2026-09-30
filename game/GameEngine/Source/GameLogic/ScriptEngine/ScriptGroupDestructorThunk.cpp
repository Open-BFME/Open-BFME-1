// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the retail pooled-list destructor.

extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")

class ScriptPoolObject
{
public:
	void deleteInstance(int destroy);
};

class ScriptGroupPoolObject
{
public:
	void deleteInstance(int destroy);
};

template <class T>
class PoolAllocation
{
public:
	~PoolAllocation()
	{
		if (m_object)
			m_object->deleteInstance(1);
	}

private:
	T *m_object;
};

class __declspec(novtable) ScriptGroup
{
protected:
	virtual ~ScriptGroup();

private:
	PoolAllocation<ScriptPoolObject> *m_firstScript;
	PoolAllocation<ScriptGroupPoolObject> *m_nextGroup;
};

// ??1ScriptGroup@@MAE@XZ
ScriptGroup::~ScriptGroup()
{
	*(volatile unsigned int *)this = (unsigned int)bfmeVftSnapshot;
	PoolAllocation<ScriptGroupPoolObject> *nextGroup =
		*(PoolAllocation<ScriptGroupPoolObject> * volatile *)&m_nextGroup;
	delete nextGroup;
	PoolAllocation<ScriptPoolObject> *firstScript =
		*(PoolAllocation<ScriptPoolObject> * volatile *)&m_firstScript;
	delete firstScript;
}
