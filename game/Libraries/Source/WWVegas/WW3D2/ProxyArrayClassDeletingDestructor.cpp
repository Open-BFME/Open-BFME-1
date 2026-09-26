// cl: /EHs-c-
//
// Compiler-owned scalar-deleting wrapper for the matched ProxyArrayClass
// complete destructor at retail 0x0097C9D0. The upstream HLOD source proves
// the ref-counted proxy-array identity; this focused TU selects global delete.

class ProxyArrayClass
{
public:
	virtual ~ProxyArrayClass();
};

void ForceProxyArrayClassDeletingDestructor()
{
	ProxyArrayClass value;
}
