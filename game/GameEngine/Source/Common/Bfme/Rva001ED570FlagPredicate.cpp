// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001ED570 (12 bytes).

class Rva001ED570
{
public:
	bool isSet() const;

private:
	unsigned char m_unmodelled_000[0x18];
	unsigned m_flags;
};

bool Rva001ED570::isSet() const
{
	return (m_flags & 7u) != 0;
}
