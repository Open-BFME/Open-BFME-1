// Clean reconstruction of the eight-child state adjuster at retail RVA
// 0x003CBB70.  The owning type is retained as an address-derived view because
// the retail body has no named caller or independently named vtable.

typedef signed char SByte;

struct Rva003CBB70Child
{
	char m_pad[0x38];
	SByte m_state;
};

class Rva003CBB70
{
public:
	void adjustChildren(bool enabled);

private:
	char m_pad[0x10];
	Rva003CBB70Child *m_child0;
	Rva003CBB70Child *m_child1;
	Rva003CBB70Child *m_child2;
	Rva003CBB70Child *m_child3;
	Rva003CBB70Child *m_child4;
	Rva003CBB70Child *m_child5;
	Rva003CBB70Child *m_child6;
	Rva003CBB70Child *m_child7;
	char m_pad30[8];
	SByte m_state;
};

void Rva003CBB70::adjustChildren(bool enabled)
{
	SByte delta = enabled ? 1 : -1;
	if (m_child0)
		m_child0->m_state += delta;
	if (m_child1)
		m_child1->m_state += delta;
	if (m_child2)
		m_child2->m_state += delta;
	if (m_child3)
		m_child3->m_state += delta;
	if (m_child4)
		m_child4->m_state += delta;
	if (m_child5)
		m_child5->m_state += delta;
	if (m_child6)
		m_child6->m_state += delta;
	if (m_child7)
		m_child7->m_state += delta;
	m_state += delta;
}
