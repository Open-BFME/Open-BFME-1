// Three independent hinted-insert wrappers previously claimed through
// the reference ScoreKeeper.cpp specialization. Evidence:
// reverse/identity_evidence/003e25f0-tree-wrappers.md
// Each forwards to the tree subobject at offset zero. The key/value semantics
// are unknown, so each address has its own opaque value and iterator types.

// 0x003E25F0 calls ILT 0x003E103 -> 0x003DE190. The complete 592-byte callee
// has the thiscall tree ABI: ECX is this; it reads iterator from original
// ESP+8 and const-value pointer from ESP+12, stores the returned node pointer
// through hidden return storage, returns that storage in EAX, and ret 12.
struct Rva003E25F0Value;
struct Rva003E25F0Iterator
{
	Rva003E25F0Iterator(const Rva003E25F0Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};
struct Rva003DE190Tree
{
	Rva003E25F0Iterator insert_unique(
		Rva003E25F0Iterator position, const Rva003E25F0Value &value);
};
struct Rva003E25F0Map
{
	Rva003DE190Tree m_tree;
	Rva003E25F0Iterator insert(
		Rva003E25F0Iterator position, const Rva003E25F0Value &value);
};
Rva003E25F0Iterator Rva003E25F0Map::insert(
	Rva003E25F0Iterator position, const Rva003E25F0Value &value)
{
	return m_tree.insert_unique(position, value);
}

// 0x00401600 calls ILT 0x00440BC -> 0x00400A90. This separate 592-byte
// callee independently exhibits the same argument/return ABI at entry and
// exit; it has its own address-qualified tree/value/iterator declarations.
struct Rva00401600Value;
struct Rva00401600Iterator
{
	Rva00401600Iterator(const Rva00401600Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};
struct Rva00400A90Tree
{
	Rva00401600Iterator insert_unique(
		Rva00401600Iterator position, const Rva00401600Value &value);
};
struct Rva00401600Map
{
	Rva00400A90Tree m_tree;
	Rva00401600Iterator insert(
		Rva00401600Iterator position, const Rva00401600Value &value);
};
Rva00401600Iterator Rva00401600Map::insert(
	Rva00401600Iterator position, const Rva00401600Value &value)
{
	return m_tree.insert_unique(position, value);
}

// 0x00587390 calls ILT 0x0041B3C -> 0x00586D60. The full 592-byte callee
// independently confirms the same physical ABI, but remains a third distinct
// declaration because no semantic value identity is established by that ABI.
struct Rva00587390Value;
struct Rva00587390Iterator
{
	Rva00587390Iterator(const Rva00587390Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};
struct Rva00586D60Tree
{
	Rva00587390Iterator insert_unique(
		Rva00587390Iterator position, const Rva00587390Value &value);
};
struct Rva00587390Map
{
	Rva00586D60Tree m_tree;
	Rva00587390Iterator insert(
		Rva00587390Iterator position, const Rva00587390Value &value);
};
Rva00587390Iterator Rva00587390Map::insert(
	Rva00587390Iterator position, const Rva00587390Value &value)
{
	return m_tree.insert_unique(position, value);
}
