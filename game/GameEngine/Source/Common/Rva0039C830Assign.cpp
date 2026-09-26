// cl: /O2 /Ob0

class ScienceInfoBase
{
public:
	ScienceInfoBase &operator=(const ScienceInfoBase &other);

private:
	char m_head[0x0C];
};

class Rva0036CA00Str
{
public:
	Rva0036CA00Str &operator=(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva00630D00UStr
{
public:
	Rva00630D00UStr &operator=(const Rva00630D00UStr &other);

private:
	void *m_item;
};

class Rva0039C830Mid
{
public:
	Rva0039C830Mid &operator=(const Rva0039C830Mid &other);

private:
	int m_00;
};

class Rva0039C830 : public ScienceInfoBase
{
	Rva0036CA00Str m_0C;
	Rva00630D00UStr m_10;
	Rva0039C830Mid m_14;

public:
	Rva0039C830 &operator=(const Rva0039C830 &other);
};

Rva0039C830 &Rva0039C830::operator=(const Rva0039C830 &other)
{
	ScienceInfoBase::operator=(other);
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	return *this;
}
