// cl: /O2 /Ob0

class Rva002E9E70Mid
{
public:
	Rva002E9E70Mid &operator=(const Rva002E9E70Mid &other);

private:
	void *m_item;
};

class Rva002E17F0
{
	virtual void handle();
	char m_04;
	Rva002E9E70Mid m_08;

public:
	void operator=(const Rva002E17F0 &other);
};

void Rva002E17F0::operator=(const Rva002E17F0 &other)
{
	m_08 = other.m_08;
	m_04 = other.m_04;
}
