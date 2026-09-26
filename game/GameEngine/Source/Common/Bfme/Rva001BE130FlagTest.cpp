// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BE130 (30 bytes).

class Rva001BE130
{
public:
	bool has(unsigned bit) const;

private:
	unsigned char m_unmodelled_000[0x28C];
	unsigned m_flags;
};

bool Rva001BE130::has(unsigned bit) const
{
	return (m_flags & (1u << bit)) != 0;
}
