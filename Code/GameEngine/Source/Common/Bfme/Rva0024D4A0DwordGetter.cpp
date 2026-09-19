// cl: /DNDEBUG /MD /EHsc
// Retail reads a dword at this+0x04 and returns it. No caller proves an
// owner, so the class name keeps the carved address visible.

class Rva0024D4A0DwordGetter
{
private:
	char m_data[4];
	int m_value;

public:
	int get() const;
};

int Rva0024D4A0DwordGetter::get() const
{
	return m_value;
}
