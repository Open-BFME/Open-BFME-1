// cl: /O2 /Ob0

class Gen0089CC10
{
public:
	int handle();
};

class Rva00899D70
{
	char m_lead[8];
	Gen0089CC10 m_inner;

public:
	int next();
};

int Rva00899D70::next()
{
	return m_inner.handle() + 1;
}
