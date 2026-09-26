class Rva003D4CD0
{
public:
	void set(short value);

private:
	void *m_data;
};

void Rva003D4CD0::set(short value)
{
	*(short *)((char *)m_data + 0x12) = value;
}
