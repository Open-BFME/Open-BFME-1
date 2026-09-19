// cl: /O2 /MD

class Rva005DCC00ValueGetter
{
public:
	int get() const;

private:
	int m_value;
};

int Rva005DCC00ValueGetter::get() const
{
	return m_value;
}
