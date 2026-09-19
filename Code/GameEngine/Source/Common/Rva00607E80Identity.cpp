// cl: /DNDEBUG /MD /EHsc

class Rva00607E80Identity
{
public:
	void *identity()
	{
		return this;
	}
};

typedef void *(Rva00607E80Identity::*Rva00607E80IdentityMethod)();
Rva00607E80IdentityMethod g_rva00607E80Identity = &Rva00607E80Identity::identity;
