// cl: /EHsc
// Destructor that destroys members at +8 then +4 (an Inner at +4) and stores
// a vftable at +0 last.

struct Rva001D6D80Head
{
	virtual ~Rva001D6D80Head() {}
};

struct Rva001D6D80Elem
{
	char m_body[4];
	Rva001D6D80Elem();
	~Rva001D6D80Elem();
};

struct Rva001D6D80Inner
{
	Rva001D6D80Elem m_first;
	Rva001D6D80Elem m_second;
};

struct Rva001D6D80
{
	Rva001D6D80Head m_head;
	Rva001D6D80Inner m_inner;
	~Rva001D6D80();
};

Rva001D6D80::~Rva001D6D80() {}
