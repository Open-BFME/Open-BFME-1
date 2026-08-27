// Open-BFME: clean C++ lift of the accumulator body at 0x000C7DA0.

class Rva000C7DA0
{
public:
	int adjust(int value);                         // retail 0x000C7D10
	void add(int value);

private:
	int m_padding[2];
	int m_total;                                   // +0x08
};

void Rva000C7DA0::add(int value)
{
	m_total += adjust(value);
}

class Rva000C7DC0
{
public:
	int adjust(int value);                         // retail 0x000C7D10
	void subtract(int value);

private:
	int m_padding[2];
	int m_total;                                   // +0x08
};

void Rva000C7DC0::subtract(int value)
{
	m_total -= adjust(value);
}
