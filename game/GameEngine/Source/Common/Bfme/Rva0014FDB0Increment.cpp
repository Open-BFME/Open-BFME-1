// cl: /DNDEBUG /MD /EHsc

class Rva0014FDB0
{
public:
	void increment();

private:
	unsigned char m_padding[0x18];
	volatile unsigned m_value;
};

void Rva0014FDB0::increment()
{
	++m_value;
}
