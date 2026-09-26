// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

struct Rva00385150Extra
{
	int a;
	int b;
};

extern Rva0036CA00Str Rva01336E50Str;

class Rva00385150
{
	virtual void handle();
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;

public:
	void set(const Rva0036CA00Str &s, const Rva00385150Extra *extra);
	void reset();
};

void Rva00385150::set(const Rva0036CA00Str &s, const Rva00385150Extra *extra)
{
	m_04 = s;
	m_08 = extra->a;
	m_0C = extra->b;
}

void Rva00385150::reset()
{
	m_04 = Rva01336E50Str;
	m_08 = 0;
	m_0C = 0;
}
