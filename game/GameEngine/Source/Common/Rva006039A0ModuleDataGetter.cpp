// cl: /DNDEBUG /MD /EHsc

class Rva006039A0ModuleDataGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

unsigned int Rva006039A0ModuleDataGetter::get() const
{
	return m_value;
}
