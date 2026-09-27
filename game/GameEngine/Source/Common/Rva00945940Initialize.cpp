// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-
// Retail 0x00945940 writes zero at +4 then 0x0113D01C at +0 and returns this.
// The address-derived fields encode only the observed layout and store order.

struct Rva00945940Owner
{
	void *field0;
	unsigned int field4;
	Rva00945940Owner *initialize();
};

Rva00945940Owner *Rva00945940Owner::initialize()
{
	field4 = 0;
	field0 = reinterpret_cast<void *>(0x0113D01C);
	return this;
}
