// ?findLocomotorTemplateByName@@YGPAXABVAsciiString@@@Z
// partial score=0.42 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x001B70E0: intern an AsciiString through TheNameKeyGenerator then
// look the key up in TheLocomotorStore's name-key tree.

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? m_data + 8 : (const char *)0x0107388B;
	}

private:
	char *m_data;
};

class NameKeyGenerator
{
public:
	unsigned nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct LocoNode
{
	char m_pad[0x14];
	void *m_value;
};

struct LocoIter
{
	LocoNode *m_node;
	LocoIter(const LocoIter &other) : m_node(other.m_node) {}
};

class LocoTree
{
public:
	LocoIter find(const unsigned &key);

	LocoNode *m_end;
};

class LocomotorStore
{
public:
	char m_pad[8];
	LocoTree m_tree;
};

#define TheLocomotorStore (*(LocomotorStore **)0x012EF504)

void *__stdcall findLocomotorTemplateByName(const AsciiString &name)
{
	unsigned key = TheNameKeyGenerator->nameToKey(name.str());
	if (key != 0)
		goto found;
zero:
	return 0;
found:
	LocoTree *tree = &TheLocomotorStore->m_tree;
	LocoIter it = tree->find(key);
	if (it.m_node == tree->m_end)
		goto zero;
	return it.m_node->m_value;
}
