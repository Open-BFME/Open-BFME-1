// cl: /DNDEBUG /MD /O2 /Ob2
// Open-BFME5: clean C++ lift of the retail pointer-range count helper.

class PointerRangeCount
{
public:
	unsigned int size() const;
	unsigned int alternateSize() const;
	unsigned int thirdSize() const;

private:
	void **m_begin;
	void **m_end;
};

// ?d_000c9db0@@YAXXZ
unsigned int PointerRangeCount::size() const
{
	return m_end - m_begin;
}

// ?d_000c9e40@@YAXXZ
unsigned int PointerRangeCount::alternateSize() const
{
	return m_end - m_begin;
}

// ?d_000c9f70@@YAXXZ
unsigned int PointerRangeCount::thirdSize() const
{
	return m_end - m_begin;
}
