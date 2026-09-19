class Rva00297E60
{
public:
	unsigned int getAt4();

private:
	char m_padding[ 4 ];
	unsigned int m_value;
};

unsigned int Rva00297E60::getAt4()
{
	return m_value;
}
