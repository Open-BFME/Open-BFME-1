// cl: /DNDEBUG /MD /EHsc

inline void *operator new(unsigned int, void *place) { return place; }
inline void operator delete(void *, void *) {}

struct Rva005A84D0Tail
{
	int m_values[6];
};

class BfmeThingAB
{
public:
	BfmeThingAB(const BfmeThingAB &other)
	{
		bfmeBaseAB((void *)&other);
		m_tail = other.m_tail;
	}
	~BfmeThingAB();
	void bfmeBaseAB(void *other);

private:
	char m_base[0x10];
	Rva005A84D0Tail m_tail;
};

void constructRva005A84D0Record(BfmeThingAB *place, const BfmeThingAB &value)
{
	new (place) BfmeThingAB(value);
}
