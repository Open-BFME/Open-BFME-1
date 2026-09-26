// cl: /O2 /Ob0

class Rva005818D0
{
	int m_value;

public:
	bool eq(const int *a) const;
};

bool Rva005818D0::eq(const int *a) const
{
	return a[1] == m_value;
}
