class Rva003D4CF0
{
public:
	void set(short value);

private:
	void *m_data;
};

void Rva003D4CF0::set(short value)
{
	*(short *)((char *)m_data + 0x10) = value;
}
