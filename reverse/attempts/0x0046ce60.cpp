// ?apply@BfmeLevelActionRegistry@@QAEXPBDPAX@Z
// partial score=0.96 date=2026-09-04
// ?apply@BfmeLevelActionRegistry@@QAEXPBDPAX@Z
// partial score=0.96 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /EHsc

#include <exception>

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

class BfmeErr1042 : public std::exception
{
};
const char *__cdecl bfmeSkipLevelPrefix(const char *path);

class BfmeLevelAction
{
public:
	virtual void unused();
	virtual void apply(void *value, void *context, int enabled);
};

struct BfmeLevelActionNode
{
	void *m_next;
	void *m_nameData;
	BfmeLevelAction *m_action;
	void *m_value;
};

class BfmeLevelActionMap
{
public:
	BfmeLevelActionNode *find(const AsciiString &name) const;
};

class BfmeLevelActionRegistry
{
public:
	void apply(const char *name, void *context);

private:
	unsigned char m_unmodelled000[0x1C];
	BfmeLevelActionMap m_actions;
};

void BfmeLevelActionRegistry::apply(const char *name, void *context)
{
	BfmeLevelActionMap *volatile retainedActions;
	BfmeLevelActionNode *node;
	{
		AsciiString key(name);
		node = m_actions.find(key);
	}

	if (node == 0)
	{
		AsciiString key(bfmeSkipLevelPrefix(name));
		node = m_actions.find(key);
		retainedActions = &m_actions;
	}

	if (node != 0)
	{
		BfmeLevelAction *action = node->m_action;
		void *value = node->m_value;
		if (action == 0)
			throw BfmeErr1042();
		action->apply(value, context, 1);
	}
}
