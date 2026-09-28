// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x009455B0 links a node into the +0xBC/+0xC0 list: no-op when the
// link slot is already set, otherwise it keys on the node word, stores the
// key at this+0xC0, links the node and back-points the node at this.
// Neighbours: dx8renderer.cpp MeshModel/RenderObj. Pairs with the 0x009455F0
// unlink below. IDENTITY IS NOT RECOVERED: the owner keeps its address
// token.
class Rva009455B0Box
{
public:
	void link(void *node);
	char m_pad[0xBC];
	void *m_link;
	void *m_tail;
};
void Rva009455B0Box::link(void *node)
{
	if (m_link != 0)
		return;
	void *key = *(void **)node;
	*(void **)((char *)this + 0xC0) = key;
	m_link = node;
	*(void **)node = this;
	void *t = *(void **)((char *)this + 0xC0);
	if (t == 0)
		return;
	*(void **)((char *)t + 0xBC) = (char *)this + 0xC0;
}

class Rva009455F0Box
{
public:
	void unlink();
	char m_pad[0xBC];
	void *m_link;
	void *m_tail;
};
// Link-reload spelling (m_link re-read for the back-pointer store) is what
// emits retail's second mov-edx,[ecx+0xBC] load. Pairs with the 0x009455B0
// link above.
void Rva009455F0Box::unlink()
{
	void *link = m_link;
	if (link != 0)
	{
		void *tail = m_tail;
		*(void **)link = tail;
		void *t2 = m_tail;
		if (t2 != 0)
		{
			void *l2 = m_link;
			*(void **)((char *)t2 + 0xBC) = l2;
		}
		m_link = 0;
	}
}
