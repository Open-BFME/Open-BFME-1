// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME: guarded pointer-key lookup wrapper at retail 0x00769260.

struct Rva00769260Node
{
	char m_pad00[0x14];
	char m_result[0x30];
	int m_value;
};

struct Rva00769260Iterator
{
	Rva00769260Node *m_node;
};

// ILT 0x0004B66E is the pointer-key tree find called by the wrapper.
extern void j_0004b66e();

class Rva00769260Tree
{
public:
	Rva00769260Node *m_end;
};

class Rva00769260Owner
{
public:
	void *lookup(void *key, int *value);

private:
	char m_pad00[0x70];
	Rva00769260Tree m_tree;
	char m_pad74[0xAC - 0x74];
	unsigned char m_flags;
};

void *Rva00769260Owner::lookup(void *key, int *value)
{
	if ((m_flags & 1) != 0 && key != 0)
	{
		typedef Rva00769260Iterator *(Rva00769260Tree::*Find)(Rva00769260Iterator *, void *const &);
		union { void (*fn)(); Find call; } find = { j_0004b66e };
		Rva00769260Iterator found;
		(m_tree.*find.call)(&found, key);
		if (found.m_node != m_tree.m_end)
		{
			if (value != 0)
				*value = found.m_node->m_value;
			return found.m_node->m_result;
		}
	}
	if (value != 0)
		*value = 0;
	return 0;
}
