class Rva003CBA00
{
public:
	int get(int index);

private:
	char m_pad[0x10];
	int m_data[1];
};

int Rva003CBA00::get(int index)
{
	return m_data[index];
}
