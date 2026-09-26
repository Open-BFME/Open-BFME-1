// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BD980 (25 bytes).

class Rva001BD980
{
public:
	bool has(unsigned bit) const;

private:
	unsigned char m_unmodelled_000[0x28];
	unsigned m_flags;
};

bool Rva001BD980::has(unsigned bit) const
{
	return (m_flags & (1u << bit)) != 0;
}
