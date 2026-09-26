// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Q1Forwardee0000871A::handle, retail 0x00102610, 37 bytes.
//
// An intrusive unlink and a delete, on the node the argument names -- `this' is
// never read. The node carries its successor at +0x04 and, at +0x08, a pointer
// to the field that points AT it, so the unlink is one store through that
// pointer plus a back-pointer fixup on the successor.
//
// The delete is a tail jump: the deleting destructor's flag is written over the
// argument slot and the vtable slot 0 call becomes the return.

typedef int Int;

class BfmeIntrusiveNode
{
public:
	virtual ~BfmeIntrusiveNode();

	BfmeIntrusiveNode *m_next;				// +0x04
	BfmeIntrusiveNode **m_prevNext;				// +0x08
};

class Q1Forwardee0000871A
{
public:
	void handle(Int node);
};

void Q1Forwardee0000871A::handle(Int node)
{
	BfmeIntrusiveNode *n = (BfmeIntrusiveNode *)node;

	*n->m_prevNext = n->m_next;
	if (n->m_next)
		n->m_next->m_prevNext = n->m_prevNext;

	delete n;
}
