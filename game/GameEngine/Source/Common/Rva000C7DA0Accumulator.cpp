// Open-BFME: clean C++ lift of the accumulator body at 0x000C7DA0.

class Drawable;
int __stdcall bfmeGetXR(Drawable *d);

class Rva000C7DA0
{
public:
	void add(int value);

private:
	int m_padding[2];
	int m_total;                                   // +0x08
};

void Rva000C7DA0::add(int value)
{
	m_total += bfmeGetXR((Drawable *)value);
}

class Rva000C7DC0
{
public:
	void subtract(int value);

private:
	int m_padding[2];
	int m_total;                                   // +0x08
};

void Rva000C7DC0::subtract(int value)
{
	m_total -= bfmeGetXR((Drawable *)value);
}
