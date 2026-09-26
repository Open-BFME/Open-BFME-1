// Retail 0x006BE4D0 returns the dword at this.
class Rva006BE4D0DwordGetter
{
public:
	unsigned int get() const;

private:
	unsigned int m_value;
};

unsigned int Rva006BE4D0DwordGetter::get() const
{
	return m_value;
}
