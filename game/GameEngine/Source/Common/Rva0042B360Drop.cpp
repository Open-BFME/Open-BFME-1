// Retail 0x0042B360 is an anonymous two-argument helper reached through the
// generated thunk at ILT 0x00042578.  Its only proven behavior is ret 8, so
// the source keeps the address in the opaque type name.

class Rva0042B360
{
public:
	static void __stdcall drop( int first, int second );
};

void __stdcall Rva0042B360::drop( int first, int second )
{
	(void)first;
	(void)second;
}
