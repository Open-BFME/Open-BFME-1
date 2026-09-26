// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

class FirewallHelperClassGetNATPortAllocationSchemeShim
{
public:
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
	return ((FirewallHelperClassGetNATPortAllocationSchemeShim *)this)->getNATPortAllocationScheme(
		numPorts, originalPorts, mangledPorts, relativeDelta, looksGood);
}
