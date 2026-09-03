// ?any@Rva001E4160List@@QAE_NPAX0@Z
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Circular sentinel list at +0x538; each node stores a handler at +8 whose
// virtual slot 1 is tried with (arg2, arg1). First true wins. Named callers:
// BfmeThingACF::checkAndRun and BfmeC1009::bfmeGo1009C.

class Rva001E4160Handler
{
public:
	virtual void _slot0(void) = 0;
	virtual bool accept(void *second, void *first) = 0;
};

struct Rva001E4160Node
{
	Rva001E4160Node *next;
	unsigned char m_unreconstructed_04[4];
	Rva001E4160Handler *handler;
};

class Rva001E4160List
{
public:
	bool any(void *first, void *second);

private:
	unsigned char m_unreconstructed_00[0x538];
	Rva001E4160Node *m_sentinel;
};

bool Rva001E4160List::any(void *first, void *second)
{
	void *a = first;
	if (!a)
		return false;

	Rva001E4160Node *sent = m_sentinel;
	Rva001E4160Node *node = sent->next;
	if (node == sent)
		return false;

	void *b = second;
	do
	{
		if (node->handler->accept(b, a))
			return true;
		node = node->next;
	}
	while (node != sent);

	return false;
}
