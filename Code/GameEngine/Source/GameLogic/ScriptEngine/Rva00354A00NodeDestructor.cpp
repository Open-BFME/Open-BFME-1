// cl: /DNDEBUG /MD /EHsc
// ScriptGroup destructor inlined after a 4-byte next-link prefix: vtable at
// +4, next-group at +0xC, first-script at +8. Same PoolAllocation delete
// shape as ??1ScriptGroup@@MAE@XZ at 0x00352950.

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

class Rva00354A00Node
{
public:
	~Rva00354A00Node();

private:
	Rva00354A00Node *m_next;
	unsigned int m_vftable;
	PoolAllocation<ScriptPoolObject> *m_firstScript;
	PoolAllocation<ScriptGroupPoolObject> *m_nextGroup;
};

// ??1Rva00354A00Node@@QAE@XZ
Rva00354A00Node::~Rva00354A00Node()
{
	*(volatile unsigned int *)&m_vftable = 0x01073744;
	PoolAllocation<ScriptGroupPoolObject> *nextGroup =
		*(PoolAllocation<ScriptGroupPoolObject> * volatile *)&m_nextGroup;
	delete nextGroup;
	PoolAllocation<ScriptPoolObject> *firstScript =
		*(PoolAllocation<ScriptPoolObject> * volatile *)&m_firstScript;
	delete firstScript;
}
