// cl: /O2 /Ob0

struct Rva0049D540Element
{
	char m_bytes[112];
};

class Rva0049D540Vector
{
public:
	unsigned int capacity() const;

private:
	Rva0049D540Element *m_begin;
	Rva0049D540Element *m_end;
	Rva0049D540Element *m_capacity;
};

unsigned int Rva0049D540Vector::capacity() const
{
	return (unsigned int)(m_capacity - m_begin);
}
