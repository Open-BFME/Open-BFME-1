// cl: /DNDEBUG /MD /EHsc

class Rva006DAB30ValueGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[0xC];
	unsigned int m_value;
};

unsigned int Rva006DAB30ValueGetter::get() const
{
	return m_value;
}
