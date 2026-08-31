// ?d_0010eca0@@YAXXZ
// partial score=0.86 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc

inline void *operator new(unsigned int, void *place) { return place; }

namespace _STL
{
	class __new_alloc
	{
	public:
		static void *allocate(unsigned size);
	};
}

struct Rva0010ECA0Value
{
	Rva0010ECA0Value(const Rva0010ECA0Value &other)
		: first(other.first), second(other.second) { }

	unsigned first;
	unsigned second;
};

struct Rva0010ECA0Node
{
	Rva0010ECA0Node *next;
	Rva0010ECA0Node *previous;
	Rva0010ECA0Value value;
};

class Rva0010ECA0List
{
public:
	void append(const Rva0010ECA0Value &value);

private:
	Rva0010ECA0Node *createNode(const Rva0010ECA0Value &value)
	{
		Rva0010ECA0Node *node = static_cast<Rva0010ECA0Node *>(_STL::__new_alloc::allocate(sizeof(Rva0010ECA0Node)));
		new (&node->value) Rva0010ECA0Value(value);
		return node;
	}

	void insert(Rva0010ECA0Node *at, const Rva0010ECA0Value &value)
	{
		Rva0010ECA0Node *node = createNode(value);
		Rva0010ECA0Node *before = at->previous;
		node->next = at;
		node->previous = before;
		before->next = node;
		at->previous = node;
	}

	Rva0010ECA0Node *m_sentinel;
};

void Rva0010ECA0List::append(const Rva0010ECA0Value &value)
{
	insert(m_sentinel, value);
}
