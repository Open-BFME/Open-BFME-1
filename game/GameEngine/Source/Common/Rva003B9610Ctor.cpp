// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: constructor that zeros a 4-byte string and a dword, then
// inlines a 0x14-byte red-black header allocate. Retail 0x003B9610, 99 bytes.
// The tree is a member so its push 0x14 sits after the dword store; the
// allocator is a direct cdecl so the call is E8 not FF15.

void *bfmeAllocNode(unsigned int bytes);

template <typename T>
class StringBase
{
	friend class Rva003B9610Str;

private:
	StringBase() : m_data(0) {}
	~StringBase();
	int *m_data;
};

class Rva003B9610Str : private StringBase<char>
{
public:
	Rva003B9610Str() : StringBase<char>() {}
	~Rva003B9610Str() {}
};

struct Rva003B9610Node
{
	char color;
	int *parent;
	Rva003B9610Node *left;
	Rva003B9610Node *right;
};

struct Rva003B9610TreeBase
{
	Rva003B9610Node *header;
	Rva003B9610TreeBase()
	{
		header = 0;
		header = (Rva003B9610Node *)bfmeAllocNode(0x14);
	}
};

struct Rva003B9610Tree : Rva003B9610TreeBase
{
	int count;
	Rva003B9610Tree()
		: count(0)
	{
		header->color = 0;
		header->parent = 0;
		header->left = header;
		header->right = header;
	}
};

class Rva003B9610
{
public:
	Rva003B9610();

private:
	Rva003B9610Str m_a;
	int m_at04;
	Rva003B9610Tree m_tree;
};

Rva003B9610::Rva003B9610()
	: m_at04(0)
{
}
