// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME: resize wrapper for a vector-like array of 12-byte POD values,
// retail 0x007705D0, 93 bytes.

struct Rva007705D0Element
{
	int value[3];
};

struct Rva007705D0RandomAccessTag {};

Rva007705D0Element *Rva007705D0Copy(
	Rva007705D0Element *first,
	Rva007705D0Element *last,
	Rva007705D0Element *result,
	const Rva007705D0RandomAccessTag &tag,
	int *distance);

class Rva007705D0Vector
{
public:
	void resizeValue(unsigned int newSize, Rva007705D0Element value);
	void fillInsert(Rva007705D0Element *position, unsigned int count,
		const Rva007705D0Element &value);

private:
	Rva007705D0Element *m_begin;
	Rva007705D0Element *m_end;
	Rva007705D0Element *m_capacity;
};

void Rva007705D0Vector::resizeValue(
	unsigned int newSize, Rva007705D0Element value)
{
	unsigned int oldSize = (unsigned int)(m_end - m_begin);
	if (newSize < oldSize)
	{
		Rva007705D0Element *newEnd = m_begin + newSize;
		Rva007705D0RandomAccessTag tag;
		m_end = Rva007705D0Copy(
			m_end, m_end, newEnd, tag, 0);
	}
	else
	{
		fillInsert(m_end, newSize - oldSize, value);
	}
}
