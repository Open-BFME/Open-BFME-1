// cl: /DNDEBUG /MD /O2 /Ob2
// Open-BFME5: clean C++ lift of the retail four-byte table lookup helper.

struct Stride4TableEntry
{
	unsigned int value;
};

class Stride4Table
{
public:
	Stride4TableEntry *lookup(unsigned int index) const;
	Stride4TableEntry *alternateLookup(unsigned int index) const;
	Stride4TableEntry *thirdLookup(unsigned int index) const;
	Stride4TableEntry *fourthLookup(unsigned int index) const;

private:
	Stride4TableEntry *m_entries;
};

// ?d_000c9d80@@YAXXZ
Stride4TableEntry *Stride4Table::lookup(unsigned int index) const
{
	return &m_entries[index];
}

// ?d_000c9e00@@YAXXZ
Stride4TableEntry *Stride4Table::alternateLookup(unsigned int index) const
{
	return &m_entries[index];
}

// ?d_000c9f80@@YAXXZ
Stride4TableEntry *Stride4Table::thirdLookup(unsigned int index) const
{
	return &m_entries[index];
}

// ?d_000c9f90@@YAXXZ
Stride4TableEntry *Stride4Table::fourthLookup(unsigned int index) const
{
	return &m_entries[index];
}
