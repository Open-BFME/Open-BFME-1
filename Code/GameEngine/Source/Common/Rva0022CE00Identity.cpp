// ?get@Rva0022CE00Owner@@QAEPAXXZ
// The carved boundary proves a thiscall identity accessor with no semantic
// owner evidence. Keep the address in the class name until a caller names it.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0022CE00Owner
{
public:
	void *get();
};

void *Rva0022CE00Owner::get()
{
	return this;
}
