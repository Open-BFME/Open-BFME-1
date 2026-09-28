// ?d_00850dc0@@YAXXZ
// partial score=0.55 date=2026-09-28
// ?d_00850dc0@@YAXXZ (partial score=0.55 date=2026-09-28)
// STLport vector-dealloc gate: owner->m_node null test, bytes = count*12,
// over 0x80 through operator delete else _M_deallocate. Free-function trial
// with the native Q2NodeAlloc wrapper reaches 50B/50B size-exact but the
// member-load order diverges (retail tests owner word first, then loads
// count; ours loads node first). Needs the test-then-load order lever.

namespace Rva00850DC0
{
	class Owner
	{
	public:
		void *m_node;
		unsigned m_count;
	};
	void __cdecl operator delete(void *block);
}

class Q2NodeAlloc
{
public:
	static void deallocate(void *p, unsigned n);
};

void Rva00850DC0Release(Rva00850DC0::Owner *owner, unsigned count)
{
	void *node = owner->m_node;
	unsigned bytes;
	if (!node)
		return;
	bytes = count * 12;
	if (bytes > 0x80)
		Rva00850DC0::operator delete(node);
	else
		Q2NodeAlloc::deallocate(node, bytes);
}
