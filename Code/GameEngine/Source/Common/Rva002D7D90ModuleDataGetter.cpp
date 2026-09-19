// cl: /DNDEBUG /MD /EHsc

class Rva002D7D90ModuleDataGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

unsigned int Rva002D7D90ModuleDataGetter::get() const
{
	return m_value;
}
