// cl: /O2 /Ob0

class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);

private:
	void *m_item;
};

class Rva002E9E70Mid
{
public:
	Rva002E9E70Mid(const Rva002E9E70Mid &other);

private:
	void *m_item;
};

class Rva002E9E70
{
	Rva0036CA00Str m_00;
	char m_04;
	Rva002E9E70Mid m_08;

public:
	Rva002E9E70(const Rva002E9E70 &other);
};

Rva002E9E70::Rva002E9E70(const Rva002E9E70 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}
