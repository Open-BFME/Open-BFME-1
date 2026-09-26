// cl: /O2 /Ob1 /DNDEBUG /MD
// BFME retail 0x001C1F70: walk the linked owner chain and dispatch its tail.

extern void j_00048630();

class BfmeChainNode001C1F70
{
public:
	void dispatch(void *context, void *unused);

private:
	unsigned char m_pad000[0x1f8];
	BfmeChainNode001C1F70 *m_dispatch;
	unsigned char m_pad1fc[0x18];
	BfmeChainNode001C1F70 *m_next;
};

typedef void (BfmeChainNode001C1F70::*BfmeChainDispatch)(void *, void *);

union BfmeChainCall
{
	void (*freeFunction)();
	BfmeChainDispatch memberFunction;
};

void BfmeChainNode001C1F70::dispatch(void *context, void *unused)
{
	BfmeChainNode001C1F70 *node = this;
	while (node->m_next != 0)
		node = node->m_next;

	BfmeChainCall call;
	call.freeFunction = j_00048630;
	if (node->m_dispatch != 0)
		(node->m_dispatch->*call.memberFunction)(context, unused);
}
