// cl: /O2 /MD /EHsc-

class Rva00214E60Field4Getter
{
public:
	int get() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva00214E60Field4Getter::get() const
{
	return m_value;
}
