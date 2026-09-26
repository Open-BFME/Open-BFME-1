// cl: /DNDEBUG /MD /EHsc
// Retail 0x0029BDE0 (98 B). Walks the list at this+0xC (next link at +0x40)
// for up to flag ? 5 : 1 entries of type 1 or 3 whose template is equivalent
// to the argument, handing each match's payload to virtual slot +0x20 and
// restarting from the head. The comparison is ThingTemplate::isEquivalentTo
// (body 0x0013FE10), called through ILT 0x0003E80B.
//
// The key is copied into a local before the call. Passing node->m_key
// directly compiles to the same mov/push, but the payload load and the vtable
// load after the call then come out in EAX/EDX where retail has ECX/EAX: MSVC
// 7.1 hands out scratch registers round-robin, and only the copied form
// takes a step for the pushed key (docs/shape_levers.md, "Scratch registers
// rotate").

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tt) const;
};

struct Gen0029BDE0Node
{
	void *m_unused0;
	int m_type;
	const ThingTemplate *m_key;
	void *m_unused0C;
	void *m_payload;
	unsigned char m_pad14[0x2c];
	Gen0029BDE0Node *m_next;
};

class Gen0029BDE0
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void applyPayload(void *payload);

	void walk(const ThingTemplate *target, bool flag);

private:
	void *m_unused4;
	void *m_unused8;
	Gen0029BDE0Node *m_head;
};

void Gen0029BDE0::walk(const ThingTemplate *target, bool flag)
{
	Gen0029BDE0Node *node = m_head;
	int remaining = flag ? 5 : 1;
	if (!remaining)
		return;
	do
	{
		if (!node)
			return;
		if (node->m_type == 1 || node->m_type == 3)
		{
			const ThingTemplate *key = node->m_key;
			if (target->isEquivalentTo(key))
			{
				applyPayload(node->m_payload);
				node = m_head;
				remaining--;
				continue;
			}
		}
		node = node->m_next;
	} while (remaining);
}
