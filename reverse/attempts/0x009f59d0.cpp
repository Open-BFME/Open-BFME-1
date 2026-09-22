// ?m@T_009f59d0@@QAEXI@Z
// partial score=0.9 date=2026-09-21
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// The state constructor at 0x009F5B70 calls T_009f59d0::m with one unsigned
// argument. The body rejects a level above 11, skips when the level bit is
// already the stored mask, stores the new mask, folds the level into a
// 4-ary node count, runs the cleanup operation, replaces seventeen
// ICoord2D vectors with fresh count-sized ones, then walks the linked nodes.

#include <vector>

typedef int Int;

struct ICoord2D
{
	Int x, y;
};

struct BfmeNode912C
{
	char m_pad00[0x0c];
	BfmeNode912C *m_next;
};

class Gen_dtor_009f2600
{
public:
	void cleanup();
};

class BfmeThing912C
{
public:
	void bfmeDo912C(BfmeNode912C *node);
};

class T_009f59d0
{
public:
	void m(unsigned level);

	float m_values[6];
	_STL::vector<ICoord2D> m_items[17];
	BfmeNode912C *m_head;
	float m_scale;
	int m_flags;
	void *m_tail;
};

void T_009f59d0::m(unsigned level)
{
	if (level > 11)
		return;

	int mask = 1 << level;
	if (mask == m_flags)
		return;
	m_flags = mask;

	unsigned count = 1;
	while (level != 0) {
		--level;
		count = count * 4 + 1;
	}

	((Gen_dtor_009f2600 *)this)->cleanup();

	for (int i = 0; i < 17; ++i)
		m_items[i] = _STL::vector<ICoord2D>(count);

	BfmeNode912C *node = m_head;
	while (node != 0) {
		((BfmeThing912C *)this)->bfmeDo912C(node);
		node = node->m_next;
	}
}
