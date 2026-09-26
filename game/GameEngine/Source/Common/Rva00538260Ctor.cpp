// cl: /O2 /Ob0

namespace _STL {
class ios_base
{
protected:
	ios_base();
	virtual void handle();

private:
	char m_pad[0x50];
};
}

class Rva00538260 : public _STL::ios_base
{
	char m_54;
	int m_58;
	int m_5C;

public:
	Rva00538260();
};

Rva00538260::Rva00538260()
{
	m_54 = 0;
	m_58 = 0;
	m_5C = 0;
}
