// ?aptIsType9@Rva008981E0Value@@QAEHXZ
// Open-BFME7: three Apt value type predicates (31 B each at 0x008981E0
// 0x00898200 0x00898220; the negated pooled bitfield reproduces the
// not/test pair) and a 17 B count comparison at 0x00898240.
struct Rva008981E0Value {
	int m_count;
	union {
		unsigned int m_flags;
		struct {
			unsigned int m_type : 6;
			unsigned int m_bits : 9;
			unsigned int m_pooled : 1;
		};
	};
	int aptIsType9();
	int aptIsType27();
	int aptIsType28();
	int aptHasAll();
};
int Rva008981E0Value::aptIsType9()
{
	bool notPooled = !m_pooled;
	if (m_type == 9 && !notPooled)
		return 1;
	return 0;
}
// ?aptIsType27@Rva008981E0Value@@QAEHXZ
int Rva008981E0Value::aptIsType27()
{
	bool notPooled = !m_pooled;
	if (m_type == 27 && !notPooled)
		return 1;
	return 0;
}
// ?aptIsType28@Rva008981E0Value@@QAEHXZ
int Rva008981E0Value::aptIsType28()
{
	bool notPooled = !m_pooled;
	if (m_type == 28 && !notPooled)
		return 1;
	return 0;
}
// ?aptHasAll@Rva008981E0Value@@QAEHXZ
int Rva008981E0Value::aptHasAll()
{
	return (int)m_flags >= m_count;
}
