// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00943DB0 allocates an eight-byte node pair, derives the +4 cell,
// and when non-null copies the source word through it before clearing the
// head word. The zero-store always runs: it sits outside the guard, so the
// guard only skips the source copy. Key lever: the null-guarded store is a
// lone `if (c != 0) c->m_head = *src;` followed by the unconditional
// `n->m_head = 0;`, not an early return. IDENTITY IS NOT RECOVERED: the
// node/owner keep address tokens.
struct Rva00943DB0Node
{
	int m_head;
	int m_next;
};

class Rva00943DB0Box
{
public:
	void *insert(int *src);
	int m_pad;
};

// stlport
#define _STLP_USE_STATIC_LIB 1
#include <memory>

void *Rva00943DB0Box::insert(int *src)
{
	Rva00943DB0Node *n = (Rva00943DB0Node *)_STL::__node_alloc<true, 0>::allocate(8);
	Rva00943DB0Node *c = (Rva00943DB0Node *)((char *)n + 4);
	if (c != 0)
		c->m_head = *src;
	n->m_head = 0;
	return n;
}
