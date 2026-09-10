// cl: /DNDEBUG /MD /EHsc

// STLport __pop_heap_aux over the sixteen-byte record of the neighbouring heap
// helpers. Retail 0x00474A90 steps back one element and forwards it by value to
// __pop_heap at 0x004748F0 through the 0x0000561E jump stub.

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);

private:
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	T *m_data;

	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct Rva004748F0Element
{
	int m_key;
	int m_second;
	int m_third;
	AsciiString m_name;
};

struct Rva004748F0Compare
{
	int m_state;
};

void Rva004748F0PopHeap(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *result, Rva004748F0Element value,
	Rva004748F0Compare comp, int *);

#pragma comment(linker, "/alternatename:?Rva004748F0PopHeap@@YAXPAURva004748F0Element@@00U1@URva004748F0Compare@@PAH@Z=?j_0000561e@@YAXXZ")

void Rva00474A90PopHeapAux(Rva004748F0Element *first, Rva004748F0Element *last,
	Rva004748F0Element *, Rva004748F0Compare comp)
{
	Rva004748F0PopHeap(first, last - 1, last - 1, *(last - 1), comp, (int *)0);
}
