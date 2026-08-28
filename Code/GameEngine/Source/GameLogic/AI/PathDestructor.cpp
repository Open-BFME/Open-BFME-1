// BFME Path::~Path releases its singly linked node chain. novtable preserves
// the protected virtual destructor ABI without emitting a vftable restore in
// this focused translation unit.

class PathNode
{
public:
	PathNode *getNext(void) { return m_next; }
	void deleteInstance(void) { delete this; }

private:
	PathNode *m_next;
};

class __declspec(novtable) Path
{
protected:
	virtual ~Path(void);

private:
	PathNode *m_path;
};

// ??1Path@@MAE@XZ
Path::~Path(void)
{
	PathNode *node, *nextNode;

	for (node = m_path; node; node = nextNode)
	{
		nextNode = node->getNext();
		node->deleteInstance();
	}
}
