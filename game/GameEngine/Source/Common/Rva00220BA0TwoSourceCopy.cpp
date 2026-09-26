// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva00220BA0Tail
{
	unsigned int m_values[10];
};

class Rva00220BA0Value
{
public:
	Rva00220BA0Value *copyFrom(const unsigned int *head, const Rva00220BA0Tail *tail);

private:
	unsigned int m_head;
	Rva00220BA0Tail m_tail;
};

Rva00220BA0Value *Rva00220BA0Value::copyFrom(const unsigned int *head,
	const Rva00220BA0Tail *tail)
{
	m_head = *head;
	m_tail = *tail;
	return this;
}
