// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../Include/Common/ScalarTypes.h"



class FirewallHelperClass
{
	friend class Rva00012F3FFirewallHelperThunk;
private:
	Int getNATPortAllocationScheme(Int numPorts, UnsignedShort *originalPorts,
		UnsignedShort *mangledPorts, Bool &relativeDelta, Bool &looksGood);
};

class Rva00012F3FFirewallHelperThunk
{
public:
	Int getNATPortAllocationScheme(Int numPorts, UnsignedShort *originalPorts,
		UnsignedShort *mangledPorts, Bool &relativeDelta, Bool &looksGood);
};

Int Rva00012F3FFirewallHelperThunk::getNATPortAllocationScheme(
	Int numPorts, UnsignedShort *originalPorts, UnsignedShort *mangledPorts,
	Bool &relativeDelta, Bool &looksGood)
{
	return ((FirewallHelperClass *)this)->getNATPortAllocationScheme(
		numPorts, originalPorts, mangledPorts, relativeDelta, looksGood);
}
