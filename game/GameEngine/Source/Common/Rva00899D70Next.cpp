// cl: /O2 /Ob0

// Retail body at 0x0089CC10; declared in
// Rva0089CC10ConditionalOffset.cpp, spelled here by its defining name so the
// call resolves to ?get@Rva0089CC10Object@@QBEHXZ.
class Rva0089CC10Object
{
public:
	int get() const;
};

class Rva00899D70
{
	char m_lead[8];
	Rva0089CC10Object m_inner;

public:
	int next();
};

int Rva00899D70::next()
{
	return m_inner.get() + 1;
}
