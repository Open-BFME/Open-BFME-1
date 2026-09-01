// ??1ScriptList@@QAE@XZ
// partial score=0.91 date=2026-08-31
// Clean reconstruction of the ScriptList member teardown at 0x0035BC20.

extern "C" void __cdecl ScriptListFreeNode(void *node);

class ScriptListSnapshotHead
{
public:
	virtual ~ScriptListSnapshotHead() {}
};

class ScriptListGroupNode
{
public:
	ScriptListGroupNode *next;
	void deleteInstance(int deleting);
};

class ScriptListScriptNode
{
public:
	ScriptListScriptNode *next;
	void deleteInstance(int deleting);
};

class ScriptListGroupOwner
{
public:
	~ScriptListGroupOwner()
	{
		ScriptListGroupNode *node = head;
		if (node != 0) {
			if (node->next != 0) {
				node->next->deleteInstance(1);
			}
			ScriptListFreeNode(node);
		}
	}

private:
	ScriptListGroupNode *head;
};

class ScriptListScriptOwner
{
public:
	~ScriptListScriptOwner()
	{
		ScriptListScriptNode *node = head;
		if (node != 0) {
			if (node->next != 0) {
				node->next->deleteInstance(1);
			}
			ScriptListFreeNode(node);
		}
	}

private:
	ScriptListScriptNode *head;
};

class ScriptListInlineGroup
{
public:
	~ScriptListInlineGroup();

private:
	unsigned char data[0x20];
};

class ScriptListBase
{
public:
	__forceinline ~ScriptListBase() {}

private:
	ScriptListSnapshotHead snapshot;
	ScriptListGroupOwner firstGroup;
	ScriptListScriptOwner firstScript;
};

class ScriptList : public ScriptListBase
{
public:
	~ScriptList();

private:
	ScriptListInlineGroup groupA;
	ScriptListInlineGroup groupB;
};

ScriptList::~ScriptList()
{
	*(volatile unsigned int *)this = 0x010E8CA8;
}
