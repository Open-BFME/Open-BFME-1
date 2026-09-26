// cl: /O2 /Ob0

class Rva008FE900NullableField
{
	int *m_data;
public:
	int get() const;
};

int Rva008FE900NullableField::get() const
{
	return m_data ? m_data[2] : -1;
}
