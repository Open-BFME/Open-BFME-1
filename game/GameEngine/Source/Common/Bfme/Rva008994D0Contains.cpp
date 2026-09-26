// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x008994D0 (45 bytes).
// The bounded table stores dword values at +0x18; the low byte at +0x1C
// supplies the number of entries searched.

class Rva008994D0
{
public:
	bool contains(unsigned *value);

private:
	unsigned char m_unmodelled_000[0x18];
	unsigned *m_values;
	unsigned m_count;
};

bool Rva008994D0::contains(unsigned *value)
{
	for (unsigned index = 0; index < (m_count & 0xFF); ++index)
		if (m_values[index] == reinterpret_cast<unsigned>(value))
			return true;
	return false;
}
