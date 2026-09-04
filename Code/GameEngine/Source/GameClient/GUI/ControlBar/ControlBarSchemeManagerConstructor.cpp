// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

void *allocateControlBarSchemeListNode(unsigned int bytes); // retail 0x0082E540
void __cdecl deallocateControlBarSchemeListNode(void *block, unsigned int bytes); // retail 0x0082E5F0

class ControlBarScheme;

struct ControlBarSchemeListNode
{
	ControlBarSchemeListNode *m_next;
	ControlBarSchemeListNode *m_previous;
	ControlBarScheme *m_scheme;
};

class ControlBarSchemeList
{
public:
	ControlBarSchemeList(void)
	{
		m_sentinel = 0;

		ControlBarSchemeListNode *sentinel =
			(ControlBarSchemeListNode *)allocateControlBarSchemeListNode(sizeof(ControlBarSchemeListNode));

		sentinel->m_next = sentinel;
		sentinel->m_previous = sentinel;
		m_sentinel = sentinel;
	}

	~ControlBarSchemeList(void);

	void clear(void)
	{
		ControlBarSchemeListNode *node = m_sentinel->m_next;

		while (node != m_sentinel)
		{
			ControlBarSchemeListNode *current = node;
			node = node->m_next;
			deallocateControlBarSchemeListNode(current, sizeof(ControlBarSchemeListNode));
		}

		m_sentinel->m_next = m_sentinel;
		m_sentinel->m_previous = m_sentinel;
	}

private:
	ControlBarSchemeListNode *m_sentinel;
};

class ControlBarSchemeManager
{
public:
	ControlBarSchemeManager(void);

private:
	ControlBarScheme *m_currentScheme;
	float m_multiplierX;
	float m_multiplierY;
	ControlBarSchemeList m_schemeList;
};

ControlBarSchemeManager::ControlBarSchemeManager(void)
{
	m_currentScheme = 0;
	m_schemeList.clear();
	m_multiplierY = 1.0f;
	m_multiplierX = 1.0f;
}
