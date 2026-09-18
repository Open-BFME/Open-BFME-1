// cl: /DNDEBUG /MD /EHsc

class Rva002D4F90DwordGetter
{
public:
	unsigned int get() const;

private:
	char m_padding[4];
	unsigned int m_value;
};

unsigned int Rva002D4F90DwordGetter::get() const
{
	return m_value;
}
