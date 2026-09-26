// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva003ACF60
{
	virtual void handle();
	Rva0036CA00Str m_04;
	Rva0036CA00Str m_08;
	Rva0036CA00Str m_0C;
	int m_10;
	int m_14;
	char m_18;
	char m_19;
	Rva0036CA00Str m_1C;
	Rva0036CA00Str m_20;
	Rva0036CA00Str m_24;
	Rva0036CA00Str m_28;
	char m_2C;

public:
	Rva003ACF60 &operator=(const Rva003ACF60 &other);
};

Rva003ACF60 &Rva003ACF60::operator=(const Rva003ACF60 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_19 = other.m_19;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	return *this;
}
