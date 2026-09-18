// cl: /O2

class Rva005BA110
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva005BA110::get() const
{
	return m_value;
}
