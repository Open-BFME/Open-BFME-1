// cl: /DNDEBUG /MD /O2 /Ob2
// Open-BFME5: clean C++ lift of the retail eight-byte table lookup helper.

struct Stride8TableEntry
{
	unsigned int first;
	unsigned int second;
};

class Stride8Table
{
public:
	Stride8TableEntry *lookup(unsigned int index) const;

private:
	Stride8TableEntry *m_entries;
};

Stride8TableEntry *Stride8Table::lookup(unsigned int index) const
{
	return &m_entries[index];
}
