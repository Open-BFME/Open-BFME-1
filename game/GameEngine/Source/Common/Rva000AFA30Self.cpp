// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// The carved three-byte body returns its receiver unchanged.  No semantic
// owner is proven, so the class and method retain the retail address.

class Rva000AFA30
{
public:
	__declspec(noinline) Rva000AFA30 *self()
	{
		return this;
	}
};

typedef Rva000AFA30 *(Rva000AFA30::*Rva000AFA30SelfMethod)();
Rva000AFA30SelfMethod g_rva000AFA30Self = &Rva000AFA30::self;
