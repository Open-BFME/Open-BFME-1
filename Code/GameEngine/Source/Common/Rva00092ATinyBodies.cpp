// cl: /O2 /Ob0
//
// Four carved leaves in the same retail cluster.  Their only known callers are
// address-only ILT thunks, so every identity deliberately retains its RVA.

void Rva00092A30NoOp()
{
}

class Rva00092A80DwordField
{
	int m_field00;
	int m_value;

public:
	int get() const;
};

int Rva00092A80DwordField::get() const
{
	return m_value;
}

void Rva00092BA0NoOp()
{
}

void Rva00092BB0NoOp()
{
}
