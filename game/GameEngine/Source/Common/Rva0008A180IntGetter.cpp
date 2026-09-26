// cl: /O2

class Rva0008A180IntGetter
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva0008A180IntGetter::get() const
{
	return m_value;
}
