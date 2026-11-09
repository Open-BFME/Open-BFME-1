// Retail 0x005876D0 disposal; the separate 0x00605820 tree eraser lives in
// GameClient/Rva00605820TreeErase.cpp.
//
// Each walks a null-terminated chain: it hands a field of the node to a member
// of its owner, saves the successor, destroys the value the node carries, and
// frees the node with its own size.
//
// The successor is read after the notify and before the destructor, because
// both of those can change memory and the walk has to survive them; that read
// is what keeps the node itself in the callee-saved register across all three
// calls. This body frees a 0x50-byte node with the value at +0x10.

namespace _STL
{
// retail 0x0082E5F0 is STLport's private node-pool entry; reach it under its real name.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }
}
static inline void bfmeDeallocate(void *block, unsigned int bytes) { _STL::nodePoolDeallocate(block, bytes); }

class BfmeChainValue
{
public:
	~BfmeChainValue(void);					// retail 0x000402BE

private:
	char m_bfmeBytes[0x40];
};

struct BfmeChainNode
{
	int m_bfmeHead[2];					// +0x00
	BfmeChainNode *m_left;				// +0x08
	void *m_right;					// +0x0C
	BfmeChainValue m_bfmeValue;				// +0x10
};

class Gen_005876D0
{
public:
	void bfmeDisposeChain(BfmeChainNode *node);
	void bfmeNotify(void *field);				// retail 0x00037353
};

// ?bfmeDisposeChain@Gen_005876D0@@QAEXPAUBfmeChainNode@@@Z
void Gen_005876D0::bfmeDisposeChain(BfmeChainNode *node)
{
	while (node)
	{
		bfmeNotify(node->m_right);

		BfmeChainNode *next = node->m_left;

		node->m_bfmeValue.~BfmeChainValue();

		bfmeDeallocate(node, sizeof(BfmeChainNode));

		node = next;
	}
}
