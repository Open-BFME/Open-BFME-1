// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BE200 (23 bytes).

struct Rva001BE200Target
{
	unsigned char m_unmodelled_000[0x2EC];
	unsigned m_value;
};

class Rva001BE200
{
public:
	void copy(unsigned value);

private:
	unsigned char m_unmodelled_000[0x80];
	Rva001BE200Target *m_target;
};

void Rva001BE200::copy(unsigned value)
{
	if (m_target != 0)
		m_target->m_value = value;
}
