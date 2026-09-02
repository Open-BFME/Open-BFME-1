// cl: /O2 /Ob0

class W3DShadowListNode
{
public:
	virtual ~W3DShadowListNode();

private:
	char m_pad[0x64];

public:
	W3DShadowListNode *m_next;
};

class Rva007B9930ShadowList
{
public:
	void remove(W3DShadowListNode *shadow);

private:
	W3DShadowListNode *m_head;
};

void Rva007B9930ShadowList::remove(W3DShadowListNode *shadow)
{
	W3DShadowListNode *previous = 0;
	for (W3DShadowListNode *current = m_head; current != 0;
		previous = current, current = current->m_next) {
		if (current == shadow) {
			if (previous != 0)
				previous->m_next = shadow->m_next;
			else
				m_head = shadow->m_next;

			delete shadow;
			return;
		}
	}
}
