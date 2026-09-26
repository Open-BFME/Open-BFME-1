// Retail 0x00643CA0 returns the dword at this.
class Rva00643CA0DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva00643CA0DwordGetter::get() const
{
	return m_value;
}
