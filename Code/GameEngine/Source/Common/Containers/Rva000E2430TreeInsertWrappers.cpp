// Three hinted-insert wrappers whose old PlayerTemplate.cpp specializations
// named value semantics contradicted the routed retail tree bodies. The
// payload type stays incomplete; each address gets separate tree and iterator
// types because the physical ABI alone does not establish value identity.

// 0x000E2430 calls ILT 0x00030E13 -> 0x000E1C50. This complete 592-byte
// body has ECX=this, iterator at entry ESP+8 and const value reference at
// entry ESP+12. It stores the node pointer through hidden return storage,
// returns that storage in EAX, and all 15 RET paths use ret 12. Direct
// conditional branches remain inside the 592-byte extent; the furthest RET
// ends exactly at its boundary.
struct Rva000E2430Value;
struct Rva000E2430Iterator
{
	Rva000E2430Iterator(const Rva000E2430Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};
struct Rva000E1C50Tree
{
	Rva000E2430Iterator insert_unique(
		Rva000E2430Iterator position, const Rva000E2430Value &value);
};
struct Rva000E2430Map
{
	Rva000E1C50Tree m_tree;
	Rva000E2430Iterator insert(
		Rva000E2430Iterator position, const Rva000E2430Value &value);
};
Rva000E2430Iterator Rva000E2430Map::insert(
	Rva000E2430Iterator position, const Rva000E2430Value &value)
{
	return m_tree.insert_unique(position, value);
}

// 0x00401630 calls ILT 0x00040F6B -> 0x00400D80. Its own complete
// 592-byte body independently has ECX=this, iterator at entry ESP+8 and
// const value reference at entry ESP+12. Every branch remains in the body;
// 15 RET paths store the returned node through hidden return storage, return
// that storage in EAX, and clean 12 argument bytes.
struct Rva00401630Value;
struct Rva00401630Iterator
{
	Rva00401630Iterator(const Rva00401630Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};
struct Rva00400D80Tree
{
	Rva00401630Iterator insert_unique(
		Rva00401630Iterator position, const Rva00401630Value &value);
};
struct Rva00401630Map
{
	Rva00400D80Tree m_tree;
	Rva00401630Iterator insert(
		Rva00401630Iterator position, const Rva00401630Value &value);
};
Rva00401630Iterator Rva00401630Map::insert(
	Rva00401630Iterator position, const Rva00401630Value &value)
{
	return m_tree.insert_unique(position, value);
}

// 0x004E5D30 calls ILT 0x000186D3 -> 0x004E5130. Its own complete
// 592-byte body independently has ECX=this, iterator at entry ESP+8 and
// const value reference at entry ESP+12. Every branch remains in the body;
// 15 RET paths store the returned node through hidden return storage, return
// that storage in EAX, and clean 12 argument bytes.
struct Rva004E5D30Value;
struct Rva004E5D30Iterator
{
	Rva004E5D30Iterator(const Rva004E5D30Iterator &that) : m_node(that.m_node) {}
	void *m_node;
};
struct Rva004E5130Tree
{
	Rva004E5D30Iterator insert_unique(
		Rva004E5D30Iterator position, const Rva004E5D30Value &value);
};
struct Rva004E5D30Map
{
	Rva004E5130Tree m_tree;
	Rva004E5D30Iterator insert(
		Rva004E5D30Iterator position, const Rva004E5D30Value &value);
};
Rva004E5D30Iterator Rva004E5D30Map::insert(
	Rva004E5D30Iterator position, const Rva004E5D30Value &value)
{
	return m_tree.insert_unique(position, value);
}
