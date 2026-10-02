// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern void (__cdecl *g_bfmeFreeDWF)(void *);

class BfmeNode95200
{
public:
	void *m_key;
	BfmeNode95200 *m_next;
};

class Gen_00895200
{
public:
	void remove(void *key);

private:
	BfmeNode95200 *m_head;
};

void Gen_00895200::remove(void *key)
{
	BfmeNode95200 *node = m_head;
	if (m_head->m_key == key && m_head)
	{
		BfmeNode95200 *next = m_head->m_next;
		g_bfmeFreeDWF(m_head);
		m_head = next;
		return;
	}

	if (node)
	{
		do
		{
			if (node->m_next)
			{
				if (node->m_next->m_key == key)
				{
					BfmeNode95200 *removed = node->m_next;
					if (removed)
						node->m_next = removed->m_next;
					g_bfmeFreeDWF(removed);
					return;
				}
			}
			node = node->m_next;
		}
		while (node);
	}
}
