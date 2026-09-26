// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva000DF920
{
	Rva0036CA00Str *m_00;
	Rva0036CA00Str *m_04;

public:
	Rva000DF920 &operator=(const Rva0036CA00Str *pair);
};

Rva000DF920 &Rva000DF920::operator=(const Rva0036CA00Str *pair)
{
	*m_00 = pair[0];
	*m_04 = pair[1];
	return *this;
}
