// Retail 0x000EA360 forwards a hinted insertion to the distinct tree body at
// 0x000E9CC0 (via ILT 0x00007842). The complete callee disassembly is
// targets/game/reverse/identity_evidence/000ea360-tree-wrappers.md. At entry it reads the iterator argument from original
// ESP+8 and the value pointer from original ESP+12; it writes the node pointer
// through hidden return storage, returns that storage in EAX, and ret 12.
// These facts establish this ABI and the opaque reference contract without
// assigning semantic identity or width to the value type.
struct Rva000EA360Value;

struct Rva000EA360Iterator
{
	Rva000EA360Iterator(const Rva000EA360Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};

struct Rva000EA360Tree
{
	// Independently decoded contract at retail 0x000E9CC0.
	Rva000EA360Iterator insert_unique(
		Rva000EA360Iterator position, const Rva000EA360Value &value);
};

struct Rva000EA360Map
{
	Rva000EA360Tree m_tree;
	Rva000EA360Iterator insert(
		Rva000EA360Iterator position, const Rva000EA360Value &value);
};

Rva000EA360Iterator Rva000EA360Map::insert(
	Rva000EA360Iterator position, const Rva000EA360Value &value)
{
	return m_tree.insert_unique(position, value);
}

struct Rva001AB2D0Value;

struct Rva001AB2D0Iterator
{
	Rva001AB2D0Iterator(const Rva001AB2D0Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};

struct Rva001AB2D0Tree
{
	// Separate address-qualified declaration for retail 0x001AB2D0. Its raw
	// contract is the same shape, independently visible in
	// targets/game/reverse/identity_evidence/000ea360-tree-wrappers.md; keep its value type and target distinct from 0xE9CC0.
	Rva001AB2D0Iterator insert_unique(
		Rva001AB2D0Iterator position, const Rva001AB2D0Value &value);
};

struct Rva001ABFA0Map
{
	Rva001AB2D0Tree m_tree;
	Rva001AB2D0Iterator insert(
		Rva001AB2D0Iterator position, const Rva001AB2D0Value &value);
};

Rva001AB2D0Iterator Rva001ABFA0Map::insert(
	Rva001AB2D0Iterator position, const Rva001AB2D0Value &value)
{
	return m_tree.insert_unique(position, value);
}
