// ??0Rva008947A0Owner@@QAE@XZ
// Constructor: a destructible head member zeroed to 0 two further zeroed
// ints a self-pointer to the trailing array and a two-element array member
// built through the EH vector constructor iterator.
// Identity unrecovered; named from the address.

class Rva008947A0Elem
{
public:
	Rva008947A0Elem(void);
	~Rva008947A0Elem();

	int m_data;
};

class Rva008947A0Head
{
public:
	Rva008947A0Head(void)
	{
		m_a = 0;
	}
	~Rva008947A0Head();

	int m_a;
};

class Rva008947A0Owner
{
public:
	Rva008947A0Owner(void);

	Rva008947A0Head m_head;
	int m_b;
	int m_c;
	Rva008947A0Elem *m_items;
	Rva008947A0Elem m_array[2];
};

Rva008947A0Owner::Rva008947A0Owner(void)
	: m_b(0), m_c(0), m_items(m_array)
{
}
