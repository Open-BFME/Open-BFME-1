// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x003BC6D0 (8 bytes).

class Rva003BC6D0
{
public:
	void increment();

private:
	unsigned char m_unmodelled_000[0x20];
	volatile unsigned m_value;
};

void Rva003BC6D0::increment()
{
	++m_value;
}
