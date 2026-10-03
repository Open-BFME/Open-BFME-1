// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

struct Rva00646290Node
{
	char m_pad[0x14];
	void *m_value;
	int m_state;
};

struct Rva00646290Iterator
{
	Rva00646290Node *m_node;
};

class Rva00646290Tree
{
public:
	Rva00646290Node *m_head;
};

// The retail callee is reached through the incremental-link thunk at ILT
// 0x0001A55A (?j_0001a55a@@YAXXZ, whose body is `b_00645160`), which jumps to
// 0x00645160. That body is a __thiscall tree find whose iterator comes back
// through MSVC's hidden return pointer: ecx = tree, [esp+4] = out slot,
// [esp+8] = &key, and the callee pops both (ret 8 at 0x006451A4). Spelling the
// return as an explicit out parameter keeps that machine shape byte for byte,
// while a C++ return value would make the same call resolve to an undefined
// member `find` and leave this object unlinkable.
extern void j_0001a55a();
typedef void (Rva00646290Tree::*Rva00646290FindCall)(Rva00646290Iterator *out, const int &key);

class Rva00646290Owner
{
public:
	void *lookup00646290(int key);
	char m_pad[0x20C];
	Rva00646290Tree m_tree;
};

void *Rva00646290Owner::lookup00646290(int key)
{
	union { void (*raw)(); Rva00646290FindCall member; } call;
	call.raw = j_0001a55a;

	Rva00646290Iterator it;
	(m_tree.*call.member)(&it, key);

	if (it.m_node == m_tree.m_head)
		return 0;

	Rva00646290Node *value = (Rva00646290Node *)it.m_node->m_value;
	if (value && value->m_state == 0)
		return 0;
	return value;
}
