// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001BD600 (12 bytes).

class Rva001BD600
{
public:
	bool isSet() const;

private:
	unsigned char m_unmodelled_000[0x18];
	unsigned m_flags;
};

bool Rva001BD600::isSet() const
{
	return ((m_flags >> 3) ^ 1u) & 1u;
}
